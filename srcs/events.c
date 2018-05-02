/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 02:48:18 by tjeanner          #+#    #+#             */
/*   Updated: 2018/05/02 12:09:07 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		move_events(t_env *env, SDL_Event event)
{
/*	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_z)
	{
		env->portion -= 1;
		ft_putstr(", portion:");
		ft_putnbr(env->portion);
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_x)
	{
		env->portion += 1;
		ft_putstr(", portion:");
		ft_putnbr(env->portion);
	}*/
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_c && env->lums.amb_coef >= 0.020)
		env->lums.amb_coef -= 0.020;
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_v && env->lums.amb_coef <= 0.980)
		env->lums.amb_coef += 0.020;
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_n)
	{
		env->objs.obj[env->objs.curr].k_diff *= 11.00 / 10.00;
		ft_putstr(", rugos:");
		ft_putnbr(100 * env->objs.obj[env->objs.curr].k_diff);
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_b)
	{
		env->objs.obj[env->objs.curr].k_diff *= (env->objs.obj[env->objs.curr].k_diff > 0.1)
									? 10.00 / 11.00 : 1.0;
		ft_putstr(", rugos:");
		ft_putnbr(100 * env->objs.obj[env->objs.curr].k_diff);
	}
	else
		return (0);
	return (1);
}

static int		events_obj_mod(t_env *env, unsigned int sym)
{
	if ((sym == SDLK_1 || sym == SDLK_2 || sym == SDLK_3 || sym == SDLK_4))
		update_and_copy_a(env, sym);
	else if (sym == SDLK_BACKSPACE && env->objs.curr >= 0)
		update_and_copy_r(env, env->objs.curr);
	else if (sym == SDLK_BACKSLASH)
	{
		if (env->objs.curr >= 0)
			env->objs.obj[env->objs.curr].col = get_rand();
		else if (env->objs.curr == -2)
			env->lums.lum[env->lums.curr].col = get_rand();
	}
	else if (sym == SDLK_MINUS && env->objs.curr >= 0)
	{
		if (env->objs.obj[env->objs.curr].type == CONE && env->objs.obj[env->objs.curr].radius > 0.0)
			env->objs.obj[env->objs.curr].radius -= 0.5;
		else if (env->objs.obj[env->objs.curr].type != CONE)
			env->objs.obj[env->objs.curr].radius -= (env->objs.obj[env->objs.curr].radius >= 0 || env->objs.obj[env->objs.curr].type == SPHERE || env->objs.obj[env->objs.curr].type == PLANE) ? 10 : 0;
		ft_putnbr(env->objs.obj[env->objs.curr].radius);
		ft_putstr(", ");
	}
	else if (sym == SDLK_MINUS && env->objs.curr == -2)
		env->lums.lum[env->lums.curr].coef /= (env->lums.lum[env->lums.curr].coef > 0) ? 1.1000000 : 10;
	else if (sym == SDLK_EQUALS && env->objs.curr >= 0)
	{
		if (env->objs.obj[env->objs.curr].type == CONE && env->objs.obj[env->objs.curr].radius < 89.5)
			env->objs.obj[env->objs.curr].radius += 0.5;
		else if (env->objs.obj[env->objs.curr].type != CONE)
			env->objs.obj[env->objs.curr].radius += 10;
		ft_putnbr(env->objs.obj[env->objs.curr].radius);
		ft_putstr(", ");
	}
	else if (sym == SDLK_EQUALS && env->objs.curr == -2)
		env->lums.lum[env->lums.curr].coef *= 1.1000000;
	else
		return (0);
	return (1);
}

static int		events_random(t_env *env, unsigned int sym, SDL_Event event)
{
	if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		|| event.type == SDL_QUIT)
	{
		ft_putendl("yolo");
		env->state = 1;
		return (0);
	}
	else if (event.type == SDL_KEYDOWN && sym == SDLK_m)
	{
		ft_memdel((void **)&env->objs.obj);
		ft_memdel((void **)&env->cams.cam);
		ft_memdel((void **)&env->lums.lum);
		free(env->effects.filter);
		j_init(env);
//		init_scene(env);
	}
/*	else if (event.type == SDL_KEYDOWN && sym == SDLK_KP_MINUS)
		env->flou *= (env->flou > WIN_X  / 2 || env->flou > WIN_Y  / 2) ? 1.0 : 2.0;
	else if (event.type == SDL_KEYDOWN && sym == SDLK_KP_PLUS)
		env->flou /= (env->flou <= 1) ? 1 : 2;*/
	else if (event.type == SDL_KEYDOWN && sym == SDLK_END)
		j_scene_generator(env);
	else
		return (0);
	return (1);
}

int				events_special_move_cam(t_env *env, unsigned int sym, SDL_Event event)
{
	int		angle;

	if (event.type == SDL_KEYDOWN)
	{
		if (env->objs.curr == -1 && (sym == SDLK_5 || sym == SDLK_6))
		{
			env->cams.cam[env->cams.curr].pos = rotation(env->cams.cam[env->cams.curr].pos, (t_v){0, 1, 0}, angle = (sym == SDLK_5) ? 1.0 : -1.0);
			env->cams.cam[env->cams.curr].vcam = vect_norm(vect_inv(env->cams.cam[env->cams.curr].pos));
			env->cams.cam[env->cams.curr].v3cam = vect_prod(env->cams.cam[env->cams.curr].vcam, env->cams.cam[env->cams.curr].v2cam);
		}
		else if (env->objs.curr >= 0 && (sym == SDLK_5 || sym == SDLK_6))
		{
			env->cams.cam[env->cams.curr].pos = vect_add(env->objs.obj[env->objs.curr].o, rotation(vect_sous(env->cams.cam[env->cams.curr].pos, env->objs.obj[env->objs.curr].o), (t_v){0, 1, 0}, angle = (sym == SDLK_5) ? 1.0 : -1.0));
			env->cams.cam[env->cams.curr].vcam = vect_norm(vect_sous(env->objs.obj[env->objs.curr].o, env->cams.cam[env->cams.curr].pos));
			env->cams.cam[env->cams.curr].v3cam = vect_prod(env->cams.cam[env->cams.curr].vcam, env->cams.cam[env->cams.curr].v2cam);
		}
		else
			return (0);
		return (1);
	}
	return (0);
}

int				events(t_env *env)
{
	SDL_Event		event;
	unsigned int	sym;
	t_cam			*cam;
	t_obj			*obj;

	cam = &env->cams.cam[env->cams.curr];
	obj = &env->objs.obj[env->objs.curr];
	if (SDL_PollEvent(&event) != 0)
	{
		sym = event.key.keysym.sym;
		cam->vcam = vect_norm(cam->vcam);
		cam->v2cam = vect_norm(cam->v2cam);
		cam->v3cam = vect_norm(cam->v3cam);
		if (events_random(env, sym, event) || events_sel(env, event, sym))
			;
		else if (events_special_move_cam(env, sym, event))
			;
		else if (event.type == SDL_KEYDOWN && (events_obj_mod(env, sym)
			|| events_rotation(env, sym, &obj->norm)
			|| events_move(env, sym, cam, obj)))
			;
//		else if (event.type == SDL_KEYDOWN && sym == SDLK_z)
//			event_cam_switch(env, sym);
		else if (event.type == SDL_MOUSEWHEEL && event.wheel.y != 0)
			mouse_move(env, event, &env->cams.cam[env->cams.curr],
						&env->objs.obj[env->objs.curr]);
		else if (!move_events(env, event))
			ev_screenshot(env);
		tutu(env);
	}
	return (1);
}

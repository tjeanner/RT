/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 02:48:18 by tjeanner          #+#    #+#             */
/*   Updated: 2018/04/15 17:54:03 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		move_events(t_env *env, SDL_Event event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_z)
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
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_c && env->amb_coef >= 0.020)
		env->amb_coef -= 0.020;
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_v && env->amb_coef <= 0.980)
		env->amb_coef += 0.020;
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_n)
	{
		env->objs[env->curr_obj].k_diff *= 11.00 / 10.00;
		ft_putstr(", rugos:");
		ft_putnbr(100 * env->objs[env->curr_obj].k_diff);
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_b)
	{
		env->objs[env->curr_obj].k_diff *= (env->objs[env->curr_obj].k_diff > 0.1)
									? 10.00 / 11.00 : 1.0;
		ft_putstr(", rugos:");
		ft_putnbr(100 * env->objs[env->curr_obj].k_diff);
	}
	else
		return (0);
	return (1);
}

static int		events_obj_mod(t_env *env, unsigned int sym)
{
	if ((sym == SDLK_1 || sym == SDLK_2 || sym == SDLK_3 || sym == SDLK_4))
		update_and_copy_a(env, sym);
	else if (sym == SDLK_BACKSPACE && env->curr_obj >= 0)
		update_and_copy_r(env, env->curr_obj);
	else if (sym == SDLK_BACKSLASH)
	{
		if (env->curr_obj >= 0)
			env->objs[env->curr_obj].col = get_rand();
		else if (env->curr_obj == -2)
			env->lums[env->curr_lum].col = get_rand();
	}
	else if (sym == SDLK_MINUS && env->curr_obj >= 0)
	{
		if (env->objs[env->curr_obj].type == 'c' && env->objs[env->curr_obj].radius > 0.0)
			env->objs[env->curr_obj].radius -= 0.5;
		else if (env->objs[env->curr_obj].type != 'c')
			env->objs[env->curr_obj].radius -= (env->objs[env->curr_obj].radius >= 0 || env->objs[env->curr_obj].type == 's') ? 10 : 0;
		ft_putnbr(env->objs[env->curr_obj].radius);
		ft_putstr(", ");
	}
	else if (sym == SDLK_MINUS && env->curr_obj == -2)
		env->lums[env->curr_lum].coef /= (env->lums[env->curr_lum].coef > 0) ? 1.1000000 : 10;
	else if (sym == SDLK_EQUALS && env->curr_obj >= 0)
	{
		if (env->objs[env->curr_obj].type == 'c' && env->objs[env->curr_obj].radius < 89.5)
			env->objs[env->curr_obj].radius += 0.5;
		else if (env->objs[env->curr_obj].type != 'c')
			env->objs[env->curr_obj].radius += 10;
		ft_putnbr(env->objs[env->curr_obj].radius);
		ft_putstr(", ");
	}
	else if (sym == SDLK_EQUALS && env->curr_obj == -2)
		env->lums[env->curr_lum].coef *= 1.1000000;
	else
		return (0);
	return (1);
}

static int	events_random(t_env *env, unsigned int sym, SDL_Event event)
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
		ft_memdel((void **)&env->objs);
		ft_memdel((void **)&env->cams);
		ft_memdel((void **)&env->lums);
		free(env->filter);
		j_init(env);
//		init_scene(env);
	}
	else if (event.type == SDL_KEYDOWN && sym == SDLK_KP_MINUS)
		env->flou *= (env->flou > WIN_X  / 2 || env->flou > WIN_Y  / 2) ? 1.0 : 2.0;
	else if (event.type == SDL_KEYDOWN && sym == SDLK_KP_PLUS)
		env->flou /= (env->flou <= 1) ? 1 : 2;
	else if (event.type == SDL_KEYDOWN && sym == SDLK_END)
		j_scene_generator(env);
	else
		return (0);
	return (1);
}

int			events_special_move_cam(t_env *env, unsigned int sym, SDL_Event event)
{
	int		angle;

	if (event.type == SDL_KEYDOWN)
	{
		if (env->curr_obj == -1 && (sym == SDLK_5 || sym == SDLK_6))
		{
			env->cams[env->curr_cam].pos = rotation(env->cams[env->curr_cam].pos, (t_v){0, 1, 0}, angle = (sym == SDLK_5) ? 1.0 : -1.0);
			env->cams[env->curr_cam].vcam = vect_mult(env->cams[env->curr_cam].pos, -1.0);
			env->cams[env->curr_cam].vcam = vect_norm(env->cams[env->curr_cam].vcam);
			env->cams[env->curr_cam].v3cam = vect_inv(vect_prod(env->cams[env->curr_cam].vcam, env->cams[env->curr_cam].v3cam));
		}
		else if (env->curr_obj >= 0 && (sym == SDLK_5 || sym == SDLK_6))
		{
			env->cams[env->curr_cam].pos = vect_add(env->objs[env->curr_obj].o, rotation(vect_add(env->cams[env->curr_cam].pos, vect_mult(env->objs[env->curr_obj].o, -1.0)), (t_v){0, 1, 0}, angle = (sym == SDLK_5) ? 1.0 : -1.0));
			env->cams[env->curr_cam].vcam = vect_add(env->objs[env->curr_obj].o, vect_mult(env->cams[env->curr_cam].pos, -1.0));
			env->cams[env->curr_cam].vcam = vect_norm(env->cams[env->curr_cam].vcam);
			env->cams[env->curr_cam].v3cam = vect_inv(vect_prod(env->cams[env->curr_cam].vcam, env->cams[env->curr_cam].v3cam));
		}
		else
			return (0);
		return (1);
	}
	return (0);
}

int			events(t_env *env)
{
	SDL_Event		event;
	unsigned int	sym;
	t_cam			*cam;
	t_obj			*obj;

	cam = &env->cams[env->curr_cam];
	obj = &env->objs[env->curr_obj];
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
		else if (event.type == SDL_KEYDOWN && sym >= SDLK_KP_1
			&& sym <= SDLK_KP_0)
			event_cam_switch(env, sym);
		else if (event.type == SDL_MOUSEWHEEL && event.wheel.y != 0)
			mouse_move(env, event, &env->cams[env->curr_cam],
						&env->objs[env->curr_obj]);
		else if (!move_events(env, event))
			return (0);
		rays(env);
	}
	return (1);
}

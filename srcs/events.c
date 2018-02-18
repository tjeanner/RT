/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 02:48:18 by tjeanner          #+#    #+#             */
/*   Updated: 2018/02/18 05:52:23 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		move_events(t_env *env, SDL_Event event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_z)
	{
		env->portion *= (env->portion > 0.00001) ? 10.00 / 13.00 : 1.0;
		ft_putstr(", portion:");
		ft_putnbr(100 * env->portion);
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_x)
	{
		env->portion *= 13.00 / 10.00;
		ft_putstr(", portion:");
		ft_putnbr(100 * env->portion);
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_c)
	{
		env->constante2test -= 0.05;
		ft_putstr(", ksy:");
		ft_putnbr(100 * env->constante2test);
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_v)
	{
		env->constante2test += 0.05;
		ft_putstr(", ksy:");
		ft_putnbr(100 * env->constante2test);
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_n)
	{
		env->objs[env->curr_obj].p *= 11.00 / 10.00;
		ft_putstr(", rugos:");
		ft_putnbr(100 * env->objs[env->curr_obj].p);
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_b)
	{
		env->objs[env->curr_obj].p *= (env->objs[env->curr_obj].p > 0.1)
									? 10.00 / 11.00 : 1.0;
		ft_putstr(", rugos:");
		ft_putnbr(100 * env->objs[env->curr_obj].p);
	}
	else
		return (0);
	return (1);
}

static int		events_obj_mod(t_env *env, unsigned int sym, t_obj *obj)
{
	if ((sym == SDLK_1 || sym == SDLK_2 || sym == SDLK_3 || sym == SDLK_4))
		update_and_copy_a(env, sym);
	else if (sym == SDLK_BACKSPACE && env->curr_obj >= 0)
		update_and_copy_r(env, env->curr_obj);
	else if (sym == SDLK_BACKSLASH)
	{
		if (env->curr_obj >= 0)
			obj->col = get_rand();
		else if (env->curr_obj == -2)
			env->lums[env->curr_lum].col = get_rand();
	}
	else if (sym == SDLK_MINUS && env->curr_obj != -1)
	{
		obj->radius -= (obj->radius >= 0) ? 10 : 0;
	}
	else if (sym == SDLK_EQUALS && env->curr_obj != -1)
		obj->radius += 10;
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
		init_scene(env);
	}
	else if (event.type == SDL_KEYDOWN && sym == SDLK_KP_MINUS)
		env->flou = (env->flou * 16 > WIN_Y) ? env->flou : env->flou * 2;
	else if (event.type == SDL_KEYDOWN && sym == SDLK_KP_PLUS)
		env->flou /= (env->flou == 0.125) ? 1 : 2;
	else if (event.type == SDL_KEYDOWN && sym == SDLK_END)
		scene_generator(env);
	else
		return (0);
	return (1);
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
		cam->vcam = vect_mult(cam->vcam, 1.0 / vect_norm(cam->vcam));
		cam->v2cam = vect_mult(cam->v2cam, 1.0 / vect_norm(cam->v2cam));
		cam->v3cam = vect_mult(cam->v3cam, 1.0 / vect_norm(cam->v3cam));
		if (events_random(env, sym, event) || events_sel(env, event, sym))
			;
		else if (event.type == SDL_KEYDOWN && (events_obj_mod(env, sym, obj)
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

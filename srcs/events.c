/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 02:48:18 by tjeanner          #+#    #+#             */
/*   Updated: 2018/01/28 01:41:06 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		rotate_events(t_env *env, SDL_Event event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q)
	{
		env->cams[0].vcam.x -= 0.1;
		env->cams[0].vcam = vect_mult(env->cams[0].vcam, 1 / vect_norm(env->cams[0].vcam));
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_e)
	{
		env->cams[0].vcam.x += 0.1;
		env->cams[0].vcam = vect_mult(env->cams[0].vcam, 1 / vect_norm(env->cams[0].vcam));
	}
	else
		return (0);
	return (1);
}

static int		move_events(t_env *env, SDL_Event event)
{
	if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			|| event.type == SDL_QUIT)
	{
		ft_putendl("yolo");
		env->state = 1;
		return (0);
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_w)
		env->cams[0].pos_cam = vect_add(env->cams[0].pos_cam, vect_mult(env->cams[0].v2cam, 50));
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
		env->cams[0].pos_cam = vect_add(env->cams[0].pos_cam, vect_mult(env->cams[0].v2cam, -50));
	else if (event.type == SDL_MOUSEWHEEL && event.wheel.y != 0)
	{
		env->cams[0].pos_cam = vect_add(env->cams[0].pos_cam,
				vect_mult(env->cams[0].vcam, -10 * event.wheel.y));
		event.wheel.y = 0;
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)
		env->cams[0].pos_cam = vect_add(env->cams[0].pos_cam, vect_mult(env->cams[0].vcam, 100));
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
		env->cams[0].pos_cam = vect_add(env->cams[0].pos_cam, vect_mult(env->cams[0].vcam, -100));
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a)
	{
		env->cams[0].v3cam = vect_prod(env->cams[0].vcam, env->cams[0].v2cam);
		env->cams[0].pos_cam = vect_add(env->cams[0].pos_cam, vect_mult(env->cams[0].v3cam, 50));
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d)
	{
		env->cams[0].v3cam = vect_prod(env->cams[0].vcam, env->cams[0].v2cam);
		env->cams[0].pos_cam = vect_add(env->cams[0].pos_cam, vect_mult(env->cams[0].v3cam, -50));
	}
	else if (!rotate_events(env, event))
		return (0);
	return (1);
}

int				events(t_env *env)
{
	SDL_Event	event;

	if (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r)
			env->lums[0].pos_lum.z += (env->lums[0].pos_lum.z > 1000) ? 0 : 100;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_f)
			env->lums[0].pos_lum.z -= (env->lums[0].pos_lum.z < -5000) ? 0 : 100;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_c)
			env->lums[0].pos_lum.x -= (env->lums[0].pos_lum.x < -800) ? 0 : 100;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_v)
			env->lums[0].pos_lum.x += (env->lums[0].pos_lum.x > 800) ? 0 : 100;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_t)
			env->lums[0].pos_lum.y += 100;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_g)
			env->lums[0].pos_lum.y -= 100;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_m)
		{
			ft_memdel((void **)&env->objs);
			ft_memdel((void **)&env->cams);
			ft_memdel((void **)&env->lums);
			init_scene(env);
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_KP_MINUS)
		{
			env->flou = (env->flou * 16 > WIN_Y) ? env->flou : env->flou * 2;
			ft_putnbr(which_pow(env->flou, 2));
			ft_putchar('\n');
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_KP_PLUS)
		{
			env->flou /= (env->flou == 0.125) ? 1 : 2;
			ft_putnbr(which_pow(env->flou, 2));
			ft_putchar('\n');
		}
		else if (!move_events(env, event))
			return (0);
		rays(env);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 02:48:18 by tjeanner          #+#    #+#             */
/*   Updated: 2018/01/24 01:12:37 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		rotate_events(t_env *env, SDL_Event event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q)
	{
		env->vcam.x -= 0.1;
		env->vcam = vect_mult(env->vcam, 1 / vect_norm(env->vcam));
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_e)
	{
		env->vcam.x += 0.1;
		env->vcam = vect_mult(env->vcam, 1 / vect_norm(env->vcam));
	}
}

static void		move_events(t_env *env, SDL_Event event)
{
	if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			|| event.type == SDL_QUIT)
	{
		ft_putendl("yolo");
		env->state = 1;
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_w)
		env->pos_cam = vect_add(env->pos_cam, vect_mult(env->v2cam, 50));
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
		env->pos_cam = vect_add(env->pos_cam, vect_mult(env->v2cam, -50));
	else if (event.type == SDL_MOUSEWHEEL && event.wheel.y != 0)
	{
		env->pos_cam = vect_add(env->pos_cam,
				vect_mult(env->vcam, -10 * event.wheel.y));
		event.wheel.y = 0;
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)
		env->pos_cam = vect_add(env->pos_cam, vect_mult(env->vcam, 100));
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
		env->pos_cam = vect_add(env->pos_cam, vect_mult(env->vcam, -100));
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a)
	{
		env->v3cam = vect_prod(env->vcam, env->v2cam);
		env->pos_cam = vect_add(env->pos_cam, vect_mult(env->v3cam, 50));
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d)
	{
		env->v3cam = vect_prod(env->vcam, env->v2cam);
		env->pos_cam = vect_add(env->pos_cam, vect_mult(env->v3cam, -50));
	}
	else
		rotate_events(env, event);
}

void			events(t_env *env)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r)
			env->pos_lum.z += (env->pos_lum.z > 1000) ? 0 : 100;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_f)
			env->pos_lum.z -= (env->pos_lum.z < -5000) ? 0 : 100;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_c)
			env->pos_lum.x -= (env->pos_lum.x < -800) ? 0 : 100;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_v)
			env->pos_lum.x += (env->pos_lum.x > 800) ? 0 : 100;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_t)
		{
			env->flou = (env->flou * 16 > WIN_Y) ? env->flou : env->flou * 2;
			ft_putnbr(which_pow(env->flou, 2));
			ft_putchar('\n');
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_g)
		{
			env->flou /= (env->flou == 0.125) ? 1 : 2;
			ft_putnbr(which_pow(env->flou, 2));
			ft_putchar('\n');
		}
		else
			move_events(env, event);
	}
}

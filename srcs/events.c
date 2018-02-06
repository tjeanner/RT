/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 02:48:18 by tjeanner          #+#    #+#             */
/*   Updated: 2018/02/05 12:57:25 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		rotate_events(t_env *env, SDL_Event event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q)
	{
		env->cams[env->curr_cam].vcam.x -= 0.1;
		env->cams[env->curr_cam].vcam = vect_mult(env->cams[env->curr_cam].vcam, 1 / vect_norm(env->cams[env->curr_cam].vcam));
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_e)
	{
		env->cams[env->curr_cam].vcam.x += 0.1;
		env->cams[env->curr_cam].vcam = vect_mult(env->cams[env->curr_cam].vcam, 1 / vect_norm(env->cams[env->curr_cam].vcam));
	}
	else
		return (0);
	return (1);
}

static int		movect_events(t_env *env, SDL_Event event)
{
	if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			|| event.type == SDL_QUIT)
	{
		ft_putendl("yolo");
		env->state = 1;
		return (0);
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_w)
	{
		if (env->curr_obj == -1)
			env->cams[env->curr_cam].pos_cam = vect_add(env->cams[env->curr_cam].pos_cam, vect_mult(env->cams[env->curr_cam].v2cam, 50));
		else
			env->objs[env->curr_obj].o = vect_add(env->objs[env->curr_obj].o, vect_mult(env->cams[env->curr_cam].v2cam, 50));
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
	{
		if (env->curr_obj == -1)
			env->cams[env->curr_cam].pos_cam = vect_add(env->cams[env->curr_cam].pos_cam, vect_mult(env->cams[env->curr_cam].v2cam, -50));
		else
			env->objs[env->curr_obj].o = vect_add(env->objs[env->curr_obj].o, vect_mult(env->cams[env->curr_cam].v2cam, -50));
	}
	else if (event.type == SDL_MOUSEWHEEL && event.wheel.y != 0)
	{
		if (env->curr_obj == -1)
			env->cams[env->curr_cam].pos_cam = vect_add(env->cams[env->curr_cam].pos_cam,
				vect_mult(env->cams[env->curr_cam].vcam, -10 * event.wheel.y));
		else
			env->objs[env->curr_obj].o = vect_add(env->objs[env->curr_obj].o, vect_mult(env->cams[env->curr_cam].vcam, -10 * event.wheel.y));
		event.wheel.y = 0;
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
	{
		env->mousex = event.button.x;
		event.button.x = 0;
		env->mousey = event.button.y;
		event.button.y = 0;
		env->mouse_select = 1;
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_NUMLOCKCLEAR)
	{
		env->curr_obj = -1;
		env->mouse_select = 0;
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
		env->cams[env->curr_cam].pos_cam = vect_add(env->cams[env->curr_cam].pos_cam, vect_mult(env->cams[env->curr_cam].vcam, -100));
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a)
	{
		env->cams[env->curr_cam].v3cam = vect_prod(env->cams[env->curr_cam].vcam, env->cams[env->curr_cam].v2cam);
		env->cams[env->curr_cam].pos_cam = vect_add(env->cams[env->curr_cam].pos_cam, vect_mult(env->cams[env->curr_cam].v3cam, 50));
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d)
	{
		env->cams[env->curr_cam].v3cam = vect_prod(env->cams[env->curr_cam].vcam, env->cams[env->curr_cam].v2cam);
		env->cams[env->curr_cam].pos_cam = vect_add(env->cams[env->curr_cam].pos_cam, vect_mult(env->cams[env->curr_cam].v3cam, -50));
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
			env->lums[0].pos_lum.z += 100;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_f)
			env->lums[0].pos_lum.z -= 100;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_c)
			env->lums[0].pos_lum.x -= 100;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_v)
			env->lums[0].pos_lum.x += 100;
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
		else if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_KP_0 || event.key.keysym.sym == SDLK_KP_1 || event.key.keysym.sym == SDLK_KP_2 || event.key.keysym.sym == SDLK_KP_3 || event.key.keysym.sym == SDLK_KP_4 || event.key.keysym.sym == SDLK_KP_5 || event.key.keysym.sym == SDLK_KP_6 || event.key.keysym.sym == SDLK_KP_7 || event.key.keysym.sym == SDLK_KP_8 || event.key.keysym.sym == SDLK_KP_9))
		{
			if (event.key.keysym.sym == SDLK_KP_0 && env->curr_cam != 0)
				env->curr_cam = 0;
			else if (event.key.keysym.sym == SDLK_KP_1 && env->nb_cam > 1 && env->curr_cam != 1)
				env->curr_cam = 1;
			else if (event.key.keysym.sym == SDLK_KP_2 && env->nb_cam > 2 && env->curr_cam != 2)
				env->curr_cam = 2;
			else if (event.key.keysym.sym == SDLK_KP_3 && env->nb_cam > 3 && env->curr_cam != 3)
				env->curr_cam = 3;
			else if (event.key.keysym.sym == SDLK_KP_4 && env->nb_cam > 4 && env->curr_cam != 4)
				env->curr_cam = 4;
			else if (event.key.keysym.sym == SDLK_KP_5 && env->nb_cam > 5 && env->curr_cam != 5)
				env->curr_cam = 5;
			else if (event.key.keysym.sym == SDLK_KP_6 && env->nb_cam > 6 && env->curr_cam != 6)
				env->curr_cam = 6;
			else if (event.key.keysym.sym == SDLK_KP_7 && env->nb_cam > 7 && env->curr_cam != 7)
				env->curr_cam = 7;
			else if (event.key.keysym.sym == SDLK_KP_8 && env->nb_cam > 8 && env->curr_cam != 8)
				env->curr_cam = 8;
			else if (event.key.keysym.sym == SDLK_KP_9 && env->nb_cam > 9 && env->curr_cam != 9)
				env->curr_cam = 9;
			else
				return (0);
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_KP_MINUS)
			env->flou = (env->flou * 16 > WIN_Y) ? env->flou : env->flou * 2;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_KP_PLUS)
			env->flou /= (env->flou == 0.125) ? 1 : 2;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
			env->curr_obj = (env->curr_obj < env->nb_obj - 1) ? env->curr_obj + 1 : 0;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_i)
			env->objs[env->curr_obj].norm = rotation(env->objs[env->curr_obj].norm, (t_v){1, 0, 0}, 1);
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_k)
			env->objs[env->curr_obj].norm = rotation(env->objs[env->curr_obj].norm, (t_v){1, 0, 0}, -1);
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_j)
			env->objs[env->curr_obj].norm = rotation(env->objs[env->curr_obj].norm, (t_v){0, 1, 0}, 1);
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_l)
			env->objs[env->curr_obj].norm = rotation(env->objs[env->curr_obj].norm, (t_v){0, 1, 0}, -1);
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_u)
			env->objs[env->curr_obj].norm = rotation(env->objs[env->curr_obj].norm, (t_v){0, 0, 1}, 1);
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_o)
			env->objs[env->curr_obj].norm = rotation(env->objs[env->curr_obj].norm, (t_v){0, 0, 1}, -1);
		else if (!move_events(env, event))
			return (0);
		rays(env);
	}
	return (1);
}

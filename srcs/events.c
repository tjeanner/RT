/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 02:48:18 by tjeanner          #+#    #+#             */
/*   Updated: 2018/02/13 18:28:36 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
	{
		if (env->curr_obj == -1)
			env->cams[env->curr_cam].pos_cam = vect_add(env->cams[env->curr_cam].pos_cam, vect_mult(env->cams[env->curr_cam].v2cam, 50.0));
		else
			env->objs[env->curr_obj].o = vect_add(env->objs[env->curr_obj].o, vect_mult((t_v){0, 1, 0}, 50.0));
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_z)
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
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_y)
	{
	//	env->constante2test -= 0.05;
		ft_putstr("x:");
		ft_putnbr(100 * env->objs[0].norm.x);
		ft_putstr("y:");
		ft_putnbr(100 * env->objs[0].norm.y);
		ft_putstr("z:");
		ft_putnbr(100 * env->objs[0].norm.z);
		ft_putstr("z:");
	}
//	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_h)
//	{
//		env->constante2test += 0.05;
//		ft_putstr(", ksy:");
//		ft_putnbr(100 * env->constante2test);
//	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_n)
	{
		env->objs[env->curr_obj].p *= 11.00 / 10.00;
		ft_putstr(", rugos:");
		ft_putnbr(100 * env->objs[env->curr_obj].p);
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_b)
	{
		env->objs[env->curr_obj].p *= (env->objs[env->curr_obj].p > 0.1) ? 10.00 / 11.00 : 1.0;
		ft_putstr(", rugos:");
		ft_putnbr(100 * env->objs[env->curr_obj].p);
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
	{
		if (env->curr_obj == -1)
			env->cams[env->curr_cam].pos_cam = vect_add(env->cams[env->curr_cam].pos_cam, vect_mult(env->cams[env->curr_cam].v2cam, -50.0));
		else
			env->objs[env->curr_obj].o = vect_add(env->objs[env->curr_obj].o, vect_mult((t_v){0, 1, 0}, -50.0));
	}
	else if (event.type == SDL_MOUSEWHEEL && event.wheel.y != 0)
	{
		if (env->curr_obj == -1)
			env->cams[env->curr_cam].pos_cam = vect_add(env->cams[env->curr_cam].pos_cam,
				vect_mult(env->cams[env->curr_cam].vcam, -50.0 * event.wheel.y));
		else
			env->objs[env->curr_obj].o = vect_add(env->objs[env->curr_obj].o, vect_mult(env->cams[env->curr_cam].vcam, -50.0 * event.wheel.y));
		event.wheel.y = 0;
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
	{
		init_ray(env, event.button.x, event.button.y);
		env->curr_obj = which_obj_col(env);
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_NUMLOCKCLEAR)
		env->curr_obj = -1;
	else if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_q))
	{
		if (env->curr_obj == -1)
			env->cams[env->curr_cam].pos_cam = vect_add(env->cams[env->curr_cam].pos_cam, vect_mult(env->cams[env->curr_cam].vcam, 50.0));
		else
			env->objs[env->curr_obj].o = vect_add(env->objs[env->curr_obj].o, vect_mult((t_v){0, 0, 1}, 50.0));
	}
	else if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_e))
	{
		if (env->curr_obj == -1)
			env->cams[env->curr_cam].pos_cam = vect_add(env->cams[env->curr_cam].pos_cam, vect_mult(env->cams[env->curr_cam].vcam, -50.0));
		else
			env->objs[env->curr_obj].o = vect_add(env->objs[env->curr_obj].o, vect_mult((t_v){0, 0, 1}, -50.0));
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a)
	{
		if (env->curr_obj == -1)
		{
			env->cams[env->curr_cam].v3cam = vect_prod(env->cams[env->curr_cam].vcam, env->cams[env->curr_cam].v2cam);
			env->cams[env->curr_cam].pos_cam = vect_add(env->cams[env->curr_cam].pos_cam, vect_mult(env->cams[env->curr_cam].v3cam, 50.0));
		}
		else
			env->objs[env->curr_obj].o = vect_add(env->objs[env->curr_obj].o, vect_mult((t_v){1, 0, 0}, -50.0));
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d)
	{
		if (env->curr_obj == -1)
		{
			env->cams[env->curr_cam].v3cam = vect_prod(env->cams[env->curr_cam].vcam, env->cams[env->curr_cam].v2cam);
			env->cams[env->curr_cam].pos_cam = vect_add(env->cams[env->curr_cam].pos_cam, vect_mult(env->cams[env->curr_cam].v3cam, -50.0));
		}
		else
			env->objs[env->curr_obj].o = vect_add(env->objs[env->curr_obj].o, vect_mult((t_v){1, 0, 0}, 50.0));
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_MINUS && env->curr_obj != -1)
	{
		if (env->curr_obj >= 0)
			env->objs[env->curr_obj].radius -= (env->objs[env->curr_obj].radius >= 0) ? 10 : 0;
		else
			env->lums[env->curr_lum].coef -= 0.005;
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_EQUALS && env->curr_obj != -1)
	{
		if (env->curr_obj >= 0)
			env->objs[env->curr_obj].radius += 10;
		else
			env->lums[env->curr_lum].coef += 0.005;
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_h)
	{
		env->curr_obj = (env->curr_obj >= 0) ? -2 : env->curr_obj + 1;
		ft_putnbr(env->curr_obj);
		ft_putstr(", ");
	}
	else
		return (0);
	return (1);
}

int				events(t_env *env)
{
	SDL_Event	event;

	if (SDL_PollEvent(&event) != 0)
	{
		env->cams[env->curr_cam].vcam = vect_mult(env->cams[env->curr_cam].vcam, 1.0 / vect_norm(env->cams[env->curr_cam].vcam));
		env->cams[env->curr_cam].v2cam = vect_mult(env->cams[env->curr_cam].v2cam, 1.0 / vect_norm(env->cams[env->curr_cam].v2cam));
		env->cams[env->curr_cam].v3cam = vect_mult(env->cams[env->curr_cam].v3cam, 1.0 / vect_norm(env->cams[env->curr_cam].v3cam));
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r)
			env->lums[env->curr_lum].pos_lum.z += 50;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_f)
			env->lums[env->curr_lum].pos_lum.z -= 50;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_c)
			env->lums[env->curr_lum].pos_lum.x -= 50;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_v)
			env->lums[env->curr_lum].pos_lum.x += 50;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_t)
			env->lums[env->curr_lum].pos_lum.y += 50;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_g)
			env->lums[env->curr_lum].pos_lum.y -= 50;
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
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SEMICOLON)
		{
			env->curr_lum = (env->curr_lum < env->nb_lum - 1) ? env->curr_lum + 1 : 0;
			ft_putnbr(env->curr_lum);
			ft_putnbr(env->nb_lum);
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_i)
		{
			if (env->curr_obj == -1)
			{
				env->cams[env->curr_cam].v3cam = vect_prod(env->cams[env->curr_cam].vcam, env->cams[env->curr_cam].v2cam);
				env->cams[env->curr_cam].v3cam = vect_mult(env->cams[env->curr_cam].v3cam, vect_norm(env->cams[env->curr_cam].v3cam));
				env->cams[env->curr_cam].vcam = rotation(env->cams[env->curr_cam].vcam, env->cams[env->curr_cam].v3cam, 1.0);
				env->cams[env->curr_cam].vcam = vect_mult(env->cams[env->curr_cam].vcam, vect_norm(env->cams[env->curr_cam].vcam));
				env->cams[env->curr_cam].v2cam = vect_prod(env->cams[env->curr_cam].v3cam, env->cams[env->curr_cam].vcam);
				env->cams[env->curr_cam].v2cam = vect_mult(env->cams[env->curr_cam].v2cam, vect_norm(env->cams[env->curr_cam].v2cam));
			}
			else
				env->objs[env->curr_obj].norm = rotation(env->objs[env->curr_obj].norm, (t_v){1, 0, 0}, 1);
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_k)
		{
			if (env->curr_obj == -1)
			{
				env->cams[env->curr_cam].v3cam = vect_prod(env->cams[env->curr_cam].vcam, env->cams[env->curr_cam].v2cam);
				env->cams[env->curr_cam].v3cam = vect_mult(env->cams[env->curr_cam].v3cam, vect_norm(env->cams[env->curr_cam].v3cam));
				env->cams[env->curr_cam].vcam = rotation(env->cams[env->curr_cam].vcam, env->cams[env->curr_cam].v3cam, -1.0);
				env->cams[env->curr_cam].vcam = vect_mult(env->cams[env->curr_cam].vcam, vect_norm(env->cams[env->curr_cam].vcam));
				env->cams[env->curr_cam].v2cam = vect_prod(env->cams[env->curr_cam].v3cam, env->cams[env->curr_cam].vcam);
				env->cams[env->curr_cam].v2cam = vect_mult(env->cams[env->curr_cam].v2cam, vect_norm(env->cams[env->curr_cam].v2cam));
			}
			else
				env->objs[env->curr_obj].norm = rotation(env->objs[env->curr_obj].norm, (t_v){1, 0, 0}, -1);
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_j)
		{
			if (env->curr_obj == -1)
			{
				env->cams[env->curr_cam].vcam = rotation(env->cams[env->curr_cam].vcam, env->cams[env->curr_cam].v2cam, -1);
				env->cams[env->curr_cam].vcam = vect_mult(env->cams[env->curr_cam].vcam, vect_norm(env->cams[env->curr_cam].vcam));
				env->cams[env->curr_cam].v3cam = vect_prod(env->cams[env->curr_cam].v2cam, env->cams[env->curr_cam].vcam);
				env->cams[env->curr_cam].v3cam = vect_mult(env->cams[env->curr_cam].v3cam, vect_norm(env->cams[env->curr_cam].v3cam));
			}
			else
				env->objs[env->curr_obj].norm = rotation(env->objs[env->curr_obj].norm, (t_v){0, 1, 0}, 1);
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_l)
		{
			if (env->curr_obj == -1)
			{
				env->cams[env->curr_cam].vcam = rotation(env->cams[env->curr_cam].vcam, env->cams[env->curr_cam].v2cam, 1);
				env->cams[env->curr_cam].vcam = vect_mult(env->cams[env->curr_cam].vcam, vect_norm(env->cams[env->curr_cam].vcam));
				env->cams[env->curr_cam].v3cam = vect_prod(env->cams[env->curr_cam].v2cam, env->cams[env->curr_cam].vcam);
				env->cams[env->curr_cam].v3cam = vect_mult(env->cams[env->curr_cam].v3cam, vect_norm(env->cams[env->curr_cam].v3cam));
			}
			else
				env->objs[env->curr_obj].norm = rotation(env->objs[env->curr_obj].norm, (t_v){0, 1, 0}, -1);
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_u)
		{
			if (env->curr_obj == -1)
			{
				env->cams[env->curr_cam].v2cam = rotation(env->cams[env->curr_cam].v2cam, env->cams[env->curr_cam].vcam, 1);
				env->cams[env->curr_cam].v2cam = vect_mult(env->cams[env->curr_cam].v2cam, vect_norm(env->cams[env->curr_cam].v2cam));
				env->cams[env->curr_cam].v3cam = vect_prod(env->cams[env->curr_cam].v2cam, env->cams[env->curr_cam].vcam);
				env->cams[env->curr_cam].v3cam = vect_mult(env->cams[env->curr_cam].v3cam, vect_norm(env->cams[env->curr_cam].v3cam));
			}
			else
				env->objs[env->curr_obj].norm = rotation(env->objs[env->curr_obj].norm, (t_v){0, 0, 1}, 1);
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_o)
		{
			if (env->curr_obj == -1)
			{
				env->cams[env->curr_cam].v2cam = rotation(env->cams[env->curr_cam].v2cam, env->cams[env->curr_cam].vcam, -1);
				env->cams[env->curr_cam].v2cam = vect_mult(env->cams[env->curr_cam].v2cam, vect_norm(env->cams[env->curr_cam].v2cam));
				env->cams[env->curr_cam].v3cam = vect_prod(env->cams[env->curr_cam].v2cam, env->cams[env->curr_cam].vcam);
				env->cams[env->curr_cam].v3cam = vect_mult(env->cams[env->curr_cam].v3cam, vect_norm(env->cams[env->curr_cam].v3cam));
			}
			else
				env->objs[env->curr_obj].norm = rotation(env->objs[env->curr_obj].norm, (t_v){0, 0, 1}, -1);
		}
		else if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_1 || event.key.keysym.sym == SDLK_2
			|| event.key.keysym.sym == SDLK_3 || event.key.keysym.sym == SDLK_4))
			update_and_copy_a(env, event.key.keysym.sym);
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && env->curr_obj >= 0)
			update_and_copy_r(env, env->curr_obj);
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSLASH)
		{
			if (env->curr_obj >= 0) 
				env->objs[env->curr_obj].col = get_rand();
			else if (env->curr_obj == -2)
				env->lums[env->curr_lum].col = get_rand();
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_KP_CLEAR)
			env->curr_obj = -1;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_END)
			scene_generator(env);
		else if (!move_events(env, event))
			return (0);
		rays(env);
	}
	return (1);
}

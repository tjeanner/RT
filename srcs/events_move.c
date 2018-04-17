/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 07:30:16 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/15 18:23:19 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	lum_move(t_env *env, unsigned int sym)
{
	if (sym == SDLK_r)
		env->lums[env->curr_lum].pos.z += 50;
	else if (sym == SDLK_y)
		env->lums[env->curr_lum].pos.z -= 50;
	else if (sym == SDLK_f)
		env->lums[env->curr_lum].pos.x -= 50;
	else if (sym == SDLK_h)
		env->lums[env->curr_lum].pos.x += 50;
	else if (sym == SDLK_t)
		env->lums[env->curr_lum].pos.y += 50;
	else if (sym == SDLK_g)
		env->lums[env->curr_lum].pos.y -= 50;
	else
		return (0);
	return (1);
}

void	mouse_move(t_env *env, SDL_Event event, t_cam *cam, t_obj *obj)
{
	if (env->curr_obj == -1)
		cam->pos = vect_add(cam->pos,
			vect_mult(cam->vcam, -50.0 * event.wheel.y));
	else
		obj->o = vect_add(obj->o, vect_mult(cam->vcam, -50.0 * event.wheel.y));
	event.wheel.y = 0;
}

static int	events_move2(t_env *env, unsigned int sym, t_cam *cam, t_obj *obj)
{
	if (env->curr_obj == -1 && sym == SDLK_a)
	{
		cam->v3cam = vect_prod(cam->vcam, cam->v2cam);
		cam->pos = vect_add(cam->pos, vect_mult(cam->v3cam, 50.0));
	}
	else if (env->curr_obj >= -1 && sym == SDLK_a)
		obj->o = vect_add(obj->o, vect_mult((t_v){1, 0, 0}, -50.0));
	else if (env->curr_obj == -1 && sym == SDLK_d)
	{
		cam->v3cam = vect_prod(cam->vcam, cam->v2cam);
		cam->pos = vect_add(cam->pos, vect_mult(cam->v3cam, -50.0));
	}
	else if (env->curr_obj >= -1 && sym == SDLK_d)
		obj->o = vect_add(obj->o, vect_mult((t_v){1, 0, 0}, 50.0));
	else if (lum_move(env, sym))
		;
	else
		return (0);
	return (1);
}

int			events_move(t_env *env, unsigned int sym, t_cam *cam, t_obj *obj)
{
	if (env->curr_obj == -1 && (sym == SDLK_UP || sym == SDLK_q))
		cam->pos = vect_add(cam->pos, vect_mult(cam->vcam, 50.0));
	else if (env->curr_obj >= -1 && (sym == SDLK_UP || sym == SDLK_q))
		obj->o = vect_add(obj->o, vect_mult((t_v){0, 0, 1}, 50.0));
	else if (env->curr_obj == -1 && (sym == SDLK_DOWN || sym == SDLK_e))
		cam->pos = vect_add(cam->pos, vect_mult(cam->vcam, -50.0));
	else if (env->curr_obj >= -1 && (sym == SDLK_DOWN || sym == SDLK_e))
		obj->o = vect_add(obj->o, vect_mult((t_v){0, 0, 1}, -50.0));
	else if (env->curr_obj == -1 && sym == SDLK_w)
		cam->pos = vect_add(cam->pos, vect_mult(cam->v2cam, 50.0));
	else if (env->curr_obj >= -1 && sym == SDLK_w)
		obj->o = vect_add(obj->o, vect_mult((t_v){0, 1, 0}, 50.0));
	else if (env->curr_obj == -1 && sym == SDLK_s)
		cam->pos = vect_add(cam->pos, vect_mult(cam->v2cam, -50.0));
	else if (env->curr_obj >= -1 && sym == SDLK_s)
		obj->o = vect_add(obj->o, vect_mult((t_v){0, 1, 0}, -50.0));
	else
		return (events_move2(env, sym, cam, obj));
	return (1);
}

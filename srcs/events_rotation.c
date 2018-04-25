/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 06:35:34 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/25 11:14:36 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
/*
static void		cam_rotation_x(t_env *env, float angle)
{
//	env->cams.cam[env->cams.curr].v3cam = vect_prod(env->cams.cam[env->cams.curr].vcam,
//						env->cams.cam[env->cams.curr].v2cam);
//	env->cams.cam[env->cams.curr].v3cam = vect_mult(env->cams.cam[env->cams.curr].v3cam,
//						get_vect_norm(env->cams.cam[env->cams.curr].v3cam));
	env->cams.cam[env->cams.curr].vcam = rotation(env->cams.cam[env->cams.curr].vcam,
						env->cams.cam[env->cams.curr].v3cam, angle);
	env->cams.cam[env->cams.curr].vcam = vect_mult(env->cams.cam[env->cams.curr].vcam,
						get_vect_norm(env->cams.cam[env->cams.curr].vcam));
	env->cams.cam[env->cams.curr].v2cam = vect_prod(env->cams.cam[env->cams.curr].v3cam,
						env->cams.cam[env->cams.curr].vcam);
	env->cams.cam[env->cams.curr].v2cam = vect_mult(env->cams.cam[env->cams.curr].v2cam,
						get_vect_norm(env->cams.cam[env->cams.curr].v2cam));
}*/

static void		cam_rotation_x(t_env *env, float angle)
{
	env->cams.cam[env->cams.curr].vcam = vect_norm(rotation(
		env->cams.cam[env->cams.curr].vcam, env->cams.cam[env->cams.curr].v3cam, angle));
	env->cams.cam[env->cams.curr].v2cam = vect_norm(vect_prod(
		env->cams.cam[env->cams.curr].v3cam, env->cams.cam[env->cams.curr].vcam));
}

static void		cam_rotation_y(t_env *env, float angle)
{
	env->cams.cam[env->cams.curr].vcam = vect_norm(rotation(
		env->cams.cam[env->cams.curr].vcam, env->cams.cam[env->cams.curr].v2cam, angle));
	env->cams.cam[env->cams.curr].v3cam = vect_norm(vect_inv(vect_prod(
		env->cams.cam[env->cams.curr].v2cam, env->cams.cam[env->cams.curr].vcam)));
}

static void		cam_rotation_z(t_env *env, float angle)
{
	env->cams.cam[env->cams.curr].v2cam = vect_norm(rotation(
		env->cams.cam[env->cams.curr].v2cam, env->cams.cam[env->cams.curr].vcam, angle));
	env->cams.cam[env->cams.curr].v3cam = vect_norm(vect_inv(vect_prod(
		env->cams.cam[env->cams.curr].v2cam, env->cams.cam[env->cams.curr].vcam)));
}

static int		events_rotation2(t_env *env, unsigned int sym, t_v *norm)
{
	if (sym == SDLK_i && env->objs.curr == -1)
		cam_rotation_x(env, 1.0);
	else if (sym == SDLK_i && env->objs.curr >= -1)
		*norm = rotation(*norm, (t_v){1, 0, 0}, 1);
	else if (sym == SDLK_k && env->objs.curr == -1)
		cam_rotation_x(env, -1.0);
	else if (sym == SDLK_k && env->objs.curr >= -1)
		*norm = rotation(*norm, (t_v){1, 0, 0}, -1);
	else if (sym == SDLK_j && env->objs.curr == -1)
		cam_rotation_y(env, -1.0);
	else if (sym == SDLK_j && env->objs.curr >= -1)
		*norm = rotation(*norm, (t_v){0, 1, 0}, 1);
	else
		return (0);
	return (1);
}

int				events_rotation(t_env *env, unsigned int sym, t_v *norm)
{
	if (events_rotation2(env, sym, norm))
		;
	else if (sym == SDLK_l && env->objs.curr == -1)
		cam_rotation_y(env, 1.0);
	else if (sym == SDLK_l && env->objs.curr >= -1)
		*norm = rotation(*norm, (t_v){0, 1, 0}, -1);
	else if (sym == SDLK_u && env->objs.curr == -1)
		cam_rotation_z(env, 1);
	else if (sym == SDLK_u && env->objs.curr >= -1)
		*norm = rotation(*norm, (t_v){0, 0, 1}, 1);
	else if (sym == SDLK_o && env->objs.curr == -1)
		cam_rotation_z(env, -1);
	else if (sym == SDLK_o && env->objs.curr >= -1)
		*norm = rotation(*norm, (t_v){0, 0, 1}, -1);
	else
		return (0);
	return (1);
}

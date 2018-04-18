/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 06:35:34 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/18 19:11:48 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
/*
static void		cam_rotation_x(t_env *env, float angle)
{
//	env->cams[env->curr_cam].v3cam = vect_prod(env->cams[env->curr_cam].vcam,
//						env->cams[env->curr_cam].v2cam);
//	env->cams[env->curr_cam].v3cam = vect_mult(env->cams[env->curr_cam].v3cam,
//						get_vect_norm(env->cams[env->curr_cam].v3cam));
	env->cams[env->curr_cam].vcam = rotation(env->cams[env->curr_cam].vcam,
						env->cams[env->curr_cam].v3cam, angle);
	env->cams[env->curr_cam].vcam = vect_mult(env->cams[env->curr_cam].vcam,
						get_vect_norm(env->cams[env->curr_cam].vcam));
	env->cams[env->curr_cam].v2cam = vect_prod(env->cams[env->curr_cam].v3cam,
						env->cams[env->curr_cam].vcam);
	env->cams[env->curr_cam].v2cam = vect_mult(env->cams[env->curr_cam].v2cam,
						get_vect_norm(env->cams[env->curr_cam].v2cam));
}*/

static void		cam_rotation_x(t_env *env, float angle)
{
	env->cams[env->curr_cam].vcam = vect_norm(rotation(
		env->cams[env->curr_cam].vcam, env->cams[env->curr_cam].v3cam, angle));
	env->cams[env->curr_cam].v2cam = vect_norm(vect_prod(
		env->cams[env->curr_cam].v3cam, env->cams[env->curr_cam].vcam));
}

static void		cam_rotation_y(t_env *env, float angle)
{
	env->cams[env->curr_cam].vcam = vect_norm(rotation(
		env->cams[env->curr_cam].vcam, env->cams[env->curr_cam].v2cam, angle));
	env->cams[env->curr_cam].v3cam = vect_norm(vect_inv(vect_prod(
		env->cams[env->curr_cam].v2cam, env->cams[env->curr_cam].vcam)));
}

static void		cam_rotation_z(t_env *env, float angle)
{
	env->cams[env->curr_cam].v2cam = vect_norm(rotation(
		env->cams[env->curr_cam].v2cam, env->cams[env->curr_cam].vcam, angle));
	env->cams[env->curr_cam].v3cam = vect_norm(vect_inv(vect_prod(
		env->cams[env->curr_cam].v2cam, env->cams[env->curr_cam].vcam)));
}

static int		events_rotation2(t_env *env, unsigned int sym, t_v *norm)
{
	if (sym == SDLK_i && env->curr_obj == -1)
		cam_rotation_x(env, 1.0);
	else if (sym == SDLK_i && env->curr_obj >= -1)
		*norm = rotation(*norm, (t_v){1, 0, 0}, 1);
	else if (sym == SDLK_k && env->curr_obj == -1)
		cam_rotation_x(env, -1.0);
	else if (sym == SDLK_k && env->curr_obj >= -1)
		*norm = rotation(*norm, (t_v){1, 0, 0}, -1);
	else if (sym == SDLK_j && env->curr_obj == -1)
		cam_rotation_y(env, -1.0);
	else if (sym == SDLK_j && env->curr_obj >= -1)
		*norm = rotation(*norm, (t_v){0, 1, 0}, 1);
	else
		return (0);
	return (1);
}

int				events_rotation(t_env *env, unsigned int sym, t_v *norm)
{
	if (events_rotation2(env, sym, norm))
		;
	else if (sym == SDLK_l && env->curr_obj == -1)
		cam_rotation_y(env, 1.0);
	else if (sym == SDLK_l && env->curr_obj >= -1)
		*norm = rotation(*norm, (t_v){0, 1, 0}, -1);
	else if (sym == SDLK_u && env->curr_obj == -1)
		cam_rotation_z(env, 1);
	else if (sym == SDLK_u && env->curr_obj >= -1)
		*norm = rotation(*norm, (t_v){0, 0, 1}, 1);
	else if (sym == SDLK_o && env->curr_obj == -1)
		cam_rotation_z(env, -1);
	else if (sym == SDLK_o && env->curr_obj >= -1)
		*norm = rotation(*norm, (t_v){0, 0, 1}, -1);
	else
		return (0);
	return (1);
}

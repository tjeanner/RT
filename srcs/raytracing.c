/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 19:12:29 by tjeanner          #+#    #+#             */
/*   Updated: 2018/04/07 17:07:21 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			init_ray(t_env *env, double x, double y)
{
	env->cams[env->curr_cam].v3cam = vect_inv(vect_prod(//////////////////////
	env->cams[env->curr_cam].vcam, env->cams[env->curr_cam].v2cam));////////////////
	env->init_rays.dir = vect_norm(vect_add(vect_mult(
	env->cams[env->curr_cam].vcam, DIST), vect_add(vect_mult(
	env->cams[env->curr_cam].v3cam, (x - WIN_X / 2.0) /
	get_vect_norm(env->cams[env->curr_cam].v3cam)),
		vect_mult(env->cams[env->curr_cam].v2cam, (WIN_Y / 2.0 - y) /
				get_vect_norm(env->cams[env->curr_cam].v2cam)))));
	env->init_rays.pos = env->cams[env->curr_cam].pos_cam;
	return (1);
}

int			which_obj_col(t_env *env)
{
	double	res;
	int		i;
	int		ob;

	i = -1;
	res = -1.0;
	while (++i < env->nb_obj && (env->objs[i].dist = -1.0) == -1.0)
	{
		if (env->col_fcts[ft_strchr(FCTS, env->objs[i].type) - FCTS](
					&env->init_rays, env->objs[i]) == 1 &&
				(env->init_rays.v1 > 0.0 || env->init_rays.v2 > 0.0))
			if (env->init_rays.v1 > 0.0 && env->init_rays.v2 > 0.0)
				env->objs[i].dist = (env->init_rays.v1 < env->init_rays.v2) ?
					env->init_rays.v1 : env->init_rays.v2;
			else
				env->objs[i].dist = (env->init_rays.v1 > 0.0) ?
					env->init_rays.v1 : env->init_rays.v2;
		else
			env->objs[i].dist = -1.0;
		if ((i == 0 || (env->objs[i].dist > 0.0 &&
			(res == -1.0 || res > env->objs[i].dist))) && (ob = i) == i)
			res = env->objs[i].dist;
	}
	return (ob = (res <= 0.0) ? -1 : ob);
}

void		rays(t_env *env)
{
	int		i;
	int		y;
	int		x;
	int		alias_coef;
	t_color	col;

	env->cams[env->curr_cam].v3cam = vect_inv(vect_prod(
		env->cams[env->curr_cam].vcam, env->cams[env->curr_cam].v2cam));
	y = 0;
	alias_coef = env->flou;
	while ((x = 0) == 0 && y < WIN_Y)
	{
		while ((i = 0) == 0 && x < WIN_X &&
				init_ray(env, x + alias_coef / 2, y + alias_coef / 2))
		{
			col = get_col(env, env->init_rays.dir);
			((int *)env->surf->pixels)[x + y * env->surf->w] = col.color;
			while (alias_coef > 1 && ++i < alias_coef * alias_coef)
				if (x + i % alias_coef < WIN_X && y + i / alias_coef < WIN_Y)
					((int *)env->surf->pixels)[x + i % alias_coef +
						(y + i / alias_coef) * env->surf->w] = col.color;
			x += alias_coef;
		}
		y += alias_coef;
	}
	set_filter(env);
	SDL_UpdateWindowSurface(env->win);
}

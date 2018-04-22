/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 19:12:29 by tjeanner          #+#    #+#             */
/*   Updated: 2018/04/22 06:38:41 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			init_ray(t_env *env, double x, double y)
{
	env->init_rays.dir = vect_norm(vect_add(vect_mult(
					env->cams[env->curr_cam].vcam, DIST), vect_add(vect_mult(
							vect_inv(env->cams[env->curr_cam].v3cam), (double)((x - WIN_X / 2.0) /
								get_vect_norm(env->cams[env->curr_cam].v3cam))),
						vect_mult(env->cams[env->curr_cam].v2cam, (double)((WIN_Y / 2.0 - y) /
								get_vect_norm(env->cams[env->curr_cam].v2cam))))));
	env->init_rays.pos = env->cams[env->curr_cam].pos;
	return (1);
}

t_v			get_norm(t_obj obj, t_ray init_rays, t_v pos_col)
{
	double	res;
	t_v		vect;

	if (obj.type == 's' || obj.type == 'p')
		vect = (obj.type == 'p') ? obj.norm : vect_sous(pos_col, obj.o);
	else if (obj.type == 'c')
	{
		vect = vect_sous(init_rays.pos, obj.o);
		res = vect_scal(init_rays.dir, vect_mult(obj.norm, obj.dist)) +
			vect_scal(vect, obj.norm);
		vect = vect_sous(vect_sous(pos_col, obj.o), vect_mult(obj.norm,
					res * (1.0 + pow(tan(obj.radius * TORAD), 2.0))));
	}
	else
	{
		res = vect_scal(obj.norm, vect_sous(pos_col, obj.o)) /
			vect_scal(obj.norm, obj.norm);
		vect = vect_sous(pos_col, vect_add(obj.o, vect_mult(obj.norm, res)));
	}
	return (vect = (obj.type == 'p' && vect_scal(vect, init_rays.dir) > 0.000)
			? vect_norm(vect_inv(vect)) : vect_norm(vect));
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
				(env->init_rays.d1 > 0.000 || env->init_rays.d2 > 0.000))
		{
			env->objs[i].dist = (env->init_rays.d1 > 0.0 && (env->init_rays.d1
< env->init_rays.d2 || env->init_rays.d2 < 0.0)) ? env->init_rays.d1 : env->objs[i].dist;
			env->objs[i].dist = (env->init_rays.d2 > 0.0 && (env->init_rays.d1
> env->init_rays.d2 || env->init_rays.d1 < 0.0)) ? env->init_rays.d2 : env->objs[i].dist;
		}
		if ((i == 0 || (env->objs[i].dist > 0.0 &&
		(res == -1.0 || res > env->objs[i].dist))) && (ob = i) == i)
			res = env->objs[i].dist;
	}
	while ((i = (i == env->nb_obj) ? 0 : i + 1) < env->nb_obj && res > 0.0)
		if (i != ob && env->objs[i].dist > 0.0 && env->objs[i].dist - res <
				0.50 && (env->objs[i].dist = ob) == ob)
			return (-1.0 * i - 2);
	return (ob = (res <= 0.0) ? -1 : ob);
}

t_color		get_lum(t_env *env, int obj, int lum)
{
	int		i;
	t_v		pos_col;
	t_v		col_2_lum;
	t_v		norm;
	double	res;
	t_ray	tutu;

	pos_col = vect_add(env->init_rays.pos, vect_mult(env->init_rays.dir,
				env->objs[obj].dist));
	norm = get_norm(env->objs[obj], env->init_rays, pos_col);
	norm = (env->objs[obj].type == 'p' && vect_scal(norm, env->init_rays.dir) > 0.0) ? vect_inv(norm) : norm;
	pos_col = vect_add(pos_col, vect_mult(norm, 0.00000001000));
	norm = get_norm(env->objs[obj], env->init_rays, pos_col);
	col_2_lum = vect_sous(env->lums[lum].pos, pos_col);
	res = get_vect_norm(col_2_lum);
	tutu.dir = vect_norm(col_2_lum);
	tutu.pos = pos_col;
	i = -1;
	while (++i < env->nb_obj && (tutu.d1 = -1.0) < 0)
		if ((tutu.d2 = -1.0) < 0 && env->col_fcts[ft_strchr(FCTS,
					env->objs[i].type) - FCTS](&tutu, env->objs[i]) == 1 &&
				(((tutu.d1 > 0.0 && tutu.d1 < res) || ((tutu.d2 > 0.0 && tutu.d2 < res)))))
			return (get_black());
	res = fmax(0.0, vect_scal(norm, tutu.dir));
	return (mult_color(env->objs[obj].col, res));
}

t_color		get_col(t_env *env, t_v ray_dir)
{
	int		obj;
	int		obj2;
	int		i;
	t_color	ambi_col;
	t_color	cols[3];
	t_v		tmp;
	t_v		tmp2;

	(void)ray_dir;
	if ((obj = which_obj_col(env)) == -1)
		return (get_black());
	if (env->amb_coef < 0.980)
	{
		if (obj < 0)
		{
			obj += 2;
			obj *= -1;
			obj2 = obj;
			obj = env->objs[obj2].dist;
			tmp = get_norm(env->objs[obj], env->init_rays, vect_add(env->init_rays.pos, vect_mult(ray_dir, env->objs[obj].dist)));
			tmp2 = get_norm(env->objs[obj2], env->init_rays, vect_add(env->init_rays.pos, vect_mult(ray_dir, env->objs[obj].dist)));
			env->init_rays.pos = vect_add(env->init_rays.pos, vect_mult(vect_add(tmp, tmp2), 0.500));
		}
		ambi_col = mult_color(env->objs[obj].col, env->amb_coef);
		cols[0] = get_black();
		cols[1] = get_black();
		i = -1;
		while (++i < env->nb_lum)
		{
				cols[1] = get_lum(env, obj, i);
				cols[0].c.r = fmin(255, cols[0].c.r + cols[1].c.r * env->lums[i].coef / env->coefs_sum);
				cols[0].c.g = fmin(255, cols[0].c.g + cols[1].c.g * env->lums[i].coef / env->coefs_sum);
				cols[0].c.b = fmin(255, cols[0].c.b + cols[1].c.b * env->lums[i].coef / env->coefs_sum);
		}
		env->init_rays.pos = vect_sous(env->init_rays.pos, vect_mult(vect_add(tmp, tmp2), 50.00));
		cols[0] = mult_color(cols[0], 1.000 - env->amb_coef);
		cols[0] = add_color(cols[0], ambi_col);
	}
	else
		cols[0] = env->objs[obj].col;
	return (cols[0]);
}

void		rays(t_env *env, SDL_Surface *surf)
{
	int		i;
	int		y;
	int		x;
	int		alias_coef;
	t_color	col[2];

	y = 0;
	alias_coef = env->flou;
	while ((x = 0) == 0 && y < WIN_Y)
	{
		while ((i = 0) == 0 && x < WIN_X &&
				init_ray(env, (double)(x + alias_coef / 2), (double)(y + alias_coef / 2)))
		{
			col[0] = get_col(env, env->init_rays.dir);
			((int *)surf->pixels)[x + y * surf->w] = col[0].color;
			while (alias_coef > 1 && ++i < alias_coef * alias_coef)
				if (x + i % alias_coef < WIN_X && y + i / alias_coef < WIN_Y)
					((int *)surf->pixels)[x + i % alias_coef +
						(y + i / alias_coef) * surf->w] = col[0].color;
			x += alias_coef;
		}
		y += alias_coef;
	}
}

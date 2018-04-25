/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 19:12:29 by tjeanner          #+#    #+#             */
/*   Updated: 2018/04/25 18:48:47 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_line			init_line(double x, double y, t_cam cam)
{
	t_line	line;

	line.dir = vect_norm(vect_add(vect_mult(cam.vcam, DIST),
				vect_add(vect_mult(vect_inv(cam.v3cam),
				(double)((x - WIN_X / 2.0) / get_vect_norm(cam.v3cam))),
				vect_mult(cam.v2cam, (double)((WIN_Y / 2.0 - y) /
				get_vect_norm(cam.v2cam))))));
	line.pos = cam.pos;
	return (line);
}

t_v			get_norm(t_obj obj, t_line line, t_v pos_col)
{
	double	res;
	t_v		vect;

	if (obj.type == 's' || obj.type == 'p')
		vect = (obj.type == 'p') ? obj.norm : vect_sous(pos_col, obj.o);
	else if (obj.type == 'c')
	{
		vect = vect_sous(line.pos, obj.o);
		res = vect_scal(line.dir, vect_mult(obj.norm, obj.dist)) +
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
	return (vect = (obj.type == 'p' && vect_scal(vect, line.dir) > 0.000)
			? vect_norm(vect_inv(vect)) : vect_norm(vect));
}

int			which_obj_col(t_objs *objs, t_line line)
{
	double	res;
	double	obj_dist[2];
	double	all_dists[objs->nb];
	int		i;
	int		ob;

	i = -1;
	res = -1.0;
	while (++i < objs->nb && (all_dists[i] = -1.0) == -1.0)
	{
		if (objs->col_fcts[ft_strchr(FCTS, objs->obj[i].type) - FCTS](line, objs->obj[i],
		obj_dist) == 1 && (obj_dist[0] > 0.000 || obj_dist[1] > 0.000))
		{
			all_dists[i] = (obj_dist[0] > 0.0 && (obj_dist[0]
	< obj_dist[1] || obj_dist[1] < 0.0)) ? obj_dist[0] : all_dists[i];
			all_dists[i] = (obj_dist[1] > 0.0 && (obj_dist[0]
	> obj_dist[1] || obj_dist[0] < 0.0)) ? obj_dist[1] : all_dists[i];
		}
		if ((i == 0 || (all_dists[i] > 0.0 &&
		(res == -1.0 || res > all_dists[i]))) && (ob = i) == i)
			res = all_dists[i];
	}
	while ((i = (i == objs->nb) ? 0 : i + 1) < objs->nb && res > 0.0)
		if (i != ob && all_dists[i] > 0.0 && all_dists[i] - res <
				0.50 && (all_dists[i] = ob) == ob)
			return (-1.0 * i - 2);
	return (ob = (res <= 0.0) ? -1 : ob);
}

t_color		get_lum(t_objs *objs, int obj, t_lums *lums, int lum, t_line line)
{
	int		i;
	t_v		pos_col;
	t_v		col_2_lum;
	t_v		norm;
	double	res;
	double	dist[2];
	t_line	tutu;

	pos_col = vect_add(line.pos, vect_mult(line.dir,
				objs->obj[obj].dist));
	norm = get_norm(objs->obj[obj], line, pos_col);
	norm = (objs->obj[obj].type == 'p' && vect_scal(norm, line.dir) > 0.0) ? vect_inv(norm) : norm;
	pos_col = vect_add(pos_col, vect_mult(norm, 0.00000001000));
	norm = get_norm(objs->obj[obj], line, pos_col);
	col_2_lum = vect_sous(lums->lum[lum].pos, pos_col);
	res = get_vect_norm(col_2_lum);
	tutu.dir = vect_norm(col_2_lum);
	tutu.pos = pos_col;
	i = -1;
	while (++i < objs->nb && (dist[0] = -1.0) < 0)
		if ((dist[1]= -1.0) < 0 && objs->col_fcts[ft_strchr(FCTS,
					objs->obj[i].type) - FCTS](tutu, objs->obj[i], dist) == 1 &&
				(((dist[0] > 0.0 && dist[0] < res) || ((dist[1] > 0.0 && dist[1] < res)))))
			return (get_black());
	res = fmax(0.0, vect_scal(norm, tutu.dir));
	return (mult_color(objs->obj[obj].col, res));
}

t_color		get_col(t_objs *objs, t_lums *lums, t_line line)
{
	int		obj;
//	int		obj2;
	int		i;
	t_color	ambi_col;
	t_color	cols[3];
//	t_v		tmp;
//	t_v		tmp2;

	if ((obj = which_obj_col(objs, line)) <= -1)
		return (get_black());
	if (lums->amb_coef < 1.000)
	{
		ambi_col = mult_color(objs->obj[obj].col, lums->amb_coef);
		cols[0] = get_black();
		cols[1] = get_black();
		i = -1;
		while (++i < lums->nb)
		{
				cols[1] = get_lum(objs, obj, lums, i, line);
				cols[0].c.r = fmin(255, cols[0].c.r + cols[1].c.r * lums->lum[i].coef / lums->coefs_sum);
				cols[0].c.g = fmin(255, cols[0].c.g + cols[1].c.g * lums->lum[i].coef / lums->coefs_sum);
				cols[0].c.b = fmin(255, cols[0].c.b + cols[1].c.b * lums->lum[i].coef / lums->coefs_sum);
		}
	//	line.pos = vect_sous(line.pos, vect_mult(vect_add(tmp, tmp2), 50.00));
		cols[0] = mult_color(cols[0], 1.000 - lums->amb_coef);
		cols[0] = add_color(cols[0], ambi_col);
	}
	else
		cols[0] = objs->obj[obj].col;
	return (cols[0]);
}

void		*rays(void *tmp)
{
	int		i;
	int		y;
	int		x;
	t_color	col;
	t_env *env;

	env = ((t_threads *)tmp)->env;
	y = ((t_threads *)tmp)->start;
	i = ((t_threads *)tmp)->incr;
	while (y < WIN_Y)
	{
		x = -1;
		while (++x < WIN_X)
		{
			col = get_col(&env->objs, &env->lums, init_line(
				(double)(x + 0.5), (double)(y + 0.5),
				env->cams.cam[env->cams.curr]));
			if (env->display.sur == 1)
				((int *)env->display.surf->pixels)[x + y * env->display.surf->w] = col.color;
			else
				((int *)env->display.surf2->pixels)[x + y * env->display.surf->w] = col.color;
		}
		y += i;
	}
	return (env);
}

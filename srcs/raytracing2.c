/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 05:15:10 by hbouchet          #+#    #+#             */
/*   Updated: 2018/05/04 05:18:39 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		recup_line(t_objs *objs, t_ray *line, int ob, double tmp)
{
	line->obj = ob;
	line->to.pos = vect_add(line->from.pos, vect_mult(line->from.dir, tmp));
	line->to.dir = get_norm(objs->obj[ob], line);
	line->dist = tmp;
	line->total_dist += line->dist;
}

int				which_obj_col(t_objs *objs, t_ray *line)
{
	double	tmp;
	t_v		tutu;
	int		i;
	int		ob;

	i = -1;
	tmp = -1.0;
	while (++i < objs->nb)
	{
		if (objs->obj[i].type != NONE && objs->col_fcts[
			(int)objs->obj[i].type](line->from, objs->obj[i], &tutu) == 1)
		{
			if (tutu.y > 0.0 && (tutu.y < tmp || tmp < 0.0) && (ob = i) == i)
				tmp = tutu.y;
			if (tutu.x > 0.0 && (tutu.x < tmp || tmp < 0.0) && (ob = i) == i)
				tmp = tutu.x;
		}
	}
	if (tmp < 0.0 || objs->nb == 0)
		return (0);
	recup_line(objs, line, ob, tmp);
	return (1);
}

t_ray			init_line(double x, double y, t_cam cam)
{
	t_ray	ray;

	ray.from.dir = vect_norm(vect_add(vect_mult(cam.vcam, DIST),
				vect_add(vect_mult(vect_inv(cam.v3cam),
						(double)((x - WIN_X / 2.0) / get_vect_norm(cam.v3cam))),
					vect_mult(cam.v2cam, (double)((WIN_Y / 2.0 - y) /
							get_vect_norm(cam.v2cam))))));
	ray.from.pos = cam.pos;
	ray.dist = 0.0;
	ray.total_dist = 0.0;
	ray.obj = -1;
	ray.n2 = 1.0;
	ray.incident = NULL;
	ray.objs = NULL;
	ray.nb_objs = 0;
	return (ray);
}

t_v				get_norm(t_obj obj, t_ray *line)
{
	double	res;
	t_v		vect;

	obj.norm = vect_norm(obj.norm);
	if (obj.type == PLANE)
		vect = obj.norm;
	else
		vect = vect_sous(line->to.pos, obj.o);
	if (obj.type == CONE || obj.type == CYLINDRE)
	{
		res = vect_scal(vect, obj.norm);
		if (obj.type == CONE)
			res *= (1.0 + pow(tan(obj.radius * TORAD), 2.0));
		vect = vect_sous(vect, vect_mult(obj.norm, res));
	}
	return (vect_norm(vect_scal(vect, line->from.dir) > 0.000
		? vect_inv(vect) : vect));
}

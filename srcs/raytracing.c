/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 19:12:29 by tjeanner          #+#    #+#             */
/*   Updated: 2018/05/04 04:13:02 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

t_v			get_norm(t_obj obj, t_ray *line)
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
	return (vect_norm(vect_scal(vect, line->from.dir) > 0.000 ?
														vect_inv(vect) : vect));
}

int			which_obj_col(t_objs *objs, t_ray *line)
{
	double	tmp;
	t_v		tutu;
	int		i;
	int		ob;

	i = -1;
	tmp = -1.0;
	while (++i < objs->nb)
	{
		if (objs->obj[i].type != NONE && objs->col_fcts[(int)objs->obj[i].type]
				(line->from, objs->obj[i], &tutu) == 1)
		{
			if(tutu.y > 0.0 && (tutu.y < tmp || tmp < 0.0) && (ob = i) == i)
				tmp = tutu.y;
			if(tutu.x > 0.0 && (tutu.x < tmp || tmp < 0.0) && (ob = i) == i)
				tmp = tutu.x;
		}
	}
	if (tmp < 0.0 || objs->nb == 0)
		return (0);
	line->obj = ob;
	line->to.pos = vect_add(line->from.pos, vect_mult(line->from.dir, tmp));
	line->to.dir = get_norm(objs->obj[ob], line);
	line->dist = tmp;
	line->total_dist += line->dist;
	return (1);
}

t_color		get_col(t_objs *objs, t_lums *lums, t_ray *line, unsigned int d)
{
	int		i;
	t_color	ambi_col;
	t_color	col;
	t_obj	obj;

	if (!d || !objs || !lums || which_obj_col(objs, line) == 0)
		return (get_black());
	obj = objs->obj[line->obj];
	if (lums->amb_coef < 1.000)
	{
		ambi_col = mult_color(obj.col, lums->amb_coef);
		col = get_black();
		i = -1;
		while (++i < lums->nb)
			col = add_color(col, mult_color(
							get_lum(objs, line->obj, lums->lum[i], line),
							lums->lum[i].coef / lums->coefs_sum));
		col = add_color(mult_color(col, 1.000 - lums->amb_coef), ambi_col);
	}
	else
		col = obj.col;
	col = mult_color(col, (1.0 - 0.9 * objs->obj[line->obj].reflect) *
									(1.0 - 0.9 * objs->obj[line->obj].transp));
	if (obj.transp > 0.0)
		col = add_color(col, get_refract(objs, lums, line, d - 1));
	if (obj.reflect > 0.0)
		col = add_color(col, get_reflect(objs, lums, line, d - 1));
	return (col);
}

void		*rays(void *tmp)
{
	int		i;
	int		y;
	int		x;
	t_color	col;
	t_env *env;
	t_ray tutu;

	env = ((t_threads *)tmp)->env;
	y = ((t_threads *)tmp)->start;
	i = ((t_threads *)tmp)->incr;
	while (y < WIN_Y)
	{
		x = -1;
		while (++x < WIN_X)
		{
			tutu = init_line((double)(x + 0.5), (double)(y + 0.5),
											env->cams.cam[env->cams.curr]);
			col = get_col(&env->objs, &env->lums, &tutu, env->effects.depth);
			if (env->display.sur == 1)
				((unsigned int *)env->display.surf->pixels)
								[x + y * env->display.surf->w] = col.color;
			else
				((unsigned int *)env->display.surf2->pixels)
								[x + y * env->display.surf->w] = col.color;
		}
		y += i;
	}
	return (env);
}

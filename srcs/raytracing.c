/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 19:12:29 by tjeanner          #+#    #+#             */
/*   Updated: 2018/04/27 06:21:20 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray			init_line(double x, double y, t_cam cam)
{
	t_ray	ray;

	ray.from.dir = vect_norm(vect_add(vect_mult(cam.vcam, DIST),
				vect_add(vect_mult(vect_inv(cam.v3cam),
						(double)((x - WIN_X / 2.0) / get_vect_norm(cam.v3cam))),
					vect_mult(cam.v2cam, (double)((WIN_Y / 2.0 - y) /
							get_vect_norm(cam.v2cam))))));
	ray.from.pos = cam.pos;
	return (ray);
}

t_v			get_norm(t_obj obj, t_ray *line)
{
	double	res;
	t_v		vect;

	if (obj.type == 's' || obj.type == 'p')
		vect = (obj.type == 'p') ? obj.norm : vect_sous(line->to.pos, obj.o);
	else if (obj.type == 'c')
	{
		vect = vect_sous(line->from.pos, obj.o);
		res = vect_scal(line->from.dir, vect_mult(obj.norm, line->dist)) +
			vect_scal(vect, obj.norm);
		vect = vect_sous(vect_sous(line->to.pos, obj.o), vect_mult(obj.norm,
					res * (1.0 + pow(tan(obj.radius * TORAD), 2.0))));
	}
	else
	{
		res = vect_scal(obj.norm, vect_sous(line->to.pos, obj.o)) /
			vect_scal(obj.norm, obj.norm);
		vect = vect_sous(line->to.pos, vect_add(obj.o, vect_mult(obj.norm, res)));
	}
	return (vect = (obj.type == 'p' && vect_scal(vect, line->from.dir) > 0.000)
			? vect_norm(vect_inv(vect)) : vect_norm(vect));
}

int			which_obj_col(t_objs *objs, t_ray *line)
{
	double	tmp;
	double	tutu;
	int		i;
	int		ob;

	i = -1;
	tmp = -1.0;
	while (++i < objs->nb)
	{
		if (objs->col_fcts[ft_strchr(FCTS, objs->obj[i].type) - FCTS]
				(line->from, objs->obj[i], &tutu) == 1)
			//			tutu = -1;
			if ((i == 0 || (tutu > 0.0 &&
							(tmp == -1.0 || tmp > tutu))) && (ob = i) == i)
				tmp = tutu;
	}
	if ((line->dist = tmp) < 0.0)
		return (0);
	line->obj = ob;
	line->to.pos = vect_add(line->from.pos, vect_mult(line->from.dir, tmp));
	line->to.dir = get_norm(objs->obj[ob], line);
	return (1);
}

t_color		get_lum(t_objs *objs, int obj, t_lum lum, t_ray *line)
{
	int		i;
	t_v		col_2_lum;
	double	res;
	double	tmp;
	t_ray	tutu;

	//	pos_col = vect_add(line->from.pos, vect_mult(line->from.dir,
	//				dista));
	//	norm = get_norm(objs->obj[obj], line, pos_col, dista);
	//	norm = (objs->obj[obj].type == 'p' && vect_scal(norm, line->from.dir) > 0.0) ? vect_inv(norm) : norm;
//	pos_col = vect_add(pos_col, vect_mult(norm, 0.00000001000));
	//	norm = get_norm(objs->obj[obj], line, pos_col, dista);
	col_2_lum = vect_sous(lum.pos, line->to.pos);
	tmp = get_vect_norm(col_2_lum);
	tutu.from.dir = vect_norm(col_2_lum);
	tutu.from.pos = vect_add(line->to.pos, vect_mult(line->to.dir, 0.00000001));
	i = -1;
	while (++i < objs->nb && (res = -1.0) < 0)
		if (objs->col_fcts[ft_strchr(FCTS,
					objs->obj[i].type) - FCTS](tutu.from, objs->obj[i], &res) == 1 &&
				(((res > 0.0 && res < tmp))))
			return (get_black());
	res = fmax(0.0, vect_scal(line->to.dir, tutu.from.dir));
	return (mult_color(objs->obj[obj].col, res));
}

t_color		get_col(t_objs *objs, t_lums *lums, t_ray *line)
{
	int		i;
	t_color	ambi_col;
	t_color	cols[3];
//	t_v		tmp;
//	t_v		tmp2;

	(void)lums;
	if (which_obj_col(objs, line) <= -1)
		return (get_black());
	if (lums->amb_coef < 1.000)
	{
		ambi_col = mult_color(objs->obj[line->obj].col, lums->amb_coef);
		cols[0] = get_black();
		cols[1] = get_black();
		i = -1;
		while (++i < lums->nb)
		{
				cols[1] = get_lum(objs, line->obj, lums->lum[i], line);
				cols[0].c.r = fmin(255, cols[0].c.r + cols[1].c.r * lums->lum[i].coef / lums->coefs_sum);
				cols[0].c.g = fmin(255, cols[0].c.g + cols[1].c.g * lums->lum[i].coef / lums->coefs_sum);
				cols[0].c.b = fmin(255, cols[0].c.b + cols[1].c.b * lums->lum[i].coef / lums->coefs_sum);
		}
	//	line->from.pos = vect_sous(line->from.pos, vect_mult(vect_add(tmp, tmp2), 50.00));
		cols[0] = mult_color(cols[0], 1.000 - lums->amb_coef);
		cols[0] = add_color(cols[0], ambi_col);
	}
	else
	cols[0] = objs->obj[line->obj].col;
	return (cols[0]);
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
			tutu = init_line((double)(x + 0.5), (double)(y + 0.5), env->cams.cam[env->cams.curr]);
			col = get_col(&env->objs, &env->lums, &tutu);
			if (env->display.sur == 1)
				((int *)env->display.surf->pixels)[x + y * env->display.surf->w] = col.color;
			else
				((int *)env->display.surf2->pixels)[x + y * env->display.surf->w] = col.color;
		}
		y += i;
	}
	return (env);
}

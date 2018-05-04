/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lum.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 05:42:44 by cquillet          #+#    #+#             */
/*   Updated: 2018/05/04 02:45:08 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		get_specular(t_obj obj, t_ray ray)
{
	double	res;
	t_v		half;
	t_v		to_eye;
	t_color	plastic;
	t_color	col;

	if (obj.k_spec == 0.0)
		return (get_black());
	to_eye = (*(ray.incident)).to.dir;
	half = vect_norm(vect_sous(ray.from.dir, ray.incident->from.dir));
	if ((res = vect_scal(ray.to.dir, half)) < 0.0)
		return (get_black());
	plastic = mult_color(get_white(), obj.mat.plastic);
	plastic = add_color(plastic, mult_color(obj.col, 1.0 - obj.mat.plastic));
	if (obj.mat.rough == 1.0)
		col = mult_color(obj.col, res);
	else
		col = mult_color(obj.col, pow(res, obj.mat.rough));
	return (mult_color(gamma_korr(col, 0.8),
									obj.k_spec / (obj.k_diff + obj.k_spec)));
/*			res * obj.k_spec / (obj.k_diff + obj.k_spec)));
	return (mult_color(obj.col,
			pow(res, obj.mat.rough) * obj.k_spec / (obj.k_diff + obj.k_spec)));*/
}

t_color		get_diffuse(t_obj obj, t_ray ray)
{
	double	res;

	if (obj.k_diff == 0.0)
		return (get_black());
	if ((res = vect_scal(ray.to.dir, ray.from.dir)) < 0.0)
		return (get_black());
	return (mult_color(obj.col, res * obj.k_diff / (obj.k_diff + obj.k_spec)));
}

t_color		get_lum(t_objs *objs, int obj, t_lum lum, t_ray *line)
{
	int		i;
	t_v		res;
	t_ray	tutu;
	t_color	col;
	double	tmp;

	tutu.to.pos = lum.pos;
	tutu.from.dir = vect_sous(lum.pos, line->to.pos);
	tmp = get_vect_norm(tutu.from.dir);
	tutu.from.dir = vect_norm(get_vect_norm(lum.dir) ? tutu.from.dir : vect_inv(lum.dir));
	tutu.from.dir = vect_norm(tutu.from.dir);
	tutu.from.pos = vect_add(line->to.pos, vect_mult(line->to.dir, MARGIN));
	tutu.incident = line;
	line->col = get_white();
	i = -1;
	while (++i < objs->nb)
		if (objs->obj[i].type != NONE && (objs->col_fcts[(int)objs->obj[i].type]
				(tutu.from, objs->obj[i], &res) == 1) &&
			((res.x > 0.0 && res.x < tmp) || (res.y > 0.0 && res.y < tmp)))
		{
			if (objs->obj[i].transp == 0.0)
				return ((line->col = get_black()));
			lum.coef *= (res.x > 0.0 && res.x < tmp) ? objs->obj[i].transp : 1.0;
			lum.coef *= (res.y > 0.0 && res.y < tmp) ? objs->obj[i].transp : 1.0;
			line->col = prod_color(line->col, objs->obj[i].col);
		}
	tutu.to.dir = line->to.dir;
	col = get_diffuse(objs->obj[obj], tutu);
	col = add_color(col, get_specular(objs->obj[obj], tutu));
	col = prod_color(col, line->col);
	return (col);
}

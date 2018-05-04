/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lum.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 05:42:44 by cquillet          #+#    #+#             */
/*   Updated: 2018/05/04 05:43:06 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color			get_specular(t_obj obj, t_ray ray)
{
	t_color	plastic;
	double	res;

	if (obj.k_spec == 0.0)
		return (get_black());
	if ((res = vect_scal(ray.to.dir, ray.from.dir)) < 0.0)
		return (get_black());
	plastic = mult_color(get_white(), obj.mat.plastic);
	plastic = add_color(plastic, mult_color(obj.col, 1.0 - obj.mat.plastic));
	return (gamma_korr(mult_color(plastic, res), 15.0));
}

t_color			get_diffuse(t_obj obj, t_ray ray)
{
	double	res;

	if (obj.k_diff == 0.0)
		return (get_black());
	if ((res = vect_scal(ray.to.dir, ray.from.dir)) < 0.0)
		return (get_black());
	return (mult_color(obj.col, res));
}

static double	init_lum_ray(t_ray *ray, t_ray *incident, t_lum lum)
{
	double	dist;

	if (!ray)
		return (0.);
	ray->to.pos = lum.pos;
	if (!incident)
		return (0.);
	ray->from.dir = vect_sous(lum.pos, incident->to.pos);
	dist = get_vect_norm(ray->from.dir);
	ray->from.dir = vect_norm(ray->from.dir);
	ray->from.pos = vect_add(incident->to.pos, vect_mult(incident->to.dir, MARGIN));
	ray->incident = incident;
	return (dist);
}

t_color			get_lum(t_objs *objs, int obj, t_lum lum, t_ray *line)
{
	int		i;
	t_v		res;
	t_ray	tutu;
	t_color	col;
	double	tmp;

	tmp = init_lum_ray(&tutu, line, lum);
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
	col = add_color(get_specular(objs->obj[obj], tutu),
										get_diffuse(objs->obj[obj], tutu));
	return (gamma_korr( prod_color(col, line->col), 2.0));
}

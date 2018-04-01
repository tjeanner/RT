/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distances_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 03:13:21 by tjeanner          #+#    #+#             */
/*   Updated: 2018/04/02 00:12:04 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			get_dist_cone(t_ray *init_rays, t_obj obj)
{
	t_v		s;
	t_v		va;
	t_v		math;
	double	h;
	double	w;

	s = vect_soustr(obj.o, obj.norm);
	s = vect_norm(s);
	math.y = vect_scal_prod(init_rays->r2, s);
	math.z = get_vect_norm(vect_soustr(obj.o, obj.norm));
	math.z = obj.radius * obj.radius / (math.z * math.z);
	h = vect_scal_prod(s, vect_soustr(init_rays->r2, obj.norm));
	va = vect_prod(vect_prod(s, init_rays->r2), s);
	w = 50.0 - vect_scal_prod(s, vect_soustr(init_rays->r, obj.norm));
	s = vect_prod(vect_prod(s, vect_soustr(init_rays->r, obj.norm)), s);
	math.x = vect_scal_prod(va, va) - math.y * math.y * math.z;
	math.y = 2.0 * vect_scal_prod(s, va) + 2.0 * w * math.y * math.z;
	math.z = vect_scal_prod(s, s) - w * w * math.z;
	math.z = math.y * math.y - 4.0 * math.x * math.z;
	if (math.z < 0.0)//case where there's no solution for the equation, so no collision
		return (0);
	else//case where there's one solution (if math.z == 0) or 2 of them (math.z > 0)
	{
		init_rays->v1 = (-math.y + sqrt(math.z)) / (2.0 * math.x);//if math.z == 0
		init_rays->v2 = (-math.y - sqrt(math.z)) / (2.0 * math.x);//init_rays->v2 will be the same as init_rays->v1
	}
	return (1);
}

int			get_dist_tube(t_ray *init_rays, t_obj obj)
{
	t_v		va;
	t_v		ra0;
	t_v		math;

	obj.norm = vect_norm(obj.norm);
	va = vect_prod(vect_prod(obj.norm, init_rays->r2), obj.norm);//Va
	ra0 = vect_prod(vect_prod(obj.norm, vect_soustr(init_rays->r,
					obj.o)), obj.norm);//Ra0
	math.x = vect_scal_prod(va, va);
	math.y = 2.0 * vect_scal_prod(va, ra0);
	math.z = vect_scal_prod(ra0, ra0) - obj.radius * obj.radius;
	math.z = math.y * math.y - 4.0 * math.x * math.z;
	if (math.z < 0.0)
		return (0);
	else
	{
		init_rays->v1 = (-math.y + sqrt(math.z)) / (2.0 * math.x);
		init_rays->v2 = (-math.y - sqrt(math.z)) / (2.0 * math.x);
	}
	return (1);
}

int			get_dist_plan(t_ray *init_rays, t_obj obj)
{
	t_v		tmp;

	tmp = (vect_scal_prod(init_rays->r2, obj.norm)) > 0 ?
		obj.norm : vect_mult(obj.norm, -1.0000);
	if (vect_scal_prod(init_rays->r2, tmp) < 0.0000)
		return (0);
	init_rays->v1 = -1;
	init_rays->v2 = vect_scal_prod(vect_soustr(obj.o, init_rays->r), tmp) /
		vect_scal_prod(init_rays->r2, tmp);
	if ((obj.radius < 0 && get_vect_norm(vect_soustr(obj.o,
		vect_add(init_rays->r, vect_mult(init_rays->r2,
		init_rays->v2)))) > -1.0 * obj.radius)
			|| vect_scal_prod(init_rays->r2, tmp) < 0.000)
		init_rays->v2 = -1;
	return (1);
}

/*
**get_dist: a function that will return 0, 1 or 2 distances between a sphere and
**the pixel. the distance(s) is written in init_rays->v1 and init_rays->v2
*/

int			get_dist_sphere(t_ray *init_rays, t_obj obj)
{
	t_v		pixel_2_sphere_center;
	t_v		math;
	double	tmp;

	pixel_2_sphere_center = vect_soustr(init_rays->r, obj.o);
	math.x = vect_scal_prod(init_rays->r2, init_rays->r2);
	math.y = 2.0 * vect_scal_prod(init_rays->r2, pixel_2_sphere_center);
	math.z = vect_scal_prod(pixel_2_sphere_center, pixel_2_sphere_center) -
		obj.radius * obj.radius;
	tmp = math.y * math.y - 4.0 * math.x * math.z;
	if (tmp < 0.0)//case where there's no solution for the equation, so no collision
		return (0);
	else//case where there's one solution (if tmp == 0) or 2 of them (tmp > 0)
	{
		init_rays->v1 = (-math.y + sqrt(tmp)) / (2.0 * math.x);//if tmp == 0
		init_rays->v2 = (-math.y - sqrt(tmp)) / (2.0 * math.x);//init_rays->v2 will be the same as init_rays->v1
	}
	return (1);
}

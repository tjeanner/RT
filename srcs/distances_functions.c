/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distances_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 03:13:21 by tjeanner          #+#    #+#             */
/*   Updated: 2018/02/18 08:33:01 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			get_dist_cone(t_ray *init_rays, t_obj obj)
{
	t_v		s;
	t_v		va;
	double	h;
	double	w;
	double	a;
	double	b;
	double	c;

	s = vect_add(obj.o, vect_mult(obj.norm, -1.0));
	s = vect_mult(s, 1.0 / vect_norm(s));
	b = vect_scal_prod(init_rays->r2, s);
	c = vect_norm(vect_add(obj.o, vect_mult(obj.norm, -1.0)));
	c = obj.radius * obj.radius / (c * c);
	h = vect_scal_prod(s, vect_add(init_rays->r2, vect_mult(obj.norm, -1.0)));
	va = vect_prod(vect_prod(s, init_rays->r2), s);
	w = 50.0 - vect_scal_prod(s, vect_add(init_rays->r,
				vect_mult(obj.norm, -1.0)));
	s = vect_prod(vect_prod(s, vect_add(init_rays->r,
					vect_mult(obj.norm, -1.0))), s);
	a = vect_scal_prod(va, va) - b * b * c;
	b = 2.0 * vect_scal_prod(s, va) + 2.0 * w * b * c;
	c = vect_scal_prod(s, s) - w * w * c;
	c = b * b - 4.0 * a * c;
	if (c < 0.0)//case where there's no solution for the equation, so no collision
		return (0);
	else//case where there's one solution (if c == 0) or 2 of them (c > 0)
	{
		init_rays->v1 = (-b + sqrt(c)) / (2.0 * a);//if c == 0
		init_rays->v2 = (-b - sqrt(c)) / (2.0 * a);//init_rays->v2 will be the same as init_rays->v1
	}
	return (1);
}

int			get_dist_tube(t_ray *init_rays, t_obj obj)
{
	t_v		va;
	t_v		ra0;
	double	a;
	double	b;
	double	c;

	obj.norm = vect_mult(obj.norm, 1.0 / vect_norm(obj.norm));
	va = vect_prod(vect_prod(obj.norm, init_rays->r2), obj.norm);//Va
	ra0 = vect_prod(vect_prod(obj.norm, vect_add(init_rays->r,
					vect_mult(obj.o, -1.0))), obj.norm);//Ra0
	a = vect_scal_prod(va, va);
	b = 2.0 * vect_scal_prod(va, ra0);
	c = vect_scal_prod(ra0, ra0) - obj.radius * obj.radius;
	c = b * b - 4.0 * a * c;
	if (c < 0.0)
		return (0);
	else
	{
		init_rays->v1 = (-b + sqrt(c)) / (2.0 * a);
		init_rays->v2 = (-b - sqrt(c)) / (2.0 * a);
	}
	return (1);
}

int			get_dist_plan(t_ray *init_rays, t_obj obj)
{
	init_rays->v1 = -1;
	init_rays->v2 = vect_scal_prod(obj.norm, vect_add(obj.o,
	vect_mult(init_rays->r, -1.0))) / vect_scal_prod(obj.norm, init_rays->r2);
	if (obj.radius < 0 && vect_norm(vect_add(obj.o, vect_mult(vect_add(init_rays->r, vect_mult(init_rays->r2, init_rays->v2)), -1.0))) > -1.0 * obj.radius)
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
	double	a;
	double	b;
	double	c;
	double	tmp;

	pixel_2_sphere_center = vect_add(init_rays->r, vect_mult(obj.o, -1.0));
	a = vect_scal_prod(init_rays->r2, init_rays->r2);
	b = 2.0 * vect_scal_prod(init_rays->r2, pixel_2_sphere_center);
	c = vect_scal_prod(pixel_2_sphere_center, pixel_2_sphere_center) -
		obj.radius * obj.radius;
	tmp = b * b - 4.0 * a * c;
	if (tmp < 0.0)//case where there's no solution for the equation, so no collision
		return (0);
	else//case where there's one solution (if tmp == 0) or 2 of them (tmp > 0)
	{
		init_rays->v1 = (-b + sqrt(tmp)) / (2.0 * a);//if tmp == 0
		init_rays->v2 = (-b - sqrt(tmp)) / (2.0 * a);//init_rays->v2 will be the same as init_rays->v1
	}
	return (1);
}

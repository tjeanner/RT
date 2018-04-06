/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distances_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 03:13:21 by tjeanner          #+#    #+#             */
/*   Updated: 2018/04/06 06:00:46 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			get_dist_cone(t_ray *init_rays, t_obj obj)
{
	t_v		obj_o2cam;
//	t_v		va;
	t_v		math;
//	double	h;
//	double	w;

	obj.norm = vect_norm(obj.norm);
	obj_o2cam = vect_sous(init_rays->r, obj.o);
//	s = vect_sous(obj.o, obj.norm);
//	s = vect_norm(s);
//	math.y = vect_scal_prod(init_rays->r2, s);
//	math.z = get_vect_norm(vect_sous(obj.o, obj.norm));
//	math.z = obj.radius * obj.radius / (math.z * math.z);
//	h = vect_scal_prod(s, vect_sous(init_rays->r2, obj.norm));
//	va = vect_prod(vect_prod(s, init_rays->r2), s);
//	w = 50.0 - vect_scal_prod(s, vect_sous(init_rays->r, obj.norm));
//	s = vect_prod(vect_prod(s, vect_sous(init_rays->r, obj.norm)), s);
//	math.x = vect_scal_prod(va, va) - math.y * math.y * math.z;
//	math.y = 2.0 * vect_scal_prod(s, va) + 2.0 * w * math.y * math.z;
//	math.z = vect_scal_prod(s, s) - w * w * math.z;
	math.x = 1.0 + pow(tan(obj.radius * M_PI / 180.00), 2.0);
	math.y = 2.0 * (vect_scal_prod(init_rays->r2, obj_o2cam) - math.x * vect_scal_prod(init_rays->r2, obj.norm) * vect_scal_prod(obj_o2cam, obj.norm));
	math.z = vect_scal_prod(obj_o2cam, obj_o2cam) - math.x * pow(vect_scal_prod(obj_o2cam, obj.norm), 2.0);
	math.x = vect_scal_prod(init_rays->r2, init_rays->r2) - math.x * pow(vect_scal_prod(init_rays->r2, obj.norm), 2.0);
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
	t_v		obj_o2cam;
	t_v		math;

	obj.norm = vect_norm(obj.norm);
	obj_o2cam = vect_sous(init_rays->r, obj.o);
	math.x = vect_scal_prod(init_rays->r2, init_rays->r2) - pow(vect_scal_prod(init_rays->r2, obj.norm), 2.0);
	math.y = 2.0 * (vect_scal_prod(init_rays->r2, obj_o2cam) - vect_scal_prod(init_rays->r2, obj.norm) * vect_scal_prod(obj_o2cam, obj.norm));
	math.z = vect_scal_prod(obj_o2cam, obj_o2cam) - pow(vect_scal_prod(obj_o2cam, obj.norm), 2.0) - pow(obj.radius, 2.0);
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
	double	opti_a;
	double	opti_b;

	tmp = (vect_scal_prod(init_rays->r2, obj.norm)) > 0.000 ?
		obj.norm : vect_inv(obj.norm);
	opti_a = vect_scal_prod(vect_sous(init_rays->r, obj.o), tmp);
	opti_b = vect_scal_prod(init_rays->r2, tmp);
	if (vect_scal_prod(init_rays->r2, tmp) == 0.000 ||
			opti_a > 0.000 ^ opti_b < 0.000)
		return (0);
	init_rays->v1 = -1.000;
	init_rays->v2 = -1.000 * opti_a / opti_b;
//	if (obj.radius < 0 && get_vect_norm(vect_sous(obj.o,
//		vect_add(init_rays->r, vect_mult(init_rays->r2, init_rays->v2))))
	//		> -1.000 * obj.radius)
	//	init_rays->v2 = -1.000;
	return (1);
}

/*
**get_dist: a function that will return 0, 1 or 2 distances between a sphere and
**the pixel. the distance(s) is written in init_rays->v1 and init_rays->v2
*/

int			get_dist_sphere(t_ray *init_rays, t_obj obj)
{
	t_v		obj_o2cam;
	t_v		math;
	double	tmp;

	obj_o2cam = vect_sous(init_rays->r, obj.o);
	math.x = vect_scal_prod(init_rays->r2, init_rays->r2);
	math.y = 2.0 * vect_scal_prod(init_rays->r2, obj_o2cam);
	math.z = vect_scal_prod(obj_o2cam, obj_o2cam) - obj.radius * obj.radius;
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

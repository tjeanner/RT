/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distances_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 03:13:21 by tjeanner          #+#    #+#             */
/*   Updated: 2018/04/12 08:19:02 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			get_dist_cone(t_ray *init_rays, t_obj obj)
{
	t_v		obj_o2cam;
	t_v		math;

	obj.norm = vect_norm(obj.norm);
	obj_o2cam = vect_sous(init_rays->pos, obj.o);
	math.x = 1.0 + pow(tan(obj.radius * M_PI / 180.00), 2.0);
	math.y = 2.0 * (vect_scal_prod(init_rays->dir, obj_o2cam) - math.x * vect_scal_prod(init_rays->dir, obj.norm) * vect_scal_prod(obj_o2cam, obj.norm));
	math.z = vect_scal_prod(obj_o2cam, obj_o2cam) - math.x * pow(vect_scal_prod(obj_o2cam, obj.norm), 2.0);
	math.x = vect_scal_prod(init_rays->dir, init_rays->dir) - math.x * pow(vect_scal_prod(init_rays->dir, obj.norm), 2.0);
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

int			get_dist_tube(t_ray *init_rays, t_obj obj)
{
	t_v		math;
	t_v		aa;

	aa = vect_sous(init_rays->pos, obj.o);
	math.x = vect_scal_prod(vect_sous(init_rays->dir, vect_mult(obj.norm, vect_scal_prod(init_rays->dir, obj.norm))), vect_sous(init_rays->dir, vect_mult(obj.norm, vect_scal_prod(init_rays->dir, obj.norm))));
	math.y = 2.0 * vect_scal_prod(vect_sous(init_rays->dir, vect_mult(obj.norm, vect_scal_prod(init_rays->dir, obj.norm))), vect_sous(aa, vect_mult(obj.norm, vect_scal_prod(aa, obj.norm))));
	math.z = vect_scal_prod(vect_sous(aa, vect_mult(obj.norm, vect_scal_prod(aa, obj.norm))), vect_sous(aa, vect_mult(obj.norm, vect_scal_prod(aa, obj.norm)))) - pow(obj.radius, 2.0);
	math.z = pow(math.y, 2.0) - 4.0 * math.z * math.x;
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

	tmp = (vect_scal_prod(init_rays->dir, obj.norm)) > 0.000 ?
		obj.norm : vect_inv(obj.norm);
	opti_a = vect_scal_prod(vect_sous(init_rays->pos, obj.o), tmp);
	opti_b = vect_scal_prod(init_rays->dir, tmp);
	if (opti_b == 0.000 || opti_a > 0.000 ^ opti_b < 0.000)
		return (0);
	init_rays->v1 = -1.000;
	init_rays->v2 = -1.000 * opti_a / opti_b;
//	if (obj.radius < 0 && get_vect_norm(vect_sous(obj.o,
//		vect_add(init_rays->pos, vect_mult(init_rays->dir, init_rays->v2))))
	//		> -1.000 * obj.radius)
	//	init_rays->v2 = -1.000;
	return (1);
}

int			get_dist_sphere(t_ray *init_rays, t_obj obj)
{
	t_v		obj_o2cam;
	t_v		math;

	obj_o2cam = vect_sous(init_rays->pos, obj.o);
	math.x = 2.0 * vect_scal_prod(init_rays->dir, init_rays->dir);
	math.y = 2.0 * vect_scal_prod(init_rays->dir, obj_o2cam);
	math.z = vect_scal_prod(obj_o2cam, obj_o2cam) - obj.radius * obj.radius;
	math.z = math.y * math.y - 2.0 * math.x * math.z;
	if (math.z < 0.0)
		return (0);
	else
	{
		init_rays->v1 = (-math.y + sqrt(math.z)) / math.x;
		init_rays->v2 = (-math.y - sqrt(math.z)) / math.x;
	}
	return (1);
}

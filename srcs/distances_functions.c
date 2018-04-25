/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distances_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 03:13:21 by tjeanner          #+#    #+#             */
/*   Updated: 2018/04/25 03:22:26 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			get_dist_cone(t_line line, t_obj obj, double *dists)
{
	t_v		obj_o2cam;
	t_v		math;

	obj.norm = vect_norm(obj.norm);
	obj_o2cam = vect_sous(line.pos, obj.o);
	math.x = 1.0 + pow(tan(obj.radius * M_PI / 180.00), 2.0);
	math.y = 2.0 * (vect_scal(line.dir, obj_o2cam) - math.x * vect_scal(line.dir, obj.norm) * vect_scal(obj_o2cam, obj.norm));
	math.z = vect_scal(obj_o2cam, obj_o2cam) - math.x * pow(vect_scal(obj_o2cam, obj.norm), 2.0);
	math.x = vect_scal(line.dir, line.dir) - math.x * pow(vect_scal(line.dir, obj.norm), 2.0);
	math.z = math.y * math.y - 4.0 * math.x * math.z;
	if (math.z < 0.0)
		return (0);
	else
	{
		dists[0] = (-math.y + sqrt(math.z)) / (2.0 * math.x);
		dists[1] = (-math.y - sqrt(math.z)) / (2.0 * math.x);
	}
	return (1);
}

int			get_dist_tube(t_line line, t_obj obj, double *dists)
{
	t_v		math;
	t_v		aa;

	aa = vect_sous(line.pos, obj.o);
	math.x = vect_scal(vect_sous(line.dir, vect_mult(obj.norm, vect_scal(line.dir, obj.norm))), vect_sous(line.dir, vect_mult(obj.norm, vect_scal(line.dir, obj.norm))));
	math.y = 2.0 * vect_scal(vect_sous(line.dir, vect_mult(obj.norm, vect_scal(line.dir, obj.norm))), vect_sous(aa, vect_mult(obj.norm, vect_scal(aa, obj.norm))));
	math.z = vect_scal(vect_sous(aa, vect_mult(obj.norm, vect_scal(aa, obj.norm))), vect_sous(aa, vect_mult(obj.norm, vect_scal(aa, obj.norm)))) - pow(obj.radius, 2.0);
	math.z = pow(math.y, 2.0) - 4.0 * math.z * math.x;
	if (math.z < 0.0)
		return (0);
	else
	{
		dists[0] = (-math.y + sqrt(math.z)) / (2.0 * math.x);
		dists[1] = (-math.y - sqrt(math.z)) / (2.0 * math.x);
	}
	return (1);
}

int			get_dist_plan(t_line line, t_obj obj, double *dists)
{
	t_v		tmp;
	double	opti_a;
	double	opti_b;

	tmp = (vect_scal(line.dir, obj.norm)) > 0.000 ?
		obj.norm : vect_inv(obj.norm);
	opti_a = vect_scal(vect_sous(line.pos, obj.o), tmp);
	opti_b = vect_scal(line.dir, tmp);
	if (opti_b == 0.000 || opti_a > 0.000 ^ opti_b < 0.000)
		return (0);
	dists[0] = -1.000;
	dists[1] = -1.000 * opti_a / opti_b;
	return (1);
}

int			get_dist_sphere(t_line line, t_obj obj, double *dists)
{
	t_v		obj_o2cam;
	t_v		math;

	obj_o2cam = vect_sous(line.pos, obj.o);
	math.x = 2.0 * vect_scal(line.dir, line.dir);
	math.y = 2.0 * vect_scal(line.dir, obj_o2cam);
	math.z = vect_scal(obj_o2cam, obj_o2cam) - obj.radius * obj.radius;
	math.z = math.y * math.y - 2.0 * math.x * math.z;
	if (math.z < 0.0)
		return (0);
	else
	{
		dists[0] = (-math.y + sqrt(math.z)) / math.x;
		dists[1] = (-math.y - sqrt(math.z)) / math.x;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distances_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 03:13:21 by tjeanner          #+#    #+#             */
/*   Updated: 2018/05/04 04:03:20 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			resolve(t_v math, t_v *res)
{
	math.z = math.y * math.y - 4.0 * math.x * math.z;
	if (math.z < 0.0)
		return (0);
	res->y = (-math.y + sqrt(math.z)) / (2.0 * math.x);
	res->x = (-math.y - sqrt(math.z)) / (2.0 * math.x);
	if (res->y < 0.0)
		return (0);
	res->z = (res->x > 0.0) ? res->x : res->y;
	return (1);
}

int			get_dist_cone(t_line line, t_obj obj, t_v *res)
{
	t_v		obj_o2cam;
	t_v		math;
	t_v		opti;
	double	opti_ang;

	opti_ang = cos(TORAD * obj.radius) * cos(TORAD * obj.radius);
	obj_o2cam = vect_sous(line.pos, obj.o);
	opti.x = vect_scal(line.dir, obj.norm);
	opti.y = vect_scal(obj_o2cam, obj.norm);
	math.x = opti.x * opti.x - opti_ang;
	math.y = 2.0 *
				(opti.x * opti.y - vect_scal(line.dir, obj_o2cam) * opti_ang);
	math.z = opti.y * opti.y - vect_scal(obj_o2cam, obj_o2cam) * opti_ang;
	return (resolve(math, res));
}

int			get_dist_tube(t_line line, t_obj obj, t_v *res)
{
	t_v		math;
	t_v		obj2cam;
	t_v		opti1;
	t_v		opti2;

	obj2cam = vect_sous(line.pos, obj.o);
	opti1 = vect_sous(line.dir,
						vect_mult(obj.norm, vect_scal(line.dir, obj.norm)));
	math.x = vect_scal(opti1, opti1);
	opti2 = vect_sous(obj2cam,
						vect_mult(obj.norm, vect_scal(obj2cam, obj.norm)));
	math.y = 2.0 * vect_scal(opti1, opti2);
	math.z = vect_scal(opti2, opti2) - obj.radius * obj.radius;
	return (resolve(math, res));
}

int			get_dist_plan(t_line line, t_obj obj, t_v *res)
{
	t_v		tmp;
	double	opti_a;
	double	opti_b;

	tmp = (vect_scal(line.dir, obj.norm)) > 0.000 ?
		obj.norm : vect_inv(obj.norm);
	opti_a = vect_scal(vect_sous(line.pos, obj.o), tmp);
	opti_b = vect_scal(line.dir, tmp);
	if (opti_b == 0.000 || (opti_a > 0.000 ^ opti_b < 0.000))
		return (0);
	res->z = -1.000 * opti_a / opti_b;
	res->y = res->z;
	res->x = res->z;
	if (obj.mat.tex != 1)
		return ((int)(opti_a = (res->z > 0.0) ? 1 : 0));
	return (get_procedural_text(line, obj, res));
}

int			get_dist_sphere(t_line line, t_obj obj, t_v *res)
{
	t_v		obj_o2cam;
	t_v		math;

	obj_o2cam = vect_sous(line.pos, obj.o);
	math.x = vect_scal(line.dir, line.dir);
	math.y = 2.0 * vect_scal(line.dir, obj_o2cam);
	math.z = vect_scal(obj_o2cam, obj_o2cam) - obj.radius * obj.radius;
	return (resolve(math, res));
}

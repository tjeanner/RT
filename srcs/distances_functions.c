/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distances_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 03:13:21 by tjeanner          #+#    #+#             */
/*   Updated: 2018/05/01 05:41:46 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
//#include "gsl/gsl_math.h"
//#include "gsl/gsl_poly.h"
//#include "gsl/gsl_errno.h"

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

	obj.norm = vect_norm(obj.norm);
	obj_o2cam = vect_sous(line.pos, obj.o);
	math.x = 1.0 + pow(tan(obj.radius * TORAD), 2.0);
	math.y = 2.0 * (vect_scal(line.dir, obj_o2cam) - math.x * vect_scal(line.dir, obj.norm) * vect_scal(obj_o2cam, obj.norm));
	math.z = vect_scal(obj_o2cam, obj_o2cam) - math.x * pow(vect_scal(obj_o2cam, obj.norm), 2.0);
	math.x = vect_scal(line.dir, line.dir) - math.x * pow(vect_scal(line.dir, obj.norm), 2.0);
	/*	math.z = math.y * math.y - 4.0 * math.x * math.z;
		if (math.z < 0.0)
		return (0);
		else
		{
		line->dist[1] = (-math.y + sqrt(math.z)) / (2.0 * math.x);
		line->dist[0] = (-math.y - sqrt(math.z)) / (2.0 * math.x);
		}*/
	return (resolve(math, res));
}

int			get_dist_tube(t_line line, t_obj obj, t_v *res)
{
	t_v		math;
	t_v		aa;

	aa = vect_sous(line.pos, obj.o);
	math.x = vect_scal(vect_sous(line.dir, vect_mult(obj.norm, vect_scal(line.dir, obj.norm))), vect_sous(line.dir, vect_mult(obj.norm, vect_scal(line.dir, obj.norm))));
	math.y = 2.0 * vect_scal(vect_sous(line.dir, vect_mult(obj.norm, vect_scal(line.dir, obj.norm))), vect_sous(aa, vect_mult(obj.norm, vect_scal(aa, obj.norm))));
	math.z = vect_scal(vect_sous(aa, vect_mult(obj.norm, vect_scal(aa, obj.norm))), vect_sous(aa, vect_mult(obj.norm, vect_scal(aa, obj.norm)))) - pow(obj.radius, 2.0);
	/*	math.z = pow(math.y, 2.0) - 4.0 * math.z * math.x;
		if (math.z < 0.0)
		return (0);
		else
		{
		line->dist[1] = (-math.y + sqrt(math.z)) / (2.0 * math.x);
		line->dist[0] = (-math.y - sqrt(math.z)) / (2.0 * math.x);
		}*/
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
	if (opti_b == 0.000 || opti_a > 0.000 ^ opti_b < 0.000)
		return (0);
	res->z = -1.000 * opti_a / opti_b;
	res->y = res->z;
	res->x = res->z;
	return ((int)(opti_a = (res->z > 0.0) ? 1 : 0));
}

int			get_dist_sphere(t_line line, t_obj obj, t_v *res)
{
	t_v		obj_o2cam;
	t_v		math;

	obj_o2cam = vect_sous(line.pos, obj.o);
	//	math.x = 2.0 * vect_scal(line.dir, line.dir);
	math.x = vect_scal(line.dir, line.dir);
	math.y = 2.0 * vect_scal(line.dir, obj_o2cam);
	math.z = vect_scal(obj_o2cam, obj_o2cam) - obj.radius * obj.radius;
	/*	math.z = math.y * math.y - 2.0 * math.x * math.z;
		if (math.z < 0.0)
		return (0);
		else
		{
		line->dist[1] = (-math.y + sqrt(math.z)) / math.x;
		line->dist[0] = (-math.y - sqrt(math.z)) / math.x;
		}*/
	return (resolve(math, res));
}
/*
int			get_dist_torus(t_line line, t_obj obj, t_v *res)
{
	int							i;
	double						a[5];
	double						z[8];
	gsl_poly_complex_workspace	*poly;
	double						m, n, o, p, q;
	t_v							x;
	double						diff;

	x = vect_sous(line.pos, obj.o);
	m = vect_scal(line.dir, line.dir);
	n = vect_scal(line.dir, x);
	o = vect_scal(x, x);
	p = vect_scal(line.dir, obj.norm);
	q = vect_scal(x, obj.norm);
	a[4] = m * m;
	a[3] = 4.0 * m * n;
	a[2] = 4.0 * m * m + 2.0 * m * o
		- 2.0 * (obj.radius * obj.radius + obj.radius2 * obj.radius2) * m
		+ 4.0 * obj.radius * obj.radius * p * p;
	a[1] = 4.0 * n * o
		- 4.0 * (obj.radius * obj.radius + obj.radius2 * obj.radius2) * n
		+ 8.0 * obj.radius * obj.radius * p * q;
	diff = (obj.radius * obj.radius - obj.radius2 * obj.radius2);
	a[0] = o * o
		- 2.0 * (obj.radius * obj.radius + obj.radius2 * obj.radius2) * o
		+ 4.0 * obj.radius * obj.radius * q * q + diff * diff;
	poly = gsl_poly_complex_workspace_alloc (5);
	if (gsl_poly_complex_solve(a, 5, poly, z) == GSL_SUCCESS)
	{
		i = -1;
		while (++i < 5)
		{
			if (z[2 * i] > 0.0 && z[2 * i + 1] == 0)
			{
	//			printf ("z%d = %+.18f %+.18f\n", i, z[2*i], z[2*i+1]);
				*res = z[2 * i];
				gsl_poly_complex_workspace_free(poly);
				return (1);
			}
		}
		return (1);
	}
	gsl_poly_complex_workspace_free(poly);
	return (0);
}
*/

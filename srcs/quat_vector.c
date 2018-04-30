/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 12:14:11 by cquillet          #+#    #+#             */
/*   Updated: 2017/10/23 17:13:14 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quat_vector.h"
#include <math.h>

t_quat		vect_to_quat(t_re a, t_vector v)
{
	t_quat	q;

	q.r = a;
	q.i = v.x;
	q.j = v.y;
	q.k = v.z;
	return (q);
}

t_vector	quat_to_vect(t_quat q)
{
	t_vector	v;

	v.x = q.i;
	v.y = q.j;
	v.z = q.k;
	return (v);
}

/*
** creation of a quaternion of rotation around an axis by an angle (in radians)
*/

t_quat		quat_rot(t_vector axis, t_re angle)
{
	t_re		c;
	t_re		s;

	c = (t_re)cos(angle / (t_re)2.0);
	s = (t_re)sin(angle / (t_re)2.0);
	return (vect_to_quat(c, vector_scalar(vector_unit(axis), s)));
}

/*
** rotation of a vector with a unit rotation quaternion
*/

t_vector	vect_rot(t_vector v, t_quat rot)
{
	t_quat		q;

	q = quat_mul(quat_mul(rot, vect_to_quat((t_re)0.0, v)), quat_conj(rot));
	return (quat_to_vect(q));
}

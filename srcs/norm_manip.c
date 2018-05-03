/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_manip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 00:27:48 by hbouchet          #+#    #+#             */
/*   Updated: 2018/05/03 04:02:04 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_v			rotation(t_v n, t_v r, float t)
{
	double	c;
	double	s;
	t_v		v;

	c = cos(t / 360 * 2 * M_PI);
	s = sin(t / 360 * 2 * M_PI);
	v.x = (r.x * r.x * (1 - c) + c) * n.x
		+ (r.x * r.y * (1 - c) - r.z * s) * n.y
		+ (r.x * r.z * (1 - c) + r.y * s) * n.z;
	v.y = (r.x * r.y * (1 - c) + r.z * s) * n.x
		+ (r.y * r.y * (1 - c) + c) * n.y
		+ (r.y * r.z * (1 - c) - r.x * s) * n.z;
	v.z = (r.x * r.z * (1 - c) - r.y * s) * n.x
		+ (r.y * r.z * (1 - c) + r.x * s) * n.y
		+ (r.z * r.z * (1 - c) + c) * n.z;
	return (v);
}

int			is_norm_wchar(double x, double y, double z)
{
	t_v		v_test;

	v_test.x = x;
	v_test.y = y;
	v_test.z = z;
	if (v_test.x || v_test.y || v_test.z)
		return (1);
	else
		return (0);
}

t_v			norm_vect(double x, double y, double z)
{
	t_v		vect;
	t_v		res;

	vect.x = x;
	vect.y = y;
	vect.z = z;
	res = vect_norm(vect);
	return (res);
}

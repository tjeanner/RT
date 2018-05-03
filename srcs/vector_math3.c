/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 03:27:53 by hbouchet          #+#    #+#             */
/*   Updated: 2018/05/03 04:02:04 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_v			vect_reflect(t_v incident, t_v normal)
{
	t_v		r;

	r = vect_sous(incident, vect_mult(normal, 2.0 *
												vect_scal(incident, normal)));
	return (r);
}

t_v			vect_refract(t_v incident, t_v normal, double k)
{
	t_v		t;
	double	c;
	double	s2;

	if (k == 0 || k > 1.)
		return (incident);
	c = -vect_scal(vect_norm(incident), vect_norm(normal));
	s2 = k * k * (1.0 - c * c);
	t = vect_add(vect_mult(incident, k), vect_mult(normal,
													k * c - sqrt(1.0 - s2)));
	return (t);
}

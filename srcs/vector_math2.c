/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 03:24:14 by hbouchet          #+#    #+#             */
/*   Updated: 2018/05/03 03:32:01 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		get_vect_norm(t_v a)
{
	double	n;

	n = sqrt(vect_scal(a, a));
	return (n);
}

t_v			vect_norm(t_v a)
{
	t_v		b;

	b = vect_div(a, get_vect_norm(a));
	return (b);
}

t_v			vect_mult(t_v a, double n)
{
	t_v		b;

	b.x = a.x * n;
	b.y = a.y * n;
	b.z = a.z * n;
	return (b);
}

t_v			vect_div(t_v a, double n)
{
	t_v		b;
	double	o;

	o = 1.000000 / n;
	b.x = a.x * o;
	b.y = a.y * o;
	b.z = a.z * o;
	return (b);
}

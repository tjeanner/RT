/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 18:20:50 by tjeanner          #+#    #+#             */
/*   Updated: 2018/04/15 14:09:20 by tjeanner         ###   ########.fr       */
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

t_v			vect_inv(t_v a)
{
	t_v		b;

	b.x = a.x * -1.0000000;
	b.y = a.y * -1.0000000;
	b.z = a.z * -1.0000000;
	return (b);
}

t_v			vect_add(t_v a, t_v b)
{
	t_v		c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_v			vect_sous(t_v a, t_v b)
{
	t_v		c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

double		vect_scal(t_v a, t_v b)
{
	double	n;

	n = a.x * b.x + a.y * b.y + a.z * b.z;
	return (n);
}

t_v			vect_prod(t_v a, t_v b)
{
	t_v		c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = -(a.x * b.z - a.z * b.x);
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

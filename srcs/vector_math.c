/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 18:20:50 by tjeanner          #+#    #+#             */
/*   Updated: 2018/05/03 04:02:04 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_v			vect_inv(t_v a)
{
	t_v		b;

	b.x = -a.x;
	b.y = -a.y;
	b.z = -a.z;
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

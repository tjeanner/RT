/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 22:38:50 by cquillet          #+#    #+#             */
/*   Updated: 2017/10/19 19:43:42 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"
#include <math.h>
#include "libft.h"

t_quat		quat_add(t_quat x, t_quat y)
{
	t_quat	sum;

	sum.r = x.r + y.r;
	sum.i = x.i + y.i;
	sum.j = x.j + y.j;
	sum.k = x.k + y.k;
	return (sum);
}

t_quat		quat_mul(t_quat x, t_quat y)
{
	t_quat	mul;

	mul.r = x.r * y.r - x.i * y.i - x.j * y.j - x.k * y.k;
	mul.i = x.j * y.k - y.j * x.k + x.r * y.i + y.r * x.i;
	mul.j = x.k * y.i - y.k * x.i + x.r * y.j + y.r * x.j;
	mul.k = x.i * y.j - y.i * x.j + x.r * y.k + y.r * x.k;
	return (mul);
}

t_quat		quat_div(t_quat x, t_quat y)
{
	return (quat_mul(x, quat_inv(y)));
}

void		quat_print(t_quat q)
{
	write(1, "QUAT {\n\tr= ", 11);
	ft_putnbr(q.r);
	write(1, "\n\ti= ", 5);
	ft_putnbr(q.i);
	write(1, "\n\tj= ", 5);
	ft_putnbr(q.j);
	write(1, "\n\tk= ", 5);
	ft_putnbr(q.k);
	write(1, "\n}\n", 3);
}

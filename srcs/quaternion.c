/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:33:54 by cquillet          #+#    #+#             */
/*   Updated: 2017/10/23 17:11:47 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"
#include <math.h>
#include "libft.h"

t_quat		quat_conj(t_quat x)
{
	t_quat	conj;

	conj.r = x.r;
	conj.i = -x.i;
	conj.j = -x.j;
	conj.k = -x.k;
	return (conj);
}

t_re		quat_mod(t_quat x)
{
	return ((x.r * x.r) + (x.i * x.i) + (x.j * x.j) + (x.k * x.k));
}

t_quat		quat_scalar(t_quat q, t_re a)
{
	t_quat	coeff;

	coeff.r = a * q.r;
	coeff.i = a * q.i;
	coeff.j = a * q.j;
	coeff.k = a * q.k;
	return (coeff);
}

t_quat		quat_inv(t_quat x)
{
	t_re	modulus;

	modulus = quat_mod(x);
	if (barely_zero(modulus))
		return (quat_scalar(x, 0.0));
	if (barely_equals(modulus, 1.0))
		return (quat_conj(x));
	return (quat_scalar(quat_conj(x), 1.0 / modulus));
}

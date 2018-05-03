/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 04:51:14 by tjeanner          #+#    #+#             */
/*   Updated: 2018/05/03 05:37:29 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		add_color(t_color a, t_color b)
{
	t_color		c;

	c.c.r = (a.c.r > 255 - b.c.r) ? 255 : a.c.r + b.c.r;
	c.c.g = (a.c.g > 255 - b.c.g) ? 255 : a.c.g + b.c.g;
	c.c.b = (a.c.b > 255 - b.c.b) ? 255 : a.c.b + b.c.b;
	c.c.a = (a.c.a > 255 - b.c.a) ? 255 : a.c.a + b.c.a;
	return (c);
}

t_color		sub_color(t_color a, t_color b)
{
	t_color		c;

	c.c.r = (b.c.r > a.c.r) ? 0 : a.c.r - b.c.r;
	c.c.g = (b.c.g > a.c.g) ? 0 : a.c.g - b.c.g;
	c.c.b = (b.c.b > a.c.b) ? 0 : a.c.b - b.c.b;
	c.c.a = (b.c.a > a.c.a) ? 0 : a.c.a - b.c.a;
	return (c);
}

t_color		mult_color(t_color a, float n)
{
	t_color		c;

	if (!n)
		return (get_black());
	c.c.r = (unsigned char)
					(((double)a.c.r > 255. / n) ? 255 : (float)a.c.r * n);
	c.c.g = (unsigned char)
					(((double)a.c.g > 255. / n) ? 255 : (float)a.c.g * n);
	c.c.b = (unsigned char)
					(((double)a.c.b > 255. / n) ? 255 : (float)a.c.b * n);
	c.c.a = (unsigned char)
					(((double)a.c.a > 255. / n) ? 255 : (float)a.c.a * n);
	return (c);
}

t_color		div_color(t_color a, float n)
{
	t_color		c;

	if (!n)
		return (get_white());
	c.c.r = (unsigned char)((float)a.c.r / n);
	c.c.g = (unsigned char)((float)a.c.g / n);
	c.c.b = (unsigned char)((float)a.c.b / n);
	c.c.a = (unsigned char)((float)a.c.a / n);
	return (c);
}

t_color		prod_color(t_color a, t_color b)
{
	t_color		c;

	c.c.r = (unsigned char)(sqrt((double)a.c.r * (double)b.c.r));
	c.c.g = (unsigned char)(sqrt((double)a.c.g * (double)b.c.g));
	c.c.b = (unsigned char)(sqrt((double)a.c.b * (double)b.c.b));
	c.c.a = (unsigned char)(sqrt((double)a.c.a * (double)b.c.a));
	return (c);
}

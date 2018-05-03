/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 04:51:14 by tjeanner          #+#    #+#             */
/*   Updated: 2018/05/03 04:01:52 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	satur_col(t_color a, float n)
{
	t_color		b;

	b = add_color(mult_color(a, n), mult_color(get_white(), 1.0 - n));
	return (b);
}

t_color	get_rand(void)
{
	t_color	c;

	c.c.r = rand() % 256;
	c.c.g = rand() % 256;
	c.c.b = rand() % 256;
	c.c.a = 0;
	return (c);
}

t_color	get_black(void)
{
	t_color	c;

	c.c.r = 0;
	c.c.g = 0;
	c.c.b = 0;
	c.c.a = 0;
	return (c);
}

t_color	get_white(void)
{
	t_color	c;

	c.c.r = 255;
	c.c.g = 255;
	c.c.b = 255;
	c.c.a = 0;
	return (c);
}

int		set_white(t_color *c)
{
	c->c.r = 255;
	c->c.g = 255;
	c->c.b = 255;
	c->c.a = 0;
	return (1);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 04:51:14 by tjeanner          #+#    #+#             */
/*   Updated: 2018/05/01 02:41:59 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color	satur_col(t_color a, float n)
{
	t_color		b;

	b = add_color(mult_color(a, n), mult_color(get_white(), 1.0 - n));
	return (b);
}

t_color	get_rand(void)
{
	t_color	c;

	c.c.r = rand() % 255;
	c.c.g = rand() % 255;
	c.c.b = rand() % 255;
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

int		set_black(t_color *c)
{
	c->c.r = 0;
	c->c.g = 0;
	c->c.b = 0;
	c->c.a = 0;
	c->u.r = 0;
	c->u.g = 0;
	c->u.b = 0;
	c->u.a = 0;
	return (1);
}

t_color		add_color(t_color a, t_color b)
{
	t_color		c;

	c.c.r = a.c.r + b.c.r;
	c.c.g = a.c.g + b.c.g;
	c.c.b = a.c.b + b.c.b;
	c.c.a = a.c.a + b.c.a;
	c.u.r = a.u.r + b.u.r;
	c.u.g = a.u.g + b.u.g;
	c.u.b = a.u.b + b.u.b;
	c.u.a = a.u.a + b.u.a;
	return (c);
}

t_color		div_color(t_color a, float n)
{
	t_color		c;

	c.c.r = a.c.r / n;
	c.c.g = a.c.g / n;
	c.c.b = a.c.b / n;
	c.c.a = a.c.a / n;
	c.u.r = a.u.r / n;
	c.u.g = a.u.g / n;
	c.u.b = a.u.b / n;
	c.u.a = a.u.a / n;
	return (c);
}

t_color		mult_color(t_color a, float n)
{
	t_color		c;

	c.c.r = a.c.r * n;
	c.c.g = a.c.g * n;
	c.c.b = a.c.b * n;
	c.c.a = a.c.a * n;
	c.u.r = a.u.r * n;
	c.u.g = a.u.g * n;
	c.u.b = a.u.b * n;
	c.u.a = a.u.a * n;
	return (c);
}

t_color		prod_color(t_color a, t_color b)
{
	t_color		c;

	c.c.r = a.c.r * b.c.r;
	c.c.g = a.c.g * b.c.g;
	c.c.b = a.c.b * b.c.b;
	c.c.a = a.c.a * b.c.a;
	c.u.r = a.u.r * b.u.r;
	c.u.g = a.u.g * b.u.g;
	c.u.b = a.u.b * b.u.b;
	c.u.a = a.u.a * b.u.a;
	return (c);
}

int			average_color(t_color *col, float flou)
{
	t_v		colo;
	int		c;

	flou *= flou;
	colo.x = col[0].c.r * flou;
	colo.y = col[0].c.g * flou;
	colo.z = col[0].c.b * flou;
	c = 0;
	while (++c < 1.0 / flou)
	{
		colo.x += col[c].c.r * flou;
		colo.y += col[c].c.g * flou;
		colo.z += col[c].c.b * flou;
	}
	col[0].c.r = colo.x;
	col[0].c.g = colo.y;
	col[0].c.b = colo.z;
	return (1);
}

void		sature_color(t_color *col, unsigned int saturation)
{
	double max;

	max = (double)saturation;
	col->u.r = col->u.r > max ? max : col->u.r;
	col->u.g = col->u.g > max ? max : col->u.g;
	col->u.b = col->u.b > max ? max : col->u.b;
//	col->u.a = col->u.a > max ? max : col->u.a;
/*	col->u.g = fmin(max *, col->u.g);
	col->u.b = fmin(max *, col->u.b);
	col->u.a = fmin(max *, col->u.a);*/
	*col = div_color(*col, max);
	col->c.r = (unsigned char)(col->u.r * 255.);
	col->c.g = (unsigned char)(col->u.g * 255.);
	col->c.b = (unsigned char)(col->u.b * 255.);
//	col->c.a = (unsigned char)col->u.a;
	col->c.a = 0;
}

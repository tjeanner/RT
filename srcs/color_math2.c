/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 02:40:17 by hbouchet          #+#    #+#             */
/*   Updated: 2018/05/01 02:42:16 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			set_black(t_color *c)
{
	c->c.r = 0;
	c->c.g = 0;
	c->c.b = 0;
	c->c.a = 0;
	return (1);
}

t_color		add_color(t_color a, t_color b)
{
	t_color		c;

	c.c.r = a.c.r + b.c.r;
	c.c.g = a.c.g + b.c.g;
	c.c.b = a.c.b + b.c.b;
	c.c.a = a.c.a + b.c.a;
	return (c);
}

t_color		div_color(t_color a, float n)
{
	t_color		c;

	c.c.r = a.c.r / n;
	c.c.g = a.c.g / n;
	c.c.b = a.c.b / n;
	c.c.a = a.c.a / n;
	return (c);
}

t_color		mult_color(t_color a, float n)
{
	t_color		c;

	c.c.r = a.c.r * n;
	c.c.g = a.c.g * n;
	c.c.b = a.c.b * n;
	c.c.a = a.c.a * n;
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

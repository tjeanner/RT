/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 05:27:18 by cquillet          #+#    #+#             */
/*   Updated: 2018/05/03 05:35:22 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		satur_col(t_color a, float n)
{
	t_color		b;

	b = add_color(mult_color(a, n), mult_color(get_white(), 1.0 - n));
	return (b);
}

int			average_color(t_color *col, float flou)
{
	t_v			colo;
	int			c;

	if (!flou)
	{
		*col = get_black();
		return (1);
	}
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

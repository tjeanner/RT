/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 05:27:18 by cquillet          #+#    #+#             */
/*   Updated: 2018/05/04 02:33:31 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		satur_col(t_color a, float n)
{
	t_color		b;

	b = add_color(mult_color(a, n), mult_color(get_white(), 1.0 - n));
	return (b);
}

t_color		average_color(t_color *col, float flou)
{
	t_color		colo;
	t_v			tmp;
	int			c;

	colo = get_black();
	if (flou < 1)
	{
		tmp.x = col[0].c.r;
		tmp.y = col[0].c.g;
		tmp.z = col[0].c.b;
		c = 0;
		while (++c < 1.0 / flou)
		{
			tmp.x += col[c].c.r;
			tmp.y += col[c].c.g;
			tmp.z += col[c].c.b;
		}
		colo.c.r = tmp.x * flou;
		colo.c.g = tmp.y * flou;
		colo.c.b = tmp.z * flou;
	}
	free(col);
	return (colo);
}

t_color		gamma_korr(t_color a, double gamma)
{
	t_color	c;

	c.c.r = (unsigned int)(pow(((double)a.c.r / 255.), gamma) * 255.);
	c.c.g = (unsigned int)(pow(((double)a.c.g / 255.), gamma) * 255.);
	c.c.b = (unsigned int)(pow(((double)a.c.b / 255.), gamma) * 255.);
	c.c.a = (unsigned int)(pow(((double)a.c.a / 255.), gamma) * 255.);
	return (c);
}

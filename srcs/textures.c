/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 22:57:17 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/29 23:01:57 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		checkerboard(t_ray *line)
{
	t_v		lol;

	lol.x = ((int)((line->to.pos.x) / 100) % 2) ? 0 : 1;
	lol.y = ((int)((line->to.pos.y) / 100) % 2) ? 0 : 1;
	lol.z = ((int)((line->to.pos.z) / 100) % 2) ? 0 : 1;
	lol.x = (line->to.pos.x < 0) ? 1 - lol.x : lol.x;
	lol.y = (line->to.pos.y < 0) ? 1 - lol.y : lol.y;
	lol.z = (line->to.pos.z < 0) ? 1 - lol.z : lol.z;
	if ((int)lol.x ^ (int)lol.y ^ (int)lol.z)
		return (0.75);
	else
		return (1);
}
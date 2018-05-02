/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 18:17:30 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/29 01:02:57 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	stereo_filter(t_env *env)
{
	size_t			i;
	unsigned int	max;
	unsigned char	*data;
	unsigned char	*data2;

	color_filter(env, env->display.surf, get_color("00FFFF"));
	color_filter(env, env->display.surf2, get_color("FF0000"));
	data = (unsigned char *)env->display.surf->pixels;
	data2 = (unsigned char *)env->display.surf2->pixels;
	max = ((WIN_X * WIN_Y) * 4) - 4;
	i = 0;
	while (i < max)
	{
		data[i] = (data[i] + data2[i]);
		data[i + 1] = (data[i + 1] + data2[i + 1]);
		data[i + 2] = (data[i + 2] + data2[i + 2]);
		i += 4;
	}
}

void	motionblur_filter(t_env *env)
{
	int				x;
	int				moyenne;
	int				i, tmp;
	unsigned char 	*data;
	int				y;

	i = 0;
	data = (unsigned char *)env->display.surf->pixels;
	while (i < (WIN_Y * WIN_X) * 4)
	{
		x = 0;
		moyenne = 0;
		while (x < 20)
		{
			y = 0;
			while (y < 20)
			{
				tmp = i + x + (y * WIN_X);
				if (tmp > 0 && tmp < WIN_X * WIN_Y * 4)
				{
					moyenne += (data[tmp]);
					if (data[tmp] < 0)
						moyenne += 256;
				}
				y += 4;
			}
			x += 4;
		}
		moyenne /= 25;
		data[i] = moyenne;
		i++;
	}
}

void	cartoon_filter(t_env *env)
{
	size_t			i;
	unsigned int	max;
	unsigned char 	*data;
	int				pas;

	data = (unsigned char *)env->display.surf->pixels;
	max = ((WIN_X * WIN_Y) * 4);
	i = 0;
	if (env->effects.seuil <= 4 || env->effects.seuil >= 15)
		env->effects.seuil = 8;
	pas = 255 / env->effects.seuil;
	while (i < max)
	{
		data[i] = (int)(data[i] / pas) * pas;
		i++;
	}
}

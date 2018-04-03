/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:21:32 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/01 23:15:12 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	bw_filter(t_env *env)
{
	size_t			i;
	unsigned int	moy;
	unsigned int	max;
	unsigned char	*data;

	data = (unsigned char *)env->surf->pixels;
	max = ((WIN_X * WIN_Y) * 4) - 4;
	i = 0;
	while (i < max)
	{
		moy = (data[i] + data[i + 1] + data[i + 2]) / 3;
		data[i] = moy;
		data[i + 1] = moy;
		data[i + 2] = moy;
		i += 4;
	}
}

void	sobel_filter(t_env *env)
{
	int	y;
	int x;
	int gx, gy, gn;
	unsigned int *data;
	unsigned int *tmp = NULL;

	tmp = malloc(sizeof(unsigned int) * WIN_X * WIN_Y);
	data = (unsigned int *)env->surf->pixels;
	ft_bzero(tmp, sizeof(tmp));
	y = 1;
	while (y < WIN_Y - 1)
	{
		x = 1;
		while (x < WIN_X - 1)
		{
			gx = ((data[(y - 1) * WIN_X + x + 1] - data[(y - 1) * WIN_X + x - 1]) + 3 
					* (data[(y) * WIN_X + x + 1] - data[(y) * WIN_X + x - 1])
					+ (data[(y + 1) * WIN_X + x + 1] - data[(y + 1) * WIN_X + x - 1]))
				* 3;
			gy = ((data[(y + 1) * WIN_X + x - 1] - data[(y - 1) * WIN_X + x - 1]) + 3 
					* (data[(y + 1) * WIN_X + x] - data[(y - 1) * WIN_X + x])
					+ (data[(y + 1) * WIN_X + x + 1] - data[(y - 1) * WIN_X + x + 1]))
				* 3;
			gn = (unsigned int)sqrt(gx * gx + gy * gy);
			tmp[(y * WIN_X) + x] = gn;
			x++;
		}
		y++;
	}
	y = 1;
	while (y < WIN_Y)
	{
		x = 1;
		while (x < WIN_X)
		{
			if (tmp[(y * WIN_X) + x] > 1)
				data[(y * WIN_X) + x] =  get_black().color;
//			data[(y * WIN_X) + x] = tmp[(y * WIN_X) + x];
			x++;
		}
		y++;
	}
}

void	cartoon_filter(t_env *env)
{
	size_t			i;
	unsigned int	max;
	unsigned char 	*data;
	int				pas;

	data = (unsigned char *)env->surf->pixels;
	max = ((WIN_X * WIN_Y) * 4);
	i = 0;
	pas = 255 / env->seuil;
	while (i < max)
	{
		data[i] = (int)(data[i] / pas) * pas;
		i++;
	}
//	sobel_filter(env);
}

void	sepia_filter(t_env *env)
{
	size_t			i;
	unsigned int	moy;
	unsigned int	max;
	unsigned char	*data;

	data = (unsigned char *)env->surf->pixels;
	max = ((WIN_X * WIN_Y) * 4) - 4;
	i = 0;
	while (i < max)
	{
		moy = (data[i] + data[i + 1] + data[i + 2]) / 3;
		data[i] = 0.635 * moy;
		data[i + 1] = 0.887 * moy;
		data[i + 2] =  moy;
		i += 4;
	}
}

void	neg_filter(t_env *env)
{
	size_t			i;
	unsigned int	max;
	unsigned char	*data;

	data = (unsigned char *)env->surf->pixels;
	max = ((WIN_X * WIN_Y) * 4) - 4;
	i = 0;
	while (i < max)
	{
		data[i] = 255 - data[i];
		data[i + 1] = 255 - data[i + 1];
		data[i + 2] = 255 - data[i + 2];
		i += 4;
	}
}


void	set_filter(t_env *env)
{
	if (!ft_strcmp(env->filter, "NEGATIVE"))
		neg_filter(env);
	else if (!ft_strcmp(env->filter, "B&W"))
		bw_filter(env);
	else if (!ft_strcmp(env->filter, "SEPIA"))
		sepia_filter(env);
	else if (!ft_strncmp(env->filter, "CARTOON", 7))
	{
		if (!ft_strncmp(env->filter, "CARTOON:", 8) && ft_strlen(env->filter) > 8)
			env->seuil = ft_atoi(env->filter + 8);
		else
			env->seuil = 8;
//			sobel_filter(env);
		cartoon_filter(env);
	}
}

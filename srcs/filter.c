/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:21:32 by hbouchet          #+#    #+#             */
/*   Updated: 2018/03/27 17:08:49 by hbouchet         ###   ########.fr       */
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
	if (env->filter == 1)
		neg_filter(env);
	else if (env->filter == 2)
		bw_filter(env);
	else if (env->filter == 3)
		sepia_filter(env);
}
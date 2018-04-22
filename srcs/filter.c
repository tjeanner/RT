/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:21:32 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/22 20:33:01 by hbouchet         ###   ########.fr       */
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

void	color_filter(t_env *env, SDL_Surface *surf, t_color color)
{
	size_t			i;
	unsigned int	max;
	unsigned char	*data;

	(void)env;
	data = (unsigned char *)surf->pixels;
	max = ((WIN_X * WIN_Y) * 4) - 4;
	i = 0;
	while (i < max)
	{
		data[i] = data[i] * (color.c.b) / 255;
		data[i + 1] = data[i + 1] * (color.c.g) / 255;
		data[i + 2] = data[i + 2] * (color.c.r) / 255;
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
	else if (!ft_strcmp(env->filter, "MOTIONBLUR"))
		motionblur_filter(env);
	else if (!ft_strcmp(env->filter, "3D"))
		stereo_filter(env);
	else if (!ft_strncmp(env->filter, "CARTOON", 7))
	{
		if (!ft_strncmp(env->filter, "CARTOON:", 8) && ft_strlen(env->filter) > 8)
			env->seuil = ft_atoi(env->filter + 8);
		else
			env->seuil = 8;
		cartoon_filter(env);
	}
	if (ft_strcmp(env->filter, "3D") && env->cams[env->curr_cam].col.color && env->cams[env->curr_cam].col.color != 16777216)
		color_filter(env, env->surf, env->cams[env->curr_cam].col);
}

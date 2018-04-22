/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 18:17:30 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/22 06:13:40 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	stereo_filter(t_env *env)
{
	size_t			i;
	unsigned int	max;
	unsigned char	*data;
	unsigned char	*data2;

//	env->cams[env->curr_cam].col = get_color("FF0000");
//	env->cams[env->curr_cam + 1].col = get_color("00FFFF");
	color_filter(env, env->surf, get_color("FF0000"));
	color_filter(env, env->surf2, get_color("00FFfF"));
	data = (unsigned char *)env->surf->pixels;
	data2 = (unsigned char *)env->surf2->pixels;
	max = ((WIN_X * WIN_Y) * 4) - 4;
	i = 0;
	printf("%d\n", data[i + 2]);
	printf("%d\n", data2[i + 2]);
	while (i < max)
	{
		data[i] = (data[i] + data2[i]);
		data[i + 1] = (data[i + 1] + data2[i + 1]);
		data[i + 2] = (data[i + 2] + data2[i + 2]);
		i += 4;
//		data[i] = data2[i]; i++;
	}
}

void	motionblur_filter(t_env *env)
{
	(void)env;
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
	if (env->seuil <= 4 || env->seuil >= 15)
		env->seuil = 8;
	pas = 255 / env->seuil;
	while (i < max)
	{
		data[i] = (int)(data[i] / pas) * pas;
		i++;
	}
}
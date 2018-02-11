/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 01:37:44 by hbouchet          #+#    #+#             */
/*   Updated: 2018/02/11 04:16:15 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	scene_generator(t_env *env)
{
	int	i_cam;

	i_cam = 0;
	while (i_cam < env->nb_cam)
	{
		ft_putstr("cam:");
		ft_putnbr(env->cams[i_cam].pos_cam.x);
		ft_putchar('\n');
		i_cam++;
	}
}

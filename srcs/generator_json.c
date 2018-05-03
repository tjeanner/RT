/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_json.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 01:37:44 by hbouchet          #+#    #+#             */
/*   Updated: 2018/05/03 04:02:04 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	j_print_cam(t_env *env, int i, int fd)
{
	env->cams.cam[i].vcam = vect_norm(env->cams.cam[i].vcam);
	env->cams.cam[i].v2cam = vect_norm(env->cams.cam[i].v2cam);
	env->cams.cam[i].v3cam = vect_norm(env->cams.cam[i].v3cam);
	ft_putstr_fd("\n\t\t{\n\t\t\t\"pos\":", fd);
	j_print_vec(env->cams.cam[i].pos, fd);
	ft_putstr_fd(",\n\t\t\t\"color\":\"", fd);
	j_print_color(env->cams.cam[i].col, fd);
	ft_putstr_fd("\",\n\t\t\t\"v\":", fd);
	j_print_vec(env->cams.cam[i].vcam, fd);
	ft_putstr_fd(",\n\t\t\t\"v2\":", fd);
	j_print_vec(env->cams.cam[i].v2cam, fd);
	ft_putstr_fd("}", fd);
}

void	j_print_lum(t_env *env, int i, int fd)
{
	ft_putstr_fd("\n\t\t{\n\t\t\t\"color\":\"", fd);
	j_print_color(env->lums.lum[i].col, fd);
	ft_putstr_fd("\",\n\t\t\t\"intensity\":", fd);
	ft_putfloat_fd(env->lums.lum[i].coef, fd);
	if (get_vect_norm(env->lums.lum[i].dir) != 0)
	{
		ft_putstr_fd(",\n\t\t\t\"type\":\"PARALLEL\"", fd);
		ft_putstr_fd(",\n\t\t\t\"dir\":", fd);
		j_print_vec(env->lums.lum[i].dir, fd);
	}
	ft_putstr_fd(",\n\t\t\t\"pos\":", fd);
	j_print_vec(env->lums.lum[i].pos, fd);
	ft_putstr_fd("}", fd);
}

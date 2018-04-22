/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_json.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 01:37:44 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/22 19:58:26 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	j_print_cam(t_env *env, int i, int fd)
{
	ft_putstr_fd("{\"pos\":{\"x\":", fd);
	ft_putfloat_fd(env->cams[i].pos.x, fd);
	ft_putstr_fd(",\"y\":", fd);
	ft_putfloat_fd(env->cams[i].pos.y, fd);
	ft_putstr_fd(",\"z\":", fd);
	ft_putfloat_fd(env->cams[i].pos.z, fd);
	ft_putstr_fd("},\"color\":\"", fd);
	if (env->cams[i].col.c.r < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->cams[i].col.c.r, 16, fd);
	if (env->cams[i].col.c.g < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->cams[i].col.c.g, 16, fd);
	if (env->cams[i].col.c.b < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->cams[i].col.c.b, 16, fd);
	ft_putstr_fd("\",\"v\":{\"x\":", fd);
	ft_putfloat_fd(env->cams[i].vcam.x, fd);
	ft_putstr_fd(",\"y\":", fd);
	ft_putfloat_fd(env->cams[i].vcam.y, fd);
	ft_putstr_fd(",\"z\":", fd);
	ft_putfloat_fd(env->cams[i].vcam.z, fd);
	ft_putstr_fd("},\"v2\":{\"x\":", fd);
	ft_putfloat_fd(env->cams[i].v2cam.x, fd);
	ft_putstr_fd(",\"y\":", fd);
	ft_putfloat_fd(env->cams[i].v2cam.y, fd);
	ft_putstr_fd(",\"z\":", fd);
	ft_putfloat_fd(env->cams[i].v2cam.z, fd);
	ft_putstr_fd("}}", fd);
}

void	j_print_lum(t_env *env, int i, int fd)
{
	ft_putstr_fd("{\"color\":\"", fd);
	if (env->lums[i].col.c.r < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->lums[i].col.c.r, 16, fd);
	if (env->lums[i].col.c.g < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->lums[i].col.c.g, 16, fd);
	if (env->lums[i].col.c.b < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->lums[i].col.c.b, 16, fd);
	ft_putstr_fd("\",\"pos\":{\"x\":", fd);
	ft_putfloat_fd(env->lums[i].pos.x, fd);
	ft_putstr_fd(",\"y\":", fd);
	ft_putfloat_fd(env->lums[i].pos.y, fd);
	ft_putstr_fd(",\"z\":", fd);
	ft_putfloat_fd(env->lums[i].pos.z, fd);
	ft_putstr_fd("}}", fd);
}

void	j_print_d_obj(t_env *env, int i, int fd)
{
	ft_putstr_fd("{\"type\":\"", fd);
	if (env->objs[i].type == 's')
		ft_putstr_fd("sphere\",", fd);
	else if (env->objs[i].type == 'p')
		ft_putstr_fd("plane\",", fd);
	else if (env->objs[i].type == 'c')
		ft_putstr_fd("cone\",", fd);
	else if (env->objs[i].type == 't')
		ft_putstr_fd("cylindre\",", fd);
	ft_putstr_fd("\"pos\":{\"x\":", fd);
	ft_putfloat_fd(env->objs[i].o.x, fd);
	ft_putstr_fd(",\"y\":", fd);
	ft_putfloat_fd(env->objs[i].o.y, fd);
	ft_putstr_fd(",\"z\":", fd);
	ft_putfloat_fd(env->objs[i].o.z, fd);
	if (env->objs[i].type != 's')
	{
		ft_putstr_fd("},\"norm\":{\"x\":", fd);
		ft_putfloat_fd(env->objs[i].norm.x, fd);
		ft_putstr_fd(",\"y\":", fd);
		ft_putfloat_fd(env->objs[i].norm.y, fd);
		ft_putstr_fd(",\"z\":", fd);
		ft_putfloat_fd(env->objs[i].norm.z, fd);
	}
}

void	j_print_obj(t_env *env, int i, int fd)
{
	j_print_d_obj(env, i, fd);
	ft_putstr_fd("},\"radius\":", fd);
	ft_putfloat_fd(env->objs[i].radius, fd);
	ft_putstr_fd(",\"color\":\"", fd);
	if (env->objs[i].col.c.r < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->objs[i].col.c.r, 16, fd);
	if (env->objs[i].col.c.g < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->objs[i].col.c.g, 16, fd);
	if (env->objs[i].col.c.b < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->objs[i].col.c.b, 16, fd);
	ft_putstr_fd("\"}", fd);
}

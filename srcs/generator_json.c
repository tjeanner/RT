/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_json.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 01:37:44 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/25 11:15:52 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	j_print_cam(t_env *env, int i, int fd)
{
	ft_putstr_fd("{\"pos\":{\"x\":", fd);
	ft_putfloat_fd(env->cams.cam[i].pos.x, fd);
	ft_putstr_fd(",\"y\":", fd);
	ft_putfloat_fd(env->cams.cam[i].pos.y, fd);
	ft_putstr_fd(",\"z\":", fd);
	ft_putfloat_fd(env->cams.cam[i].pos.z, fd);
	ft_putstr_fd("},\"color\":\"", fd);
	if (env->cams.cam[i].col.c.r < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->cams.cam[i].col.c.r, 16, fd);
	if (env->cams.cam[i].col.c.g < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->cams.cam[i].col.c.g, 16, fd);
	if (env->cams.cam[i].col.c.b < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->cams.cam[i].col.c.b, 16, fd);
	ft_putstr_fd("\",\"v\":{\"x\":", fd);
	ft_putfloat_fd(env->cams.cam[i].vcam.x, fd);
	ft_putstr_fd(",\"y\":", fd);
	ft_putfloat_fd(env->cams.cam[i].vcam.y, fd);
	ft_putstr_fd(",\"z\":", fd);
	ft_putfloat_fd(env->cams.cam[i].vcam.z, fd);
	ft_putstr_fd("},\"v2\":{\"x\":", fd);
	ft_putfloat_fd(env->cams.cam[i].v2cam.x, fd);
	ft_putstr_fd(",\"y\":", fd);
	ft_putfloat_fd(env->cams.cam[i].v2cam.y, fd);
	ft_putstr_fd(",\"z\":", fd);
	ft_putfloat_fd(env->cams.cam[i].v2cam.z, fd);
	ft_putstr_fd("}}", fd);
}

void	j_print_lum(t_env *env, int i, int fd)
{
	ft_putstr_fd("{\"color\":\"", fd);
	if (env->lums.lum[i].col.c.r < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->lums.lum[i].col.c.r, 16, fd);
	if (env->lums.lum[i].col.c.g < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->lums.lum[i].col.c.g, 16, fd);
	if (env->lums.lum[i].col.c.b < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->lums.lum[i].col.c.b, 16, fd);
	ft_putstr_fd("\",\"pos\":{\"x\":", fd);
	ft_putfloat_fd(env->lums.lum[i].pos.x, fd);
	ft_putstr_fd(",\"y\":", fd);
	ft_putfloat_fd(env->lums.lum[i].pos.y, fd);
	ft_putstr_fd(",\"z\":", fd);
	ft_putfloat_fd(env->lums.lum[i].pos.z, fd);
	ft_putstr_fd("}}", fd);
}

void	j_print_d_obj(t_env *env, int i, int fd)
{
	ft_putstr_fd("{\"type\":\"", fd);
	if (env->objs.obj[i].type == 's')
		ft_putstr_fd("sphere\",", fd);
	else if (env->objs.obj[i].type == 'p')
		ft_putstr_fd("plane\",", fd);
	else if (env->objs.obj[i].type == 'c')
		ft_putstr_fd("cone\",", fd);
	else if (env->objs.obj[i].type == 't')
		ft_putstr_fd("cylindre\",", fd);
	ft_putstr_fd("\"pos\":{\"x\":", fd);
	ft_putfloat_fd(env->objs.obj[i].o.x, fd);
	ft_putstr_fd(",\"y\":", fd);
	ft_putfloat_fd(env->objs.obj[i].o.y, fd);
	ft_putstr_fd(",\"z\":", fd);
	ft_putfloat_fd(env->objs.obj[i].o.z, fd);
	if (env->objs.obj[i].type != 's')
	{
		ft_putstr_fd("},\"norm\":{\"x\":", fd);
		ft_putfloat_fd(env->objs.obj[i].norm.x, fd);
		ft_putstr_fd(",\"y\":", fd);
		ft_putfloat_fd(env->objs.obj[i].norm.y, fd);
		ft_putstr_fd(",\"z\":", fd);
		ft_putfloat_fd(env->objs.obj[i].norm.z, fd);
	}
}

void	j_print_obj(t_env *env, int i, int fd)
{
	j_print_d_obj(env, i, fd);
	ft_putstr_fd("},\"radius\":", fd);
	ft_putfloat_fd(env->objs.obj[i].radius, fd);
	ft_putstr_fd(",\"color\":\"", fd);
	if (env->objs.obj[i].col.c.r < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->objs.obj[i].col.c.r, 16, fd);
	if (env->objs.obj[i].col.c.g < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->objs.obj[i].col.c.g, 16, fd);
	if (env->objs.obj[i].col.c.b < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->objs.obj[i].col.c.b, 16, fd);
	ft_putstr_fd("\"}", fd);
}

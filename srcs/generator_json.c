/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_json.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 01:37:44 by hbouchet          #+#    #+#             */
/*   Updated: 2018/05/02 18:11:30 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	j_print_cam(t_env *env, int i, int fd)
{
	ft_putstr_fd("\n\t\t{\n\t\t\t\"pos\":{\n\t\t\t\t\"x\":", fd);
	ft_putfloat_fd(env->cams.cam[i].pos.x, fd);
	ft_putstr_fd(",\n\t\t\t\t\"y\":", fd);
	ft_putfloat_fd(env->cams.cam[i].pos.y, fd);
	ft_putstr_fd(",\n\t\t\t\t\"z\":", fd);
	ft_putfloat_fd(env->cams.cam[i].pos.z, fd);
	ft_putstr_fd("},\n\t\t\t\"color\":\"", fd);
	if (env->cams.cam[i].col.c.r < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->cams.cam[i].col.c.r, 16, fd);
	if (env->cams.cam[i].col.c.g < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->cams.cam[i].col.c.g, 16, fd);
	if (env->cams.cam[i].col.c.b < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->cams.cam[i].col.c.b, 16, fd);
	ft_putstr_fd("\",\n\t\t\t\"v\":{\n\t\t\t\t\"x\":", fd);
	ft_putfloat_fd(env->cams.cam[i].vcam.x, fd);
	ft_putstr_fd(",\n\t\t\t\t\"y\":", fd);
	ft_putfloat_fd(env->cams.cam[i].vcam.y, fd);
	ft_putstr_fd(",\n\t\t\t\t\"z\":", fd);
	ft_putfloat_fd(env->cams.cam[i].vcam.z, fd);
	ft_putstr_fd("},\n\t\t\t\"v2\":{\n\t\t\t\t\"x\":", fd);
	ft_putfloat_fd(env->cams.cam[i].v2cam.x, fd);
	ft_putstr_fd(",\n\t\t\t\t\"y\":", fd);
	ft_putfloat_fd(env->cams.cam[i].v2cam.y, fd);
	ft_putstr_fd(",\n\t\t\t\t\"z\":", fd);
	ft_putfloat_fd(env->cams.cam[i].v2cam.z, fd);
	ft_putstr_fd("}}", fd);
}

void	j_print_lum(t_env *env, int i, int fd)
{
	ft_putstr_fd("\n\t\t{\n\t\t\t\"color\":\"", fd);
	if (env->lums.lum[i].col.c.r < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->lums.lum[i].col.c.r, 16, fd);
	if (env->lums.lum[i].col.c.g < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->lums.lum[i].col.c.g, 16, fd);
	if (env->lums.lum[i].col.c.b < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->lums.lum[i].col.c.b, 16, fd);
	ft_putstr_fd("\",\n\t\t\t\"intensity\":", fd);
	ft_putfloat_fd(env->lums.lum[i].coef, fd);
	ft_putstr_fd(",\n\t\t\t\"pos\":{\n\t\t\t\t\"x\":", fd);
	ft_putfloat_fd(env->lums.lum[i].pos.x, fd);
	ft_putstr_fd(",\n\t\t\t\t\"y\":", fd);
	ft_putfloat_fd(env->lums.lum[i].pos.y, fd);
	ft_putstr_fd(",\n\t\t\t\t\"z\":", fd);
	ft_putfloat_fd(env->lums.lum[i].pos.z, fd);
	ft_putstr_fd("}}", fd);
}

void	j_print_d_obj(t_env *env, int i, int fd)
{
	ft_putstr_fd("\n\t\t{\n\t\t\t\"type\":\"", fd);
	if (env->objs.obj[i].type == SPHERE)
		ft_putstr_fd("sphere\",", fd);
	else if (env->objs.obj[i].type == PLANE)
		ft_putstr_fd("plane\",", fd);
	else if (env->objs.obj[i].type == CONE)
		ft_putstr_fd("cone\",", fd);
	else if (env->objs.obj[i].type == CYLINDRE)
		ft_putstr_fd("cylindre\",", fd);
	ft_putstr_fd("\n\t\t\t\"pos\":{\n\t\t\t\t\"x\":", fd);
	ft_putfloat_fd(env->objs.obj[i].o.x, fd);
	ft_putstr_fd(",\n\t\t\t\t\"y\":", fd);
	ft_putfloat_fd(env->objs.obj[i].o.y, fd);
	ft_putstr_fd(",\n\t\t\t\t\"z\":", fd);
	ft_putfloat_fd(env->objs.obj[i].o.z, fd);
	if (env->objs.obj[i].type != SPHERE)
	{
		ft_putstr_fd("},\n\t\t\t\"norm\":{\n\t\t\t\t\"x\":", fd);
		ft_putfloat_fd(env->objs.obj[i].norm.x, fd);
		ft_putstr_fd(",\n\t\t\t\t\"y\":", fd);
		ft_putfloat_fd(env->objs.obj[i].norm.y, fd);
		ft_putstr_fd(",\n\t\t\t\t\"z\":", fd);
		ft_putfloat_fd(env->objs.obj[i].norm.z, fd);
	}
}

void	j_print_obj(t_env *env, int i, int fd)
{
	j_print_d_obj(env, i, fd);
	ft_putstr_fd("},\n\t\t\t\"radius\":", fd);
	ft_putfloat_fd(env->objs.obj[i].radius, fd);
	ft_putstr_fd(",\n\t\t\t\"reflect\":", fd);
	ft_putfloat_fd(env->objs.obj[i].reflect, fd);
	ft_putstr_fd(",\n\t\t\t\"refract\":", fd);
	ft_putfloat_fd(env->objs.obj[i].refract, fd);
	ft_putstr_fd(",\n\t\t\t\"color\":\"", fd);
	if (env->objs.obj[i].col.c.r < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->objs.obj[i].col.c.r, 16, fd);
	if (env->objs.obj[i].col.c.g < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->objs.obj[i].col.c.g, 16, fd);
	if (env->objs.obj[i].col.c.b < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->objs.obj[i].col.c.b, 16, fd);
	ft_putstr_fd("\"\n\t\t\t}", fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_print_obj.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 18:44:52 by hbouchet          #+#    #+#             */
/*   Updated: 2018/05/04 01:47:43 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	j_print_vec(t_v v, int fd)
{
	ft_putstr_fd("{\n\t\t\t\t\"x\":", fd);
	ft_putfloat_fd(v.x, fd);
	ft_putstr_fd(",\n\t\t\t\t\"y\":", fd);
	ft_putfloat_fd(v.y, fd);
	ft_putstr_fd(",\n\t\t\t\t\"z\":", fd);
	ft_putfloat_fd(v.z, fd);
	ft_putstr_fd("}", fd);
}

void	j_print_color(t_color color, int fd)
{
	if (color.c.r < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(color.c.r, 16, fd);
	if (color.c.g < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(color.c.g, 16, fd);
	if (color.c.b < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(color.c.b, 16, fd);
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
	ft_putstr_fd("\n\t\t\t\"pos\":", fd);
	j_print_vec(env->objs.obj[i].o, fd);
	if (env->objs.obj[i].type != SPHERE)
	{
		ft_putstr_fd(",\n\t\t\t\"norm\":", fd);
		j_print_vec(env->objs.obj[i].norm, fd);
	}
	if (env->objs.obj[i].mat.tex == 1)
		ft_putstr_fd(",\n\t\t\t\"texture\":\"CHESS\"", fd);
}

void	j_print_obj(t_env *env, int i, int fd)
{
	j_print_d_obj(env, i, fd);
	ft_putstr_fd(",\n\t\t\t\"radius\":", fd);
	ft_putfloat_fd(env->objs.obj[i].radius, fd);
	ft_putstr_fd(",\n\t\t\t\"roughness\":", fd);
	ft_putfloat_fd(env->objs.obj[i].mat.rough, fd);
	ft_putstr_fd(",\n\t\t\t\"diffuse\":", fd);
	ft_putfloat_fd(env->objs.obj[i].k_diff, fd);
	ft_putstr_fd(",\n\t\t\t\"specular\":", fd);
	ft_putfloat_fd(env->objs.obj[i].k_spec, fd);
	ft_putstr_fd(",\n\t\t\t\"transparency\":", fd);
	ft_putfloat_fd(env->objs.obj[i].transp, fd);
	ft_putstr_fd(",\n\t\t\t\"plasticity\":", fd);
	ft_putfloat_fd(env->objs.obj[i].mat.plastic, fd);
	ft_putstr_fd(",\n\t\t\t\"reflect\":", fd);
	ft_putfloat_fd(env->objs.obj[i].reflect, fd);
	ft_putstr_fd(",\n\t\t\t\"refract\":", fd);
	ft_putfloat_fd(env->objs.obj[i].refract, fd);
	ft_putstr_fd(",\n\t\t\t\"color\":\"", fd);
	j_print_color(env->objs.obj[i].col, fd);
	ft_putstr_fd("\"\n\t\t\t}", fd);
}

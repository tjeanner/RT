/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 01:37:44 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/02 00:13:05 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	print_cam(t_env *env, int i, int fd)
{
	ft_putstr_fd("cam:", fd);
	ft_putfloat_fd(env->cams[i].pos_cam.x, fd);
	ft_putchar_fd(':', fd);
	ft_putfloat_fd(env->cams[i].pos_cam.y, fd);
	ft_putchar_fd(':', fd);
	ft_putfloat_fd(env->cams[i].pos_cam.z, fd);
	ft_putchar_fd(':', fd);
	ft_putfloat_fd(env->cams[i].vcam.x, fd);
	ft_putchar_fd(':', fd);
	ft_putfloat_fd(env->cams[i].vcam.y, fd);
	ft_putchar_fd(':', fd);
	ft_putfloat_fd(env->cams[i].vcam.z, fd);
	ft_putchar_fd(':', fd);
	ft_putfloat_fd(env->cams[i].v2cam.x, fd);
	ft_putchar_fd(':', fd);
	ft_putfloat_fd(env->cams[i].v2cam.y, fd);
	ft_putchar_fd(':', fd);
	ft_putfloat_fd(env->cams[i].v2cam.z, fd);
	ft_putchar_fd('\n', fd);
}

static void	print_lum(t_env *env, int i, int fd)
{
	ft_putstr_fd("lum:", fd);
	ft_putfloat_fd(env->lums[i].pos_lum.x, fd);
	ft_putchar_fd(':', fd);
	ft_putfloat_fd(env->lums[i].pos_lum.y, fd);
	ft_putchar_fd(':', fd);
	ft_putfloat_fd(env->lums[i].pos_lum.z, fd);
	ft_putchar_fd(':', fd);
	if (env->lums[i].col.c.r < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->lums[i].col.c.r, 16, fd);
	if (env->lums[i].col.c.g < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->lums[i].col.c.g, 16, fd);
	if (env->lums[i].col.c.b < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->lums[i].col.c.b, 16, fd);
	ft_putchar_fd('\n', fd);
}

static void	print_d_obj(t_env *env, int i, int fd)
{
	if (env->objs[i].type == 's')
		ft_putstr_fd("sphere:", fd);
	else if (env->objs[i].type == 'p')
		ft_putstr_fd("plane:", fd);
	else if (env->objs[i].type == 'c')
		ft_putstr_fd("cone:", fd);
	else if (env->objs[i].type == 't')
		ft_putstr_fd("tube:", fd);
	ft_putfloat_fd(env->objs[i].o.x, fd);
	ft_putchar_fd(':', fd);
	ft_putfloat_fd(env->objs[i].o.y, fd);
	ft_putchar_fd(':', fd);
	ft_putfloat_fd(env->objs[i].o.z, fd);
	ft_putchar_fd(':', fd);
	ft_putfloat_fd(env->objs[i].norm.x, fd);
	ft_putchar_fd(':', fd);
	ft_putfloat_fd(env->objs[i].norm.y, fd);
	ft_putchar_fd(':', fd);
	ft_putfloat_fd(env->objs[i].norm.z, fd);
	ft_putchar_fd(':', fd);
}

static void	print_obj(t_env *env, int i, int fd)
{
	int j;

	j = 3;
	print_d_obj(env, i, fd);
	while (j-- > 0)
		ft_putstr_fd("0:", fd);
	ft_putfloat_fd(env->objs[i].radius, fd);
	ft_putchar_fd(':', fd);
	j = 3;
	ft_putstr_fd("1:", fd);
	while (j-- > 0)
		ft_putstr_fd("0:", fd);
	if (env->objs[i].col.c.r < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->objs[i].col.c.r, 16, fd);
	if (env->objs[i].col.c.g < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->objs[i].col.c.g, 16, fd);
	if (env->objs[i].col.c.b < 16)
		ft_putchar_fd('0', fd);
	ft_putnbrbase_fd(env->objs[i].col.c.b, 16, fd);
	ft_putchar_fd('\n', fd);
}

void		scene_generator(t_env *env)
{
	int	i;
	int fd;

	if (!(fd = open("testscene", O_CREAT | O_WRONLY | O_APPEND, 0666)))
		ft_put_err("lol");//
	i = env->nb_cam;
	while (--i >= 0)
	{
		env->cams[i].vcam = vect_norm(env->cams[i].vcam);
		env->cams[i].v2cam = vect_norm(env->cams[i].v2cam);
		env->cams[i].v3cam = vect_norm(env->cams[i].v3cam);
		print_cam(env, i, fd);
	}
	i = env->nb_lum;
	while (--i >= 0)
		print_lum(env, i, fd);
	i = 0;
	while (i < env->nb_obj)
	{
		env->objs[i].norm = vect_norm(env->objs[i].norm);
		print_obj(env, i, fd);
		i++;
	}
}

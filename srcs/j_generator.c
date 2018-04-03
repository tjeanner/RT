/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_generator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 01:37:44 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/02 00:13:05 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	j_print_cam(t_env *env, int i, int fd)
{
	ft_putstr_fd("{\"pos\":{\"x\":", fd);
	ft_putfloat_fd(env->cams[i].pos_cam.x, fd);
	ft_putstr_fd(",\"y\":", fd);
	ft_putfloat_fd(env->cams[i].pos_cam.y, fd);
	ft_putstr_fd(",\"z\":", fd);
	ft_putfloat_fd(env->cams[i].pos_cam.z, fd);
	ft_putstr_fd("},\"v\":{\"x\":", fd);
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

static void	j_print_lum(t_env *env, int i, int fd)
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
	ft_putfloat_fd(env->lums[i].pos_lum.x, fd);
	ft_putstr_fd(",\"y\":", fd);
	ft_putfloat_fd(env->lums[i].pos_lum.y, fd);
	ft_putstr_fd(",\"z\":", fd);
	ft_putfloat_fd(env->lums[i].pos_lum.z, fd);
	ft_putstr_fd("}}", fd);
}

static void	j_print_d_obj(t_env *env, int i, int fd)
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

static void	j_print_obj(t_env *env, int i, int fd)
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

//void		j_print_scene()
void		j_scene_generator(t_env *env)
{
	int	i;
	int fd;

	if (!(fd = open("testscene.json", O_CREAT | O_WRONLY | O_APPEND, 0666)))
		ft_put_err("lol");//
	ft_putstr_fd("{\"name\":\"", fd);
	ft_putstr_fd(env->name, fd);
	ft_putstr_fd("\",\"filter\":\"", fd);
	ft_putstr_fd(env->filter, fd);
	ft_putstr_fd("\",\"scene\":{", fd);
	i = env->nb_cam;
	ft_putstr_fd("\"cameras\":[", fd);	
	while (--i >= 0)
	{
		env->cams[i].vcam = vect_norm(env->cams[i].vcam);
		env->cams[i].v2cam = vect_norm(env->cams[i].v2cam);
		env->cams[i].v3cam = vect_norm(env->cams[i].v3cam);
		j_print_cam(env, i, fd);
		if (i != 0)
			ft_putstr_fd(",", fd);
	}
	ft_putstr_fd("],", fd);
	i = env->nb_lum;
	ft_putstr_fd("\"lights\":[", fd);	
	while (--i >= 0)
	{
		j_print_lum(env, i, fd);
		if (i != 0)
			ft_putstr_fd(",", fd);
	}
	ft_putstr_fd("],", fd);
	i = 0;
	ft_putstr_fd("\"objects\":[", fd);
	while (i < env->nb_obj)
	{
		env->objs[i].norm = vect_norm(env->objs[i].norm);
		j_print_obj(env, i, fd);
		if (i != env->nb_obj - 1)
			ft_putstr_fd(",", fd);
		i++;
	}
	ft_putstr_fd("]}}", fd);
}

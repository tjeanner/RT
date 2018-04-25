/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useless_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 00:39:43 by tjeanner          #+#    #+#             */
/*   Updated: 2018/04/25 14:55:43 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_freeenv(t_env *env)
{
	SDL_FreeSurface(env->surf2);
	SDL_DestroyWindow(env->win);
	free(env->file);
	free(env->name);
	free(env->filter);
	free(env->threads);
	ft_memdel((void *)&env->objs.obj);
	ft_memdel((void *)&env->lums.lum);
	ft_memdel((void *)&env->cams.cam);
	free(env);
}

/*
void	sobel_filter(t_env *env)
{
	int	y;
	int x;
	int gx, gy, gn;
	unsigned int *data;
	unsigned int *tmp = NULL;

	tmp = malloc(sizeof(unsigned int) * WIN_X * WIN_Y);
	data = (unsigned int *)env->surf->pixels;
	ft_bzero(tmp, sizeof(tmp));
	y = 1;
	while (y < WIN_Y - 1)
	{
		x = 1;
		while (x < WIN_X - 1)
		{
			gx = ((data[(y - 1) * WIN_X + x + 1] - data[(y - 1) * WIN_X + x - 1]) + 3 
					* (data[(y) * WIN_X + x + 1] - data[(y) * WIN_X + x - 1])
					+ (data[(y + 1) * WIN_X + x + 1] - data[(y + 1) * WIN_X + x - 1]))
				* 3;
			gy = ((data[(y + 1) * WIN_X + x - 1] - data[(y - 1) * WIN_X + x - 1]) + 3 
					* (data[(y + 1) * WIN_X + x] - data[(y - 1) * WIN_X + x])
					+ (data[(y + 1) * WIN_X + x + 1] - data[(y - 1) * WIN_X + x + 1]))
				* 3;
			gn = (unsigned int)sqrt(gx * gx + gy * gy);
			tmp[(y * WIN_X) + x] = gn;
			x++;
		}
		y++;
	}
	y = 1;
	while (y < WIN_Y)
	{
		x = 1;
		while (x < WIN_X)
		{
			if (tmp[(y * WIN_X) + x] > 1)
				data[(y * WIN_X) + x] =  get_black().color;
			x++;
		}
		y++;
	}
}*/

void	ft_putfloat_fd(double nbr, int fd)
{
	int		tmp;
	int		i;
	double	nb;

	nb = nbr;
	tmp = nb;
	if (nbr < 0.0000000000000)
	{
		nb *= -1.0;
		tmp *= -1.0;
		ft_putchar_fd('-', fd);
	}
	ft_putnbr_fd(tmp,fd);
	ft_putchar_fd('.', fd);
//	while ((nb = (double)(nb - tmp) * 1000000.0) > 0)
//	{
//		tmp = nb;
//		ft_putnbr_fd(tmp, fd);
//	}
	i = -1;
	while (++i < 10)
	{
		nb -= (double)tmp;
		nb *= 10.000000000;
		tmp = nb;
		ft_putnbr_fd(tmp, fd);
	}
}

double	which_pow(double num, double pow)
{
	double	m;
	int		n;

	if (num == pow)
		return (1);
	else if ((num == 0 || pow == 0) && (n = 0) == 0)
		return (0);
	else if (num > pow && (m = pow) == pow)
	{
		while (m < num && ++n)
			m *= pow;
		return (n = (m == num) ? n + 1 : 0);
	}
	else if (num < pow && (m = num) == num)
	{
		while (m < pow && ++n)
			m *= pow;
		return (n = (m == pow) ? -n + 1 : 0);
	}
	return (0);
}

/*
t_env	*fill_env(t_env *env)
{
	t_obj	obj;

	env->cams.cam[0].pos_cam.x = 0;
	env->cams.cam[0].pos_cam.y = 0;
	env->cams.cam[0].pos_cam.z = -8000;
	env->lums.lum[0].pos_lum.x = 0;
	env->lums.lum[0].pos_lum.y = 400;
	env->lums.lum[0].pos_lum.z = -800;
	env->lums.lum[0].coef = 1.0;
	set_white(&env->lums.lum[0].col);
	env->cams.cam[0].vcam.x = 0;
	env->cams.cam[0].vcam.y = 0;
	env->cams.cam[0].vcam.z = 1;
	env->cams.cam[0].v2cam.x = 0;
	env->cams.cam[0].v2cam.y = 1;
	env->cams.cam[0].v2cam.z = 0;
	obj.type = 'p';
	obj.o.x = 0;
	obj.o.y = 0;
	obj.o.z = 1000 + DIST;
	obj.norm.x = 0;
	obj.norm.y = 0;
	obj.norm.z = -1;
	obj.col.c.r = 0;
	obj.col.c.g = 0;
	obj.col.c.b = 255;
	obj.col.c.a = 0;
	//ft_memcpy(&env->objs.obj[0], &obj, sizeof(t_obj));
	obj.type = 'p';
	obj.o.x = 1000;
	obj.o.y = 0;
	obj.o.z = 0;
	obj.norm.x = -1;
	obj.norm.y = 0;
	obj.norm.z = 0;
	obj.col.c.r = 255;
	obj.col.c.g = 0;
	obj.col.c.b = 0;
	obj.col.c.a = 0;
	//ft_memcpy(&env->objs.obj[1], &obj, sizeof(t_obj));
	obj.type = 'p';
	obj.o.x = -1000;
	obj.o.y = 0;
	obj.o.z = 0;
	obj.norm.x = 1;
	obj.norm.y = 0;
	obj.norm.z = 0;
	obj.col.c.r = 255;
	obj.col.c.g = 0;
	obj.col.c.b = 0;
	obj.col.c.a = 0;
	//ft_memcpy(&env->objs.obj[2], &obj, sizeof(t_obj));
	obj.type = 'p';
	obj.o.x = 0;
	obj.o.y = 1000;
	obj.o.z = 0;
	obj.norm.x = 0;
	obj.norm.y = -1;
	obj.norm.z = 0;
	obj.col.c.r = 0;
	obj.col.c.g = 255;
	obj.col.c.b = 0;
	obj.col.c.a = 0;
	//ft_memcpy(&env->objs.obj[3], &obj, sizeof(t_obj));
	obj.type = 'p';
	obj.o.x = 0;
	obj.o.y = -1000;
	obj.o.z = 0;
	obj.norm.x = 0;
	obj.norm.y = 1;
	obj.norm.z = 0;
	obj.col.c.r = 0;
	obj.col.c.g = 255;
	obj.col.c.b = 0;
	obj.col.c.a = 0;
	//ft_memcpy(&env->objs.obj[4], &obj, sizeof(t_obj));
	obj.type = 't';
	obj.radius = 100;
	obj.o.x = 11;
	obj.o.y = 10;
	obj.o.z = 10;
	obj.norm.x = 1;
	obj.norm.y = 0;
	obj.norm.z = 1;
	obj.col.c.r = 0;
	obj.col.c.g = 255;
	obj.col.c.b = 255;
	obj.col.c.a = 0;
	//ft_memcpy(&env->objs.obj[5], &obj, sizeof(t_obj));
	obj.type = 's';
	obj.o.x = 0;
	obj.o.y = 0;
	obj.o.z = 0;
	obj.radius = 500;
	obj.col.c.r = 255;
	obj.col.c.g = 255;
	obj.col.c.b = 255;
	obj.col.c.a = 0;
	//ft_memcpy(&env->objs.obj[6], &obj, sizeof(t_obj));
	obj.type = 'c';
	obj.radius = 5;
	obj.o.x = -11;
	obj.o.y = 10;
	obj.o.z = -10;
	obj.norm.x = 1;
	obj.norm.y = 0;
	obj.norm.z = 1;
	obj.col.c.r = 255;
	obj.col.c.g = 0;
	obj.col.c.b = 255;
	obj.col.c.a = 0;
	//ft_memcpy(&env->objs.obj[7], &obj, sizeof(t_obj));
//	if (!(env->init_rays = (t_ray *)malloc(sizeof(t_ray) * 1)))
//		return (0);
//	env->objs.nb = 8;
	return (env);
}
*/

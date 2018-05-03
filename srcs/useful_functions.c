/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 00:39:43 by tjeanner          #+#    #+#             */
/*   Updated: 2018/05/03 03:33:52 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_freeenv(t_env *env)
{
	SDL_FreeSurface(env->display.surf2);
	SDL_DestroyWindow(env->display.win);
	free(env->file);
	free(env->name);
	free(env->effects.filter);
	free(env->threads);
	ft_memdel((void *)&env->objs.obj);
	ft_memdel((void *)&env->lums.lum);
	ft_memdel((void *)&env->cams.cam);
	free(env);
}

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
	ft_putnbr_fd(tmp, fd);
	ft_putchar_fd('.', fd);
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

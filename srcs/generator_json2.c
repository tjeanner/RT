/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_json2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 18:04:19 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/22 20:05:50 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		j_print_env(t_env *env, int i)
{
	int		fd;

	while ((fd = open(ft_strjoin("./scenes/scene", ft_strjoin(ft_itoa(i),
		".json")), O_CREAT | O_EXCL | O_RDONLY, 0666)) == -1 && i < 20)
		i++;
	fd = open(ft_strjoin("./scenes/scene", ft_strjoin(ft_itoa(i), ".json")),
		O_CREAT | O_WRONLY | O_APPEND, 0666);
	ft_putstr_fd("{\"name\":\"", fd);
	ft_putstr_fd(env->name, fd);
	ft_putstr_fd("\",\"filter\":\"", fd);
	ft_putstr_fd(env->filter, fd);
	ft_putstr_fd("\",\"ambient\":", fd);
	ft_putfloat_fd(env->amb_coef, fd);
	ft_putstr_fd(",\"scene\":{", fd);
	ft_putstr_fd("\"cameras\":[", fd);
	i = env->nb_cam;
	while (--i >= 0)
	{
		env->cams[i].vcam = vect_norm(env->cams[i].vcam);
		env->cams[i].v2cam = vect_norm(env->cams[i].v2cam);
		env->cams[i].v3cam = vect_norm(env->cams[i].v3cam);
		j_print_cam(env, i, fd);
		if (i != 0)
			ft_putstr_fd(",", fd);
	}
	return (fd);
}

void	j_scene_generator(t_env *env)
{
	int	i;
	int fd;

	fd = j_print_env(env, 0);
	i = env->nb_lum;
	ft_putstr_fd("],", fd);
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

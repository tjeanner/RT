/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_json2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 18:04:19 by hbouchet          #+#    #+#             */
/*   Updated: 2018/05/03 21:48:48 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void j_print_scn(t_env *env, int fd)
{
	ft_putstr_fd("{\n\t\"name\":\"", fd);
	ft_putstr_fd(env->name, fd);
	ft_putstr_fd("\",\n\t\"filter\":\"", fd);
	ft_putstr_fd(env->effects.filter, fd);
	ft_putstr_fd("\",\n\t\"depth\":", fd);
	ft_putfloat_fd(env->effects.depth, fd);
	ft_putstr_fd(",\n\t\"ambient\":", fd);
	ft_putfloat_fd(env->lums.amb_coef, fd);
	ft_putstr_fd(",\n\t\"scene\":{\n\t\t\"cameras\":[", fd);
}

int		j_print_env(t_env *env, int i)
{
	int		fd;
	char	*tmp;
	char	*tmp2;

	tmp2 = ft_strjoinfree(ft_itoa(i), ".json", 'L');
	tmp = ft_strjoinfree("./scenes/scene_", tmp2, 'R');
	while ((fd = open(tmp, O_CREAT | O_EXCL | O_RDONLY, 0666)) == -1 && i < 20)
	{
		i++;
		free(tmp);
		tmp2 = ft_strjoinfree(ft_itoa(i), ".json", 'L');
		tmp = ft_strjoinfree("./scenes/scene_", tmp2, 'R');
	}
	if ((fd = open(tmp, O_CREAT | O_WRONLY | O_APPEND, 0666)) <= 0)
		error_mgt(11);
	free(tmp);
	j_print_scn(env, fd);
	i = env->cams.nb;
	while (--i >= 0)
	{
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
	i = env->lums.nb;
	ft_putstr_fd("],\n\t\t", fd);
	ft_putstr_fd("\"lights\":[", fd);
	while (--i >= 0)
	{
		j_print_lum(env, i, fd);
		if (i != 0)
			ft_putstr_fd(",", fd);
	}
	ft_putstr_fd("],\n", fd);
	i = 0;
	ft_putstr_fd("\n\t\t\"objects\":[", fd);
	while (i < env->objs.nb)
	{
		env->objs.obj[i].norm = vect_norm(env->objs.obj[i].norm);
		j_print_obj(env, i, fd);
		if (i != env->objs.nb - 1)
			ft_putstr_fd(",", fd);
		i++;
	}
	ft_putstr_fd("]}}", fd);
}

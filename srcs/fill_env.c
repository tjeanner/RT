/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 05:36:57 by hbouchet          #+#    #+#             */
/*   Updated: 2018/01/27 05:37:00 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char	init_struct(char *line, t_env *env)
{
	char flag;

	flag = 'e';
	if (ft_strstr(line, "#OBJ#"))
	{
		flag = 'o';
		env->nb_obj = ft_atoi(line + 6);
		if (!(env->objs = (t_obj *)malloc(sizeof(t_obj) * env->nb_obj)))
			exit(0);
	}
	else if (ft_strstr(line, "#CAM#"))
	{
		flag = 'c';
		env->nb_cam = ft_atoi(line + 6);
		if (!(env->cams = (t_cam *)malloc(sizeof(t_cam) * env->nb_cam)))
			exit(0);
	}
	else if (ft_strstr(line, "#LUM#"))
	{
		flag = 'l';
		env->nb_lum = ft_atoi(line + 6);
		if (!(env->lums = (t_lum *)malloc(sizeof(t_lum) * env->nb_lum)))
			exit(0);
	}
	return (flag);
}

int		fill_env(char flag, char **tmp, t_env *env, int i)
{
	if (flag == 'o' && (ft_strstr(tmp[0], "tube") || ft_strstr(tmp[0], "plane")
		|| ft_strstr(tmp[0], "sphere") || ft_strstr(tmp[0], "cone")))
	{
		env->objs[i] = get_obj(tmp);
		i++;
	}
	else if (flag == 'c' && ft_strstr(tmp[0], "cam"))
	{
		env->cams[i] = get_cam(tmp);
		i++;
	}
	else if (flag == 'l' && ft_strstr(tmp[0], "lum"))
	{
		env->lums[i] = get_lum(tmp);
		i++;
	}
	return (i);
}

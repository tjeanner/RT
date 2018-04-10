/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 02:03:21 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/10 03:54:46 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			putlineerr(char *str, int i)
{
	char	tmp[250];

	ft_putendl(ft_strcat(ft_strcpy(tmp, str), ft_itoa(i)));
	return (0);
}

void		malloc_env(t_env *env)
{
	if (!(env->objs = (t_obj *)malloc(sizeof(t_obj) * env->nb_obj)))
		exit(0);
	if (!(env->cams = (t_cam *)malloc(sizeof(t_cam) * env->nb_cam)))
		exit(0);
	if (!(env->lums = (t_lum *)malloc(sizeof(t_lum) * env->nb_lum)))
		exit(0);
}

void		set_struct(t_env *env, t_par *par)
{
	int		i;

	i = -1;
	while (++i < env->nb_obj)
	{
		ft_memcpy((void *)&env->objs[i], par->lst_obj->content, sizeof(t_obj));
		free(par->lst_obj->content);
		par->lst_obj = par->lst_obj->next;
	}
	i = -1;
	while (++i < env->nb_cam)
	{
		ft_memcpy((void *)&env->cams[i], par->lst_cam->content, sizeof(t_cam));
		free(par->lst_cam->content);
		par->lst_cam = par->lst_cam->next;
	}
	i = -1;
	while (++i < env->nb_lum)
	{
		ft_memcpy((void *)&env->lums[i], par->lst_lum->content, sizeof(t_lum));
		free(par->lst_lum->content);
		par->lst_lum = par->lst_lum->next;
	}
}

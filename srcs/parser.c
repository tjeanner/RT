/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 02:03:21 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/25 11:26:50 by tjeanner         ###   ########.fr       */
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
	if (!(env->objs.obj = (t_obj *)malloc(sizeof(t_obj) * env->objs.nb)))
		exit(0);
	if (!(env->cams.cam = (t_cam *)malloc(sizeof(t_cam) * env->cams.nb)))
		exit(0);
	if (!(env->lums.lum = (t_lum *)malloc(sizeof(t_lum) * env->lums.nb)))
		exit(0);
}

void		set_struct(t_env *env, t_par *par)
{
	int		i;
	void	*p;

	i = -1;
	while (++i < env->objs.nb)
	{
		ft_memcpy((void *)&env->objs.obj[i], par->lst_obj->content, sizeof(t_obj));
		free(par->lst_obj->content);
		p = par->lst_obj;
		par->lst_obj = par->lst_obj->next;
		free(p);
	}
	i = -1;
	while (++i < env->cams.nb)
	{
		ft_memcpy((void *)&env->cams.cam[i], par->lst_cam->content, sizeof(t_cam));
		free(par->lst_cam->content);
		p = par->lst_cam;
		par->lst_cam = par->lst_cam->next;
		free(p);
	}
	i = -1;
	while (++i < env->lums.nb)
	{
		ft_memcpy((void *)&env->lums.lum[i], par->lst_lum->content, sizeof(t_lum));
		p = par->lst_lum;
		free(par->lst_lum->content);
		par->lst_lum = par->lst_lum->next;
		free(p);
	}
}

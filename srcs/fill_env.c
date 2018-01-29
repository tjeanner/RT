/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 05:36:57 by hbouchet          #+#    #+#             */
/*   Updated: 2018/01/29 01:38:03 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		is_valid_cam(char **str)
{
	if (ft_strstr(str[0], "cam"))
		return (1);
	else
		return (0);
}

int		is_valid_lum(char **str)
{
	if (ft_strstr(str[0], "lum"))
		return (1);
	else
		return (0);
}

int		is_valid_obj(char **str)
{
	if ((ft_strstr(str[0], "tube") || ft_strstr(str[0], "plane")
				|| ft_strstr(str[0], "sphere") || ft_strstr(str[0], "cone")))
		return (1);
	else
		return (0);
}

void	set_list(t_env *env, char *line, t_par *par)
{
	char	**tmp;
	t_obj	obj;
	t_cam	cam;
	t_lum	lum;

	tmp = ft_strsplit(line, '\t');
	if (is_valid_obj(tmp))
	{
		get_obj(tmp, &obj);
		ft_lstadd(&par->lst_obj, ft_lstnew(&obj, sizeof(t_obj)));
		env->nb_obj++;
	}
	else if (is_valid_cam(tmp))
	{
		get_cam(tmp, &cam);
		ft_lstadd(&par->lst_cam, ft_lstnew(&cam, sizeof(t_cam)));
		env->nb_cam++;
	}
	else if (is_valid_lum(tmp))
	{
		get_lum(tmp, &lum);
		ft_lstadd(&par->lst_lum, ft_lstnew(&lum, sizeof(t_lum)));
		env->nb_lum++;
	}
}

void	set_struct(t_env *env, t_par *par)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = par->lst_obj;
	while (i < env->nb_obj)
	{
		ft_memcpy((void *)&env->objs[i], temp->content, sizeof(t_obj));
		temp = temp->next;
		i++;
	}
	i = 0;
	temp = par->lst_cam;
	while (i < env->nb_cam)
	{
		ft_memcpy((void *)&env->cams[i], temp->content, sizeof(t_cam));
		temp = temp->next;
		i++;
	}
	i = 0;
	temp = par->lst_lum;
	while (i < env->nb_lum)
	{
		ft_memcpy((void *)&env->lums[i], temp->content, sizeof(t_lum));
		temp = temp->next;
		i++;
	}
}

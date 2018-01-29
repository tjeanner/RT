/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 05:36:57 by hbouchet          #+#    #+#             */
/*   Updated: 2018/01/29 08:28:01 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			is_valid_cam(char **str, int n_line)
{
	int i;

	i = 0;
	if (ft_strncmp(str[0], "cam", ft_strstr(str[0], "cam") - *str))
		return (0);
	while (str[i])
		i++;
	if (i != 10)
		return (putlineerr("invalid vector number (cam) line ", n_line));
	return (1);
}

int			is_valid_lum(char **str, int n_line)
{
	(void)n_line;
	int i = 0;

	if (ft_strncmp(str[0], "lum", ft_strstr(str[0], "lum") - *str))
		return (0);
	while (str[i])
		i++;
	if (i != 4)
		return (putlineerr("invalid vector number (lum) line ", n_line));
	return (1);
}

int			is_valid_obj(char **str, int n_line)
{
	int		i;

	i = 0;
	if ((ft_strncmp(str[0], "tube", ft_strstr(str[0], "tube") - *str)
		 && ft_strncmp(str[0], "plane", ft_strstr(str[0], "plane") - *str)
		 && ft_strncmp(str[0], "cone", ft_strstr(str[0], "cone") - *str)
		 && ft_strncmp(str[0], "sphere", ft_strstr(str[0], "sphere") - *str)))
		return (0);
	while (str[i])
		i++;
	if (i != 12)
		return (putlineerr("invalid vector number (obj) line ", n_line));
	if (!ft_strstr(str[0], "sphere") && ft_atoi(str[4]) == 0
		&& ft_atoi(str[5]) == 0 && ft_atoi(str[6]) == 0)
		return (putlineerr("null vector line ", n_line));
	i = 0;
	while (str[11][i])
		i++;
	if (i < 6)
		return (putlineerr("invalid color line ", n_line));
	return (1);
}

void		set_list(t_env *env, char *line, t_par *par, int i)
{
	char	**tmp;
	t_obj	obj;
	t_cam	cam;
	t_lum	lum;

	tmp = ft_strsplit(line, ':');
	if (is_valid_obj(tmp, i))
	{
		get_obj(tmp, &obj);
		ft_lstadd(&par->lst_obj, ft_lstnew(&obj, sizeof(t_obj)));
		env->nb_obj++;
	}
	else if (is_valid_cam(tmp, i))
	{
		get_cam(tmp, &cam);
		ft_lstadd(&par->lst_cam, ft_lstnew(&cam, sizeof(t_cam)));
		env->nb_cam++;
	}
	else if (is_valid_lum(tmp, i))
	{
		get_lum(tmp, &lum);
		ft_lstadd(&par->lst_lum, ft_lstnew(&lum, sizeof(t_lum)));
		env->nb_lum++;
	}
}

void		set_struct(t_env *env, t_par *par)
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

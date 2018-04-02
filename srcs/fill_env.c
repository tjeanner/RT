/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 05:36:57 by hbouchet          #+#    #+#             */
/*   Updated: 2018/02/18 01:42:59 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			is_valid_cam(char **str, int n_line)
{
	int i;

	i = 0;
	if (!str[0])
		return (0);
	if (ft_strcmp(ft_strtrim(str[0]), "cam"))
		return (0);
	while (str[i])
		i++;
	if (i != 10)
		return (putlineerr("invalid cam line ", n_line));
	if (!is_norm_wchar(ft_atof(str[4]), ft_atof(str[5]), ft_atof(str[6]))
		|| !is_norm_wchar(ft_atof(str[7]), ft_atof(str[8]), ft_atof(str[9])))
		return (putlineerr("invalid vector (cam) line ", n_line));
	return (1);
}

int			is_valid_lum(char **str, int n_line)
{
	int		i;
	char	*trim;

	i = 0;
	if (!str[0])
		return (0);
	if (ft_strcmp(ft_strtrim(str[0]), "lum"))
		return (0);
	while (str[i])
		i++;
	if (i != 5)
		return (putlineerr("invalid lum line ", n_line));
	i = 0;
	trim = ft_strtrim(str[4]);
	while (trim[i])
	{
		if (!((trim[i] >= '0' && trim[i] <= '9') ||
		(ft_toupper(trim[i]) >= 'A' && ft_toupper(trim[i]) <= 'F')))
			return (putlineerr("invalid color line ", n_line));
		i++;
	}
	if (i < 6)
		return (putlineerr("invalid color line ", n_line));
	return (1);
}

int			is_valid_obj(char **str, int n_line)
{
	int		i;
	char	*trim;

	i = 0;
	if (!str[0] || ((ft_strcmp(ft_strtrim(str[0]), "tube"))
		&& (ft_strcmp(ft_strtrim(str[0]), "sphere"))
		&& (ft_strcmp(ft_strtrim(str[0]), "plane"))
		&& (ft_strcmp(ft_strtrim(str[0]), "cone"))))
		return (0);
	while (str[i])
		i++;
	if (i != 16)
		return (putlineerr("invalid obj line ", n_line));
	if (!ft_strstr(str[0], "sphere") && !is_norm_wchar(ft_atof(str[4]),
		ft_atof(str[5]), ft_atof(str[6])))
		return (putlineerr("invalid vector (obj) line ", n_line));
	if (!ft_strstr(str[0], "plane") && ft_atof(str[10]) < 0)
		return (putlineerr("invalid radius line ", n_line));
	i = 0;
	trim = ft_strtrim(str[15]);
	while (trim[i] && ((trim[i] >= '0' && trim[i] <= '9') ||
		(ft_toupper(trim[i]) >= 'A' && ft_toupper(trim[i]) <= 'F')))
		i++;
	return (i == 6) ? (1) : (putlineerr("invalid color line ", n_line));
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

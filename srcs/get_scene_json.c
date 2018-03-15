/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene_json.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 16:03:38 by hbouchet          #+#    #+#             */
/*   Updated: 2018/03/15 14:45:46 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	j_set_obj(char *key, int type, t_json *j_obj, t_obj *obj)
{
	if (!ft_strcmp(key, "type") && type == TYPE_STRING)
		j_get_type(j_obj, obj);
	else if (!ft_strcmp(key, "radius") && type == TYPE_DOUBLE)
		j_get_radius(j_obj, obj);
	else if (!ft_strcmp(key, "color") && type == TYPE_STRING)
		obj->col = j_get_color(j_obj);
	else if (!ft_strcmp(key, "norm") && type == TYPE_OBJ)
		obj->norm = j_get_vec(j_obj);
	else if (!ft_strcmp(key, "pos") && type == TYPE_OBJ)
		obj->o = j_get_vec(j_obj);
	else
		ft_put_err("invalid json");
}

void		j_get_obj(t_json_arr *tab, t_obj *obj, t_par *par, t_env *env)
{
	while (tab)
	{
		ft_bzero(obj, sizeof(t_obj));
		while (tab->val.data.obj)
		{
			j_set_obj(tab->val.data.obj->key, tab->val.data.obj->val.type,
					tab->val.data.obj, obj);
			tab->val.data.obj = tab->val.data.obj->next;
		}
		if (j_is_valid_obj(obj))
		{
			ft_lstadd(&par->lst_obj, ft_lstnew(obj, sizeof(t_obj)));
			env->nb_obj++;
		}
		tab = tab->next;
	}
}

void		j_get_lights(t_json_arr *tab, t_lum *lum, t_par *par, t_env *env)
{
	while (tab)
	{
		ft_bzero(lum, sizeof(t_lum));
		while (tab->val.data.obj)
		{
			if (!ft_strcmp(tab->val.data.obj->key, "color")
				&& tab->val.data.obj->val.type == TYPE_STRING)
				lum->col = j_get_color(tab->val.data.obj);
			else if (!ft_strcmp(tab->val.data.obj->key, "pos")
				&& tab->val.data.obj->val.type == TYPE_OBJ)
				lum->pos_lum = j_get_vec(tab->val.data.obj);
			else
				ft_put_err("invalid light");
			tab->val.data.obj = tab->val.data.obj->next;
		}
		if (j_is_valid_lum(lum))
		{
			ft_lstadd(&par->lst_lum, ft_lstnew(lum, sizeof(t_lum)));
			env->nb_lum++;
		}
		tab = tab->next;
	}
}

void		j_get_cam(t_json_arr *tab, t_cam *cam, t_par *par, t_env *env)
{
	while (tab)
	{
		ft_bzero(cam, sizeof(t_cam));
		while (tab->val.data.obj)
		{
			if (!ft_strcmp(tab->val.data.obj->key, "pos")
				&& tab->val.data.obj->val.type == TYPE_OBJ)
				cam->pos_cam = j_get_vec(tab->val.data.obj);
			else if (!ft_strcmp(tab->val.data.obj->key, "v")
				&& tab->val.data.obj->val.type == TYPE_OBJ)
				cam->vcam = j_get_vec(tab->val.data.obj);
			else if (!ft_strcmp(tab->val.data.obj->key, "v2")
				&& tab->val.data.obj->val.type == TYPE_OBJ)
				cam->v2cam = j_get_vec(tab->val.data.obj);
			else
				ft_put_err("invalid camera");
			tab->val.data.obj = tab->val.data.obj->next;
		}
		if (j_is_valid_cam(cam))
		{
			ft_lstadd(&par->lst_cam, ft_lstnew(cam, sizeof(t_cam)));
			env->nb_cam++;
		}
		tab = tab->next;
	}
}

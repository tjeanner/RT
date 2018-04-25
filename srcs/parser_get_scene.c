/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 16:03:38 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/25 11:28:06 by tjeanner         ###   ########.fr       */
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
	else if (!ft_strcmp(key, "translation") && type == TYPE_OBJ)
		obj->o = vect_add(obj->o, j_get_vec(j_obj));
	else if (!ft_strcmp(key, "rotation") && type == TYPE_OBJ)
		j_get_rot(j_obj, obj);
	else
		error_mgt(5);
}

void		j_get_obj(t_json_arr *tab, t_obj *obj, t_par *par, t_env *env)
{
	t_json_arr	*p;
	t_json		*po;

	p = tab;
	while (p)
	{
		po = p->val.data.obj;
		ft_bzero(obj, sizeof(t_obj));
		while (po)
		{
			j_set_obj(po->key, po->val.type, po, obj);
			po = po->next;
		}
		if (j_is_valid_obj(obj))
		{
			ft_lstadd(&par->lst_obj, ft_lstnew(obj, sizeof(t_obj)));
			env->objs.nb++;
		}
		p = p->next;
	}
}

void		j_get_lights(t_json_arr *tab, t_lum *lum, t_par *par, t_env *env)
{
	t_json_arr	*p;
	t_json		*po;

	p = tab;
	while (p)
	{
		po = p->val.data.obj;
		ft_bzero(lum, sizeof(t_lum));
		lum->coef = 0.4;
		while (po)
		{
			if (!ft_strcmp(po->key, "color") && po->val.type == TYPE_STRING)
				lum->col = j_get_color(po);
			else if (!ft_strcmp(po->key, "pos") && po->val.type == TYPE_OBJ)
				lum->pos = j_get_vec(po);
			else if (!ft_strcmp(po->key, "intensity") && po->val.type == TYPE_DOUBLE)
			{
				if (po->val.data.nb >= 0 && po->val.data.nb <= 1)
					lum->coef = po->val.data.nb;
				else
					lum->coef = (po->val.data.nb < 0) ? 0 : 1;
			}
			else
				error_mgt(2);
			po = po->next;
		}
		if (j_is_valid_lum(lum))
		{
			ft_lstadd(&par->lst_lum, ft_lstnew(lum, sizeof(t_lum)));
			env->lums.nb++;
		}
		p = p->next;
	}
}

void		j_get_cam(t_json_arr *tab, t_cam *cam, t_par *par, t_env *env)
{
	t_json_arr	*p;
	t_json		*po;

	p = tab;
	while (p)
	{
		po = p->val.data.obj;
		ft_bzero(cam, sizeof(t_cam));
		while (po)
		{
			if (!ft_strcmp(po->key, "pos") && po->val.type == TYPE_OBJ)
				cam->pos = j_get_vec(po);
			else if (!ft_strcmp(po->key, "v") && po->val.type == TYPE_OBJ)
				cam->vcam = j_get_vec(po);
			else if (!ft_strcmp(po->key, "v2") && po->val.type == TYPE_OBJ)
				cam->v2cam = j_get_vec(po);
			else if (!ft_strcmp(po->key, "color") && po->val.type == TYPE_STRING)
				cam->col = j_get_color(po);
			else
				error_mgt(3);
			po = po->next;
		}
		if (j_is_valid_cam(cam) && ++env->cams.nb)
			ft_lstadd(&par->lst_cam, ft_lstnew(cam, sizeof(t_cam)));
		p = p->next;
	}
}

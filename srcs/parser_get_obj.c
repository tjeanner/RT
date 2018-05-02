/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 16:03:38 by hbouchet          #+#    #+#             */
/*   Updated: 2018/05/02 16:20:16 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	j_set_obj_d(char *key, int type, t_json *j_obj, t_obj *obj)
{
	obj->mat.rough = 1;
	obj->k_diff = 0.7;
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
	else if (!ft_strcmp(key, "reflect") && type == TYPE_DOUBLE)
		obj->reflect = fmin(1, fmax(j_obj->val.data.nb, 0));
	else if (!ft_strcmp(key, "transparency") && type == TYPE_DOUBLE)
		obj->transp = fmin(1, fmax(j_obj->val.data.nb, 0));
	else
		return (0);
	return (1);
}

static void	j_set_obj(char *key, int type, t_json *j_obj, t_obj *obj)
{
	if (j_set_obj_d(key, type, j_obj, obj))
		return ;
	else if (!ft_strcmp(key, "refract") && type == TYPE_DOUBLE)
		obj->refract = fmin(10, fmax(j_obj->val.data.nb, 0));
	else if (!ft_strcmp(key, "roughness") && type == TYPE_DOUBLE)
		obj->mat.rough = fmin(20, fmax(j_obj->val.data.nb, 1));
	else if (!ft_strcmp(key, "plasticity") && type == TYPE_DOUBLE)
		obj->mat.plastic = fmin(1, fmax(j_obj->val.data.nb, 0));
	else if (!ft_strcmp(key, "specular") && type == TYPE_DOUBLE)
		obj->k_spec = fmin(1, fmax(j_obj->val.data.nb, 0));
	else if (!ft_strcmp(key, "diffuse") && type == TYPE_DOUBLE)
		obj->k_spec = fmin(1, fmax(j_obj->val.data.nb, 0));
	else if (!ft_strcmp(key, "texture") && type == TYPE_STRING)
		j_get_tex(j_obj, obj);
	else if (!ft_strcmp(key, "motion") && type == TYPE_OBJ)
		j_get_motion(j_obj, obj);
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
			if (obj->reflect > 0)
				env->effects.depth = (env->effects.depth == 1) ?
					2 : env->effects.depth;
			ft_lstadd(&par->lst_obj, ft_lstnew(obj, sizeof(t_obj)));
			env->objs.nb++;
		}
		p = p->next;
	}
}

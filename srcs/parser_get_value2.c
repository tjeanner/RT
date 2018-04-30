/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_value2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 16:19:38 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/28 05:36:12 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		j_get_tex(t_json *json, t_obj *obj)
{
	t_json	*p;

	p = json;
	if (!ft_strcmp(p->val.data.str, "STRIPES"))
		obj->tex = 1;
	else
		obj->tex = 0;
	p = p->next;
}

void		j_get_rot(t_json *json, t_obj *obj)
{
	t_json	*p;
	double	th;

	p = json->val.data.obj;
	if (!ft_strcmp(p->key, "th") && p->val.type == TYPE_DOUBLE)
		th = p->val.data.nb;
	else
		return ;
	p = p->next;
	if (!ft_strcmp(p->key, "axe") && p->val.type == TYPE_OBJ)
		obj->norm = rotation(obj->norm, vect_norm(j_get_vec(p)), th);
}

void		j_get_radius(t_json *json, t_obj *obj)
{
	t_json	*p;

	p = json;
	obj->radius = json->val.data.nb;
	p = p->next;
}

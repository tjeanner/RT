/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value_json.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 16:04:33 by hbouchet          #+#    #+#             */
/*   Updated: 2018/03/14 11:16:17 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_v		j_get_vec(t_json *json)
{
	int		cpt = 0;
	t_v		nb;

	if (!ft_strcmp(json->val.data.obj->key, "x"))
	{
		nb.x = json->val.data.obj->val.data.nb;
		json->val.data.obj = json->val.data.obj->next;
		cpt++;
	}
	if (!ft_strcmp(json->val.data.obj->key, "y") && cpt == 1)
	{
		nb.y = json->val.data.obj->val.data.nb;
		json->val.data.obj = json->val.data.obj->next;
		cpt++;
	}
	if (!ft_strcmp(json->val.data.obj->key, "z") && cpt == 2)
	{
		cpt++;
		nb.z = json->val.data.obj->val.data.nb;
		json->val.data.obj = json->val.data.obj->next;
	}
	if (cpt == 3)
		json = json->next;
	return (nb);
}

void		j_get_type(t_json *json, t_obj *obj)
{
	if (!ft_strcmp(json->val.data.str, "plane")
		|| !ft_strcmp(json->val.data.str, "sphere")
		|| !ft_strcmp(json->val.data.str, "tube")
		|| !ft_strcmp(json->val.data.str, "cone"))
		obj->type = json->val.data.str[0];
	else if (!ft_strcmp(json->val.data.str, "cylindre"))
		obj->type = 't';
	json = json->next;
}

t_color		j_get_color(t_json *json)
{
	t_color col;
	
	col = get_color(json->val.data.str);
	json = json->next;
	return (col);
}

void		j_get_radius(t_json *json, t_obj *obj)
{
	obj->radius = json->val.data.nb;
	json = json->next;
}
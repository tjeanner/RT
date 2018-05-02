/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_value2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 16:19:38 by hbouchet          #+#    #+#             */
/*   Updated: 2018/05/02 20:57:30 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		j_get_tex(t_json *json, t_obj *obj)
{
	t_json	*p;

	p = json;
	if (!ft_strncmp(p->val.data.str, "CHESS", 5))
	// {
	// 	if (!ft_strncmp(p->val.data.str, "CHESS:", 6) && ft_strlen(p->val.data.str) > 10)
	// 		obj->mat.scale = ft_atoi(p->val.data.str + 6);
	// }
		obj->mat.tex = 1;
	else if (!ft_strcmp(p->val.data.str, "STRIPES"))
		obj->mat.tex = 2;
	else
		obj->mat.tex = 0;
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

static int	j_get_action(char *str)
{
	if (!ft_strcmp(str, "translation"))
		return (TRANSLATION);
	else if (!ft_strcmp(str, "rotation"))
		return (ROTATION);
	// else if (!ft_strcmp(str, "ellipse"))
	// 	return (ELLIPSE);
	else if (!ft_strcmp(str, "color"))
		return (COLOR);
	else
		return (-1);
}

void		j_get_motion(t_json *json, t_obj *obj)
{
	t_json	*p;

	p = json->val.data.obj;
	while (p)
	{
		if (!ft_strcmp(p->key, "action") && p->val.type == TYPE_STRING)
			obj->act.action = j_get_action(p->val.data.str);
		else if (!ft_strcmp(p->key, "axe") && p->val.type == TYPE_OBJ)
			obj->act.axis = vect_norm(j_get_vec(p));
		else if (!ft_strcmp(p->key, "min") && p->val.type == TYPE_OBJ)
			obj->act.min = j_get_vec(p);
		else if (!ft_strcmp(p->key, "max") && p->val.type == TYPE_OBJ)
			obj->act.max = j_get_vec(p);
		else if (!ft_strcmp(p->key, "speed") && p->val.type == TYPE_DOUBLE)
			obj->act.speed = fmin(500, fmax(p->val.data.nb, 1));
		p = p->next;
	}
}

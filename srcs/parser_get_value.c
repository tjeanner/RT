/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 16:04:33 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/18 13:59:00 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_v			j_get_vec(t_json *json)
{
	int		cpt;
	t_v		nb;
	t_json	*p;
	t_json 	*o;

	p = json;
	o = p->val.data.obj;
	cpt = 0;
	nb = (t_v){0, 0, 0};
	if (o && !ft_strcmp(o->key, "x") && o->val.type == TYPE_DOUBLE && ++cpt)
	{
		nb.x = o->val.data.nb;
		o = o->next;
	}
	if (o && !ft_strcmp(o->key, "y") && o->val.type == TYPE_DOUBLE && ++cpt)
	{
		nb.y = o->val.data.nb;
		o = o->next;
	}
	if (o && !ft_strcmp(o->key, "z") && o->val.type == TYPE_DOUBLE && ++cpt)
	{
		nb.z = o->val.data.nb;
		o = o->next;
	}
	if (cpt == 3)
		p = p->next;
	else 
		error_mgt(4);
	return (nb);
}

void		j_get_rot(t_json *json, t_obj *obj)
{
	t_json	*p;
	double	th;

	p = json->val.data.obj;
	(void)obj;
	if (!ft_strcmp(p->key, "th") && p->val.type == TYPE_DOUBLE)
		th = p->val.data.nb;
	else
		return ;
	p = p->next;
	if (!ft_strcmp(p->key, "axe") && p->val.type == TYPE_OBJ)
		obj->norm = rotation(obj->norm, vect_norm(j_get_vec(p)), th);
}

void		j_get_type(t_json *json, t_obj *obj)
{
	t_json	*p;

	p = json;
	if (!ft_strcmp(json->val.data.str, "plane")
		|| !ft_strcmp(json->val.data.str, "sphere")
		|| !ft_strcmp(json->val.data.str, "tube")
		|| !ft_strcmp(json->val.data.str, "cone"))
		obj->type = json->val.data.str[0];
	else if (!ft_strcmp(json->val.data.str, "cylindre"))
		obj->type = 't';
	p = p->next;
}

t_color		get_color(char *hexa)
{
	t_color	col;
	int		tmp;
	int		i;

	i = 0;
	while (hexa[i] && ((hexa[i] >= '0' && hexa[i] <= '9') ||
		(ft_toupper(hexa[i]) >= 'A' && ft_toupper(hexa[i]) <= 'F')))
		i++;
	if (i != 6)
	{
		col.color = 16777216;
		return (col);
	}
	else
		col.color = 0;
	tmp = (int)(ft_strchr(S, ft_toupper(hexa[0])) - S) * 16
		+ (int)(ft_strchr(S, ft_toupper(hexa[1])) - S);
	col.c.r = tmp;
	tmp = (int)(ft_strchr(S, ft_toupper(hexa[2])) - S) * 16
		+ (int)(ft_strchr(S, ft_toupper(hexa[3])) - S);
	col.c.g = tmp;
	tmp = (int)(ft_strchr(S, ft_toupper(hexa[4])) - S) * 16
		+ (int)(ft_strchr(S, ft_toupper(hexa[5])) - S);
	col.c.b = tmp;
	return (col);
}

t_color		j_get_color(t_json *json)
{
	t_color col;
	t_json	*p;

	p = json;
	if (!ft_strcmp(json->val.data.str, "RANDOM"))
		col = get_rand();
	else
		col = get_color(json->val.data.str);
	p = p->next;
	return (col);
}

void		j_get_radius(t_json *json, t_obj *obj)
{
	t_json	*p;

	p = json;
	obj->radius = json->val.data.nb;
	p = p->next;
}

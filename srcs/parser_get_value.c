/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 16:04:33 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/10 03:56:14 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_v			j_get_vec(t_json *json)
{
	int		cpt;
	t_v		nb;

	cpt = 0;
	nb = (t_v){0, 0, 0};
	if (json->val.data.obj && !ft_strcmp(json->val.data.obj->key, "x") && ++cpt)
	{
		nb.x = json->val.data.obj->val.data.nb;
		free(json->val.data.obj->key);
		json->val.data.obj = json->val.data.obj->next;
	}
	if (json->val.data.obj && !ft_strcmp(json->val.data.obj->key, "y") && ++cpt)
	{
		nb.y = json->val.data.obj->val.data.nb;
		free(json->val.data.obj->key);
		json->val.data.obj = json->val.data.obj->next;
	}
	if (json->val.data.obj && !ft_strcmp(json->val.data.obj->key, "z") && ++cpt)
	{
		nb.z = json->val.data.obj->val.data.nb;
		free(json->val.data.obj->key);
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
	free(json->val.data.str);
	json = json->next;
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

	col = get_color(json->val.data.str);
	free(json->val.data.str);
	json = json->next;
	return (col);
}

void		j_get_radius(t_json *json, t_obj *obj)
{
	obj->radius = json->val.data.nb;
	json = json->next;
}

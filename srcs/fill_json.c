/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_json.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 01:49:37 by hbouchet          #+#    #+#             */
/*   Updated: 2018/03/11 21:10:50 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		j_fill_arr(t_json_arr *arr)
{
	j_fill_obj(&arr->val);
	if (arr->next)
		j_fill_arr(arr->next);
}

void		j_fill_obj(t_val *val)
{
	if (val->type == TYPE_OBJ)
		j_fill_env(val->data.obj);
	else if (val->type == TYPE_STRING)
		printf("%s\n", val->data.str);
	else if (val->type == TYPE_DOUBLE)
		printf("%f\n", val->data.nb);
	else if (val->type == TYPE_ARR)
		j_fill_arr(val->data.tab);
}

void		j_get_vec(t_json *json, t_obj *obj)
{
	int		cpt = 0;
	t_v		*nb;

	if (!ft_strcmp(json->key, "norm"))
		nb = &obj->norm;
	else if (!ft_strcmp(json->key, "pos"))
		nb = &obj->o;	
	if (json->val.type == TYPE_OBJ)
	{
		if (!ft_strcmp(json->val.data.obj->key, "x"))
		{
			nb->x = json->val.data.obj->val.data.nb;
			json->val.data.obj = json->val.data.obj->next;
			printf(">> x : %f\n", nb->x);
			cpt++;
		}
		if (!ft_strcmp(json->val.data.obj->key, "y") && cpt == 1)
		{
			nb->y = json->val.data.obj->val.data.nb;
			json->val.data.obj = json->val.data.obj->next;
			printf(">> y : %f\n", nb->y);
			cpt++;
		}
		if (!ft_strcmp(json->val.data.obj->key, "z") && cpt == 2)
		{
			cpt++;
			printf(">> z : %f\n", nb->z);
			nb->z = json->val.data.obj->val.data.nb;
			json->val.data.obj = json->val.data.obj->next;
		}
		if (cpt == 3)
			json = json->next;
	}
	
}

void		j_get_type(t_json *json, t_obj *obj)
{
	if (!ft_strcmp(json->val.data.str, "plane") || !ft_strcmp(json->val.data.str, "sphere")
		|| !ft_strcmp(json->val.data.str, "tube") || !ft_strcmp(json->val.data.str, "cone"))
		obj->type = json->val.data.str[0];
	printf(">> type : %c\n", obj->type);
	json = json->next;
}

void		j_get_color(t_json *json, t_obj *obj)
{
	obj->col = get_color(json->val.data.str);
	printf(">> color : %d\n", obj->col.c.r);
	json = json->next;
}

void		j_get_radius(t_json *json, t_obj *obj)
{
	obj->radius = json->val.data.nb;
	printf(">> radius : %f\n", obj->radius);
	json = json->next;
}

void		j_get_obj(t_json_arr *tab, t_par *par)
{
	t_obj	*obj = NULL;
	while (tab)
	{
		obj = malloc(sizeof(t_obj) * 1);
		while (tab->val.data.obj)
		{
			if (tab->val.data.obj)
			{
				if (!ft_strcmp(tab->val.data.obj->key, "type")
					&& tab->val.data.obj->val.type == TYPE_STRING)
					j_get_type(tab->val.data.obj, obj);
				else if (!ft_strcmp(tab->val.data.obj->key, "radius")
					&& tab->val.data.obj->val.type == TYPE_DOUBLE)
					j_get_radius(tab->val.data.obj, obj);
				else if (!ft_strcmp(tab->val.data.obj->key, "color")
					&& tab->val.data.obj->val.type == TYPE_STRING)
					j_get_color(tab->val.data.obj, obj);
				else if ((!ft_strcmp(tab->val.data.obj->key, "norm")
					|| !ft_strcmp(tab->val.data.obj->key, "pos"))
					&& tab->val.data.obj->val.type == TYPE_OBJ)
					j_get_vec(tab->val.data.obj, obj);
				tab->val.data.obj = tab->val.data.obj->next;
			}
		}
		printf("OBJ \n");
		tab = tab->next;
	}
	(void)par;
	printf("FIN \n");
}

void		j_fill_env(t_json *json)
{
	t_par	*par;

	par = malloc(sizeof(t_par) * 1);
	if (json)
	{
		printf("-- key : %s -- ", json->key);
		printf("\n");
		if (!ft_strcmp(json->key, "objects") && json->val.type == TYPE_ARR)
			j_get_obj(json->val.data.tab, par);
		j_fill_obj(&json->val);
		json = json->next;
		j_fill_env(json);
	}
}

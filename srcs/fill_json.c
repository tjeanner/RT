/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_json.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 01:49:37 by hbouchet          #+#    #+#             */
/*   Updated: 2018/03/12 16:04:05 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		j_fill_arr(t_json_arr *arr, t_par *par, t_env *env)
{
	j_fill_obj(&arr->val, par, env);
	if (arr->next)
		j_fill_arr(arr->next, par, env);
}

void		j_fill_obj(t_val *val, t_par *par, t_env *env)
{
	if (val->type == TYPE_OBJ)
		j_fill_env(val->data.obj, par, env);
	else if (val->type == TYPE_STRING)
		printf("%s\n", val->data.str);
	else if (val->type == TYPE_DOUBLE)
		printf("%f\n", val->data.nb);
	else if (val->type == TYPE_ARR)
		j_fill_arr(val->data.tab, par, env);
}

void		j_fill_env(t_json *json, t_par *par, t_env *env)
{
	t_obj	obj;
	t_lum	lum;
	t_cam	cam;

	if (json)
	{
		if (!ft_strcmp(json->key, "objects") && json->val.type == TYPE_ARR)
			j_get_obj(json->val.data.tab, &obj, par, env);
		if (!ft_strcmp(json->key, "lights") && json->val.type == TYPE_ARR)
			j_get_lights(json->val.data.tab, &lum, par, env);
		if (!ft_strcmp(json->key, "cameras") && json->val.type == TYPE_ARR)
			j_get_cam(json->val.data.tab, &cam, par, env);
		j_fill_obj(&json->val, par, env);
		json = json->next;
		j_fill_env(json, par, env);
	}
}
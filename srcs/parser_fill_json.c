/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_json.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 01:49:37 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/15 18:16:12 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		j_fill_scn(t_json *json, t_env *env)
{
	if (!ft_strcmp(json->key, "name") && json->val.type == TYPE_STRING)
	{
		free(env->name);
		env->name = ft_strdup(json->val.data.str);
		json = json->next;
	}
	if (!ft_strcmp(json->key, "filter") && json->val.type == TYPE_STRING)
	{
		free(env->filter);
		env->filter = ft_strdup(json->val.data.str);
//		free(json->val.data.str); //ARGH
		json = json->next;
	}
}

void		j_fill_arr(t_json_arr *arr, t_par *par, t_env *env)
{
	j_fill_obj(&arr->val, par, env);
	if (arr->next)
	{
		j_fill_arr(arr->next, par, env);
	}
}

void		j_fill_obj(t_val *val, t_par *par, t_env *env)
{
	if (val->type == TYPE_OBJ)
		j_fill_env(val->data.obj, par, env);
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
		j_fill_scn(json, env);
		if (!ft_strcmp(json->key, "objects") && json->val.type == TYPE_ARR)
		{
			j_get_obj(json->val.data.tab, &obj, par, env);
//			free(json->key);
		}
		else if (!ft_strcmp(json->key, "lights") && json->val.type == TYPE_ARR)
		{
			j_get_lights(json->val.data.tab, &lum, par, env);
//			free(json->key);
		}
		else if (!ft_strcmp(json->key, "cameras") && json->val.type == TYPE_ARR)
		{
			j_get_cam(json->val.data.tab, &cam, par, env);
//			free(json->key);
		}
		j_fill_obj(&json->val, par, env);
		free(json->key);
//		if (json->val.type == TYPE_STRING)
//			free(json->val.data.str);
		ft_memdel((void **)&json->val.data);
		json = json->next;
		j_fill_env(json, par, env);
	}
}

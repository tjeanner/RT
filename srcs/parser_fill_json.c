/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_json.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 01:49:37 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/27 19:56:34 by hbouchet         ###   ########.fr       */
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
		free(env->effects.filter);
		env->effects.filter = ft_strdup(json->val.data.str);
		json = json->next;
	}
	if (!ft_strcmp(json->key, "ambient") && json->val.type == TYPE_DOUBLE)
	{
		if (json->val.data.nb >= 0 && json->val.data.nb <= 1)
			env->lums.amb_coef = json->val.data.nb;
		else
			env->lums.amb_coef = (json->val.data.nb < 0) ? 0 : 1;
		json = json->next;
	}
	if (!ft_strcmp(json->key, "depth") && json->val.type == TYPE_DOUBLE)
	{
		if (json->val.data.nb >= 0 && json->val.data.nb <= 1)
			env->effects.depth = json->val.data.nb;
		else
			env->effects.depth = (json->val.data.nb < 0) ? 0 : 1;
		json = json->next;
	}
}

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
	else if (val->type == TYPE_ARR)
		j_fill_arr(val->data.tab, par, env);
}

void		j_fill_env(t_json *json, t_par *par, t_env *env)
{
	t_obj	obj;
	t_lum	lum;
	t_cam	cam;
	t_json	*p;

	p = json;
	if (p)
	{
		j_fill_scn(p, env);
		if (!ft_strcmp(p->key, "objects") && p->val.type == TYPE_ARR)
			j_get_obj(p->val.data.tab, &obj, par, env);
		else if (!ft_strcmp(p->key, "lights") && p->val.type == TYPE_ARR)
			j_get_lights(p->val.data.tab, &lum, par, env);
		else if (!ft_strcmp(p->key, "cameras") && p->val.type == TYPE_ARR)
			j_get_cam(p->val.data.tab, &cam, par, env);
		j_fill_obj(&p->val, par, env);
		p = p->next;
		j_fill_env(p, par, env);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_json.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 01:49:37 by hbouchet          #+#    #+#             */
/*   Updated: 2018/03/11 15:26:28 by hbouchet         ###   ########.fr       */
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

void		j_fill_env(t_json *json)
{
	if (json)
	{
		printf("key : %s -- ", json->key);
		j_fill_obj(&json->val);
		json = json->next;
		j_fill_env(json);
	}
}

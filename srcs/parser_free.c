/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 02:37:14 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/17 10:45:27 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		ft_free_arr(t_json_arr *tab)
{
	if (tab->next)
	{
		ft_free_arr(tab->next);
//		ft_memdel((void **)&tab->next);
	}
	else
	{
		if (tab->val.data.obj->next)
			ft_parser_free(tab->val.data.obj->next);
		else if (tab->val.data.obj)
		{
			ft_parser_free(tab->val.data.obj);
//			free(tab->val.data.obj);
		}
//		free(tab);
	}
//	if (tab)
//		free(tab);
}

void		ft_parser_free(t_json *json)
{
	if (json->next)
		ft_parser_free(json->next);
	else
	{
//		printf("%s\n", json->key);
		free(json->key);
		if (json->val.type == TYPE_STRING)
		{
//			printf("> %s\n", json->val.data.str);
			free(json->val.data.str);
		}
		else if (json->val.type == TYPE_ARR)
			ft_free_arr(json->val.data.tab);
		else if (json->val.type == TYPE_DOUBLE)
			;
		else if (json->val.type == TYPE_OBJ)
			ft_parser_free(json->val.data.obj);
//		free(json);
	}
}
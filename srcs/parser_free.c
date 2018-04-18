/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 02:37:14 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/18 16:02:28 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		ft_free_arr(t_json_arr *tab)
{
	if (tab->next)
	{
		ft_free_arr(tab->next);
		free(tab->next);
	}
	if (tab->val.data.obj->next)
	{
		ft_parser_free(tab->val.data.obj->next);
		free(tab->val.data.obj->next);
		tab->val.data.obj->next = NULL;
	}
	ft_parser_free(tab->val.data.obj);
	free(tab->val.data.obj);
}

void			ft_parser_free(t_json *json)
{
	if (json->next)
	{
		ft_parser_free(json->next);
		free(json->next);
	}
	free(json->key);
	if (json->val.type == TYPE_STRING)
		free(json->val.data.str);
	else if (json->val.type == TYPE_ARR)
	{
		ft_free_arr(json->val.data.tab);
		free(json->val.data.tab);
	}
	else if (json->val.type == TYPE_DOUBLE)
		;
	else if (json->val.type == TYPE_OBJ)
	{
		ft_parser_free(json->val.data.obj);
		free(json->val.data.obj);
	}
}

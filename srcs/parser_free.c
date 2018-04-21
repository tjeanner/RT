/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 02:37:14 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/20 23:51:44 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		ft_free_arr(t_json_arr *tab)
{
//	static int i = 0;
//	int j = 0;

//	printf("= tab : %d=\n", i++);
/*	while (tab)
	{
//		printf(">> obj : %d\n", j++);
		ft_parser_free(tab->val.data.obj);
		free(tab->val.data.obj);
		tab = tab->next;
	}
*/	
	if (tab->next)
	{
		ft_free_arr(tab->next);
		free(tab->next);
		tab->next = NULL;
	}
	ft_parser_free(tab->val.data.obj);
	free(tab->val.data.obj);
}

void			ft_parser_free(t_json *json)
{
//	staticint i = 0;
/*
	while (json)// && json->next)
	{
		printf("%s\n", json->key);
		free(json->key);
		if (json->val.type == TYPE_STRING)
		{
			printf("> %s\n", json->val.data.str);			
			free(json->val.data.str);
		}
		else if (json->val.type == TYPE_DOUBLE)
			printf("> %f\n", json->val.data.nb);
		else if (json->val.type == TYPE_OBJ)
			ft_parser_free(json->val.data.obj);
		else if (json->val.type == TYPE_ARR)
		{
			while (json->val.data.tab)// && json->val.data.tab->next)
			{
				ft_parser_free(json->val.data.tab->val.data.obj);
				free(json->val.data.tab->val.data.obj);
				json->val.data.tab = json->val.data.tab->next;
			}
		}
//		free(json);
		json = json->next;
	}
*/
	if (json->next)
	{
		ft_parser_free(json->next);
		free(json->next);
	}
	free(json->key);
//	printf("> %d\n", json->val.type);	
	if (json->val.type == TYPE_STRING)
	{
		free(json->val.data.str);
	}
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
//	free(json);
}

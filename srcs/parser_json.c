/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_json.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 00:52:17 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/20 23:41:06 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_json_arr		*parse_arr(char **str)
{
	t_json_arr	*arr;

	arr = NULL;
	skip_whitespaces(str);
	if (**str != ']')
	{
		*str += 1;
		if (!(arr = malloc(sizeof(t_json_arr) * 1)))
			error_mgt(0);			
		arr->val = parse_obj(str);
		arr->next = parse_arr(str);
	}
	else
		*str += 1;
	return (arr);
}

int				def_type(char **str)
{
	int			type;

	if (**str == '"')
		type = TYPE_STRING;
	else if (**str == '-' || **str == '+' || ft_isdigit(**str))
		type = TYPE_DOUBLE;
	else if (**str == '{' || **str == ',')
		type = TYPE_OBJ;
	else if (**str == '[')
		type = TYPE_ARR;
	else
		type = -1;
	return (type);
}

t_val			parse_obj(char **str)
{
	t_val		val;

	val.type = def_type(str);
	skip_whitespaces(str);
	if (**str == '"')
		val.data.str = parse_str(str);
	else if (**str == '-' || **str == '+' || ft_isdigit(**str))
		val.data.nb = parse_float(str);
	else if (**str == '{')
	{
		val.data.obj = parse_json(str);
		*str += (ft_strchr(*str, '}') - *str) + 1;
	}
	else if (**str == ',')
		val.data.obj = parse_json(str);
	else if (**str == '[')
	{
		val.data.tab = parse_arr(str);
	}
	else
		error_mgt(1);
	skip_whitespaces(str);
	return (val);
}

t_json			*parse_json(char **str)
{
	t_json		*json;
	int			cpt;

	json = NULL;
	cpt = init_json(&json);
	if (**str == '{' || **str == ',')
	{
		*str += 1;
		skip_whitespaces(str);
		if (**str == '"' && ++cpt)
			json->key = parse_str(str);
		if (**str == ':' && ++cpt)
		{
			*str += 1;
			skip_whitespaces(str);
			if (**str == ',' || **str == '}')
				error_mgt(1);
			json->val = parse_obj(str);
		}
		if (**str == ',' && ++cpt)
			json->next = parse_json(str);
		if (!cpt)
			error_mgt(1);
	}
	return ((!json->key) ? NULL : json);
}

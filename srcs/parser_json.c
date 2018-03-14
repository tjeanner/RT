/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_json.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 00:52:17 by hbouchet          #+#    #+#             */
/*   Updated: 2018/03/14 10:28:29 by hbouchet         ###   ########.fr       */
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
		arr = malloc(sizeof(t_json_arr) * 1);
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
	skip_whitespaces(str);
	return (val);
}

t_json			*parse_json(char **str)
{
	t_json		*json;
	int			cpt = 0;

	json = NULL;
	json = malloc(sizeof(t_json) * 1);
	json->next = NULL;
	json->key = NULL;
	if (**str == '{' || **str == ',')
	{
		*str += 1;
		skip_whitespaces(str);
		if (**str == '"')
		{
			json->key = parse_str(str);
			skip_whitespaces(str);
			cpt++;
		}
		if (**str == ':')
		{
			*str += 1;
			skip_whitespaces(str);
			json->val = parse_obj(str);
			cpt++;
		}
		if (**str == ',')
		{
			json->next = parse_json(str);
			cpt++;
		}
		if (!cpt)
			ft_put_err("lol");
	}
	if (!json->key)
		return (NULL);
	return (json);
}

void			j_init(t_env *env)
{
	int		ret;
	int		fd;
	char	*line;
	char	*tmp;
	t_par	par;

	env->nb_obj = 0;
	env->nb_cam = 0;
	env->nb_lum = 0;
	fd = open(env->file, O_RDONLY);
	tmp = ft_strnew(0);
	while ((ret = get_next_line(fd, &line)) > 0)
		tmp = ft_strjoinfree(tmp, line, 'B');
	if (!brackets(tmp, ft_strlen(tmp)))
		ft_put_err("invalid json");
	env->json = parse_json(&tmp);
	j_fill_env(env->json, &par, env);
	if (env->nb_lum == 0 || env->nb_cam == 0)
		ft_put_err("invalid scene");
	malloc_env(env);
	set_struct(env, &par);
}

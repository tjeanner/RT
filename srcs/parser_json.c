/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_json.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 00:52:17 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/17 10:35:50 by hbouchet         ###   ########.fr       */
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
	else
		ft_put_err("invalid json");
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
				ft_put_err("invalid json");
			json->val = parse_obj(str);
		}
		if (**str == ',' && ++cpt)
			json->next = parse_json(str);
		if (!cpt)
			ft_put_err("invalid json");
	}
	return ((!json->key) ? NULL : json);
}

void			j_init(t_env *env)
{
	int		ret;
	int		fd;
	char	*line;
	char	*tmp;
	t_par	par;
	t_json	*fjson;

	env->nb_obj = 0;
	env->nb_cam = 0;
	env->nb_lum = 0;
	env->name = ft_strdup("RT");
	env->filter = ft_strdup("NONE");
	if (!(fd = open(env->file, O_RDONLY)))
		ft_put_err("usage : ./rtv1 <scene.json>");
	tmp = ft_strnew(0);
	while ((ret = get_next_line(fd, &line)) > 0)
		tmp = ft_strjoinfree(tmp, line, 'B');
	free(line);
	line = tmp;
	if (!brackets(tmp, ft_strlen(tmp)))
		ft_put_err("invalid json");
	env->json = parse_json(&tmp);
	fjson = env->json;
	free(line);
	j_fill_env(fjson, &par, env);
//	ft_memdel((void **)&(env->json));
	if (env->nb_cam == 0)
		ft_put_err("invalid scene");
	malloc_env(env);
	set_struct(env, &par);
	ft_parser_free(env->json);
}

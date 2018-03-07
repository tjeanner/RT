/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_json.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 00:52:17 by hbouchet          #+#    #+#             */
/*   Updated: 2018/03/07 08:13:15 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void        skip_whitespaces(char **str)
{
    while (**str == ' ' || **str == '\t' || **str == '\n')
        *str += 1;
}

t_json_arr      *parse_arr(char **str)
{
    t_json_arr *arr;

    arr = malloc(sizeof(t_json_arr) * 1);
    arr->next = NULL;
    skip_whitespaces(str);    
    if (**str != ']')
    {
        arr->val = parse_obj(str);
        arr->next = parse_arr(str);
    }
    return (arr);
}

t_val         parse_obj(char **str)
{
    t_val   val;

    skip_whitespaces(str);
    if (**str == '"')
    {
        *str += 1;
        val.type = TYPE_STRING;
        val.data.str = ft_strsub(*str, 0, (ft_strchr(*str, '"') - *str));
        *str += (ft_strchr(*str, '"') - *str) + 1;
        printf(">%s\n", val.data.str);
    }
    else if (**str == '-' || **str == '+' || ft_isdigit(**str))
    {
        val.type = TYPE_DOUBLE;
        val.data.nb = ft_atof(*str);
        *str += (ft_strchr(*str, ',') - *str);
        printf(">%f\n", val.data.nb);
//        printf("@@@%s\n", *str);
    }
    else if (**str == '{')
    {
        val.type = TYPE_OBJ;
        val.data.obj = parse_json(str);
        *str += (ft_strchr(*str, '}') - *str) + 1;
    }
    else if (**str == ',')
    {
        val.type = TYPE_OBJ;
        val.data.obj = parse_json(str);
//        *str += (ft_strchr(*str, ',') - *str) + 1;
    }
    else if (**str == '[')
    {
        *str += 1;
        val.type = TYPE_ARR;
        val.data.tab = parse_arr(str);
    }
    else
    {
        val.type = 0;
    }
    skip_whitespaces(str);      
    return (val);
}

t_json        *parse_json(char **str)
{
    t_json  *json;

    json = malloc(sizeof(t_json) * 1);
    json->next = NULL;
    if (**str == '{' || **str == ',')
    {
        *str += 1;
        skip_whitespaces(str);
        if (**str == '"')
        {
            *str += 1;
            json->key = ft_strsub(*str, 0, (ft_strchr(*str, '"') - *str));
            printf("%s : ", json->key);
            *str += (ft_strchr(*str, '"') - *str) + 1;
        }
        if (**str == ':')
        {
            *str += 1;
            skip_whitespaces(str);
            json->val = parse_obj(str);
        }
        if (**str == ',')
        {
//            *str += 1;
            json->next = parse_json(str);
//            skip_whitespaces(str);
        }
    }
    return (json);
}

void        j_init(t_env *env)
{
    int ret;
    int fd;
    char *line;
    char *tmp;

	env->nb_obj = 0;
	env->nb_cam = 0;
	env->nb_lum = 0;
    fd = open(env->file, O_RDONLY);
    tmp = ft_strnew(0);
    while ((ret = get_next_line(fd, &line)) > 0)
        tmp = ft_strjoinfree(tmp, line, 'B');
    parse_json(&tmp);
//    printf(">%s\n", tmp);
}
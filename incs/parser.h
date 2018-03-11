/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 03:13:01 by hbouchet          #+#    #+#             */
/*   Updated: 2018/03/11 14:53:29 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_env        t_env;
typedef struct s_json       t_json;
typedef struct s_json_arr   t_json_arr;

enum
{
    TYPE_STRING, TYPE_DOUBLE, TYPE_OBJ, TYPE_ARR
};

typedef union			    u_data
{
    char                    *str;
    float                   nb;
    t_json                  *obj;
    t_json_arr              *tab;
}                           t_data;

typedef struct              s_val
{   
    int                     type;
    t_data                  data;
}                           t_val;

typedef struct              s_json
{       
    char                    *key;
    t_val                   val;
    t_json                  *next;
}                           t_json;
        
typedef struct              s_json_arr
{       
    t_val                   val;
    t_json_arr              *next;              
}                           t_json_arr;

/*
**json_parser.c
*/
void					j_init(t_env *env);
t_json                 *parse_json(char **str);
t_val                   parse_obj(char **str);

/*
**fill_json.c
*/
void                    j_fill_env(t_json *json);
void       j_fill_obj(t_val *val);

/*
**parse_function.c
*/
char        *parse_str(char **str);
float       parse_float(char **str);
void        skip_whitespaces(char **str);

#endif
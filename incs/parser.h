/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 03:13:01 by hbouchet          #+#    #+#             */
/*   Updated: 2018/03/07 07:29:38 by hbouchet         ###   ########.fr       */
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

#endif
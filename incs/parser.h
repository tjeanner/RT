/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 03:13:01 by hbouchet          #+#    #+#             */
/*   Updated: 2018/03/15 13:49:04 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_env        t_env;
typedef struct s_cam        t_cam;
typedef struct s_lum        t_lum;
typedef union u_color      t_color;
typedef struct s_v          t_v;
typedef struct s_par        t_par;
typedef struct s_obj        t_obj;
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
void                    j_fill_env(t_json *json, t_par *par, t_env *env);
void                    j_fill_obj(t_val *val, t_par *par, t_env *env);

/*
**parse_function.c
*/
char                    *parse_str(char **str);
float                   parse_float(char **str);
void                    skip_whitespaces(char **str);
int			            init_json(t_json **json);

/*
**get_value_json.c
*/
t_v		                j_get_vec(t_json *json);
void	            	j_get_type(t_json *json, t_obj *obj);
t_color	            	j_get_color(t_json *json);
void            		j_get_radius(t_json *json, t_obj *obj);

/*
**get_scene_json.c
*/
void	            	j_get_obj(t_json_arr *tab, t_obj *obj, t_par *par, t_env *env);
void	            	j_get_lights(t_json_arr *tab, t_lum *lum, t_par *par, t_env *env);
void	            	j_get_cam(t_json_arr *tab, t_cam *cam, t_par *par, t_env *env);

/*
**valid_json.c
*/
int		                j_is_valid_obj(t_obj *obj);
int		                j_is_valid_cam(t_cam *cam);
int		                j_is_valid_lum(t_lum *lum);
int			            brackets(char *str, int len);

#endif
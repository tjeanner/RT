/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 18:01:28 by tjeanner          #+#    #+#             */
/*   Updated: 2018/02/08 12:50:10 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "libft.h"
# include <fcntl.h>//open
# include <sys/types.h>//read
# include <sys/uio.h>//read
# include <unistd.h>//read, write, close
# include <stdlib.h>//malloc, free
# include <stdio.h>//perror, strerror
# include <string.h>//strerror
# include "SDL.h"
# include <string.h>
# include <stdbool.h>
# include <pthread.h>

//# define WIN_X 1920
//# define WIN_Y 1080
# define WIN_X 640
# define WIN_Y 480
# define DIST ((int)WIN_X / tan(30 * M_PI / 180))
# define BPP 32
# define FCTS "sptc"

typedef union			u_color
{
	unsigned int		color;
	struct
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	a;
	}					c;
}						t_color;

typedef struct			s_v
{
	double				x;
	double				y;
	double				z;
}						t_v;

typedef struct			s_obj
{
	char				type;
	float				radius;
	t_v					o;
	t_v					norm;
	t_color				col;
	double				dist;
	t_v					r;
	float				p;
}						t_obj;

typedef struct			s_cam
{
	t_v					pos_cam;
	t_v					vcam;
	t_v					v2cam;
	t_v					v3cam;	
}						t_cam;

typedef struct			s_lum
{
	t_v					pos_lum;
	float				coef;
	t_color				col;
}						t_lum;

typedef struct			s_ray
{
	double				v1;
	double				v2;
	t_v					r;
	t_v					r2;
}						t_ray;

typedef struct			s_par
{
	t_list				*lst_obj;
	t_list				*lst_cam;
	t_list				*lst_lum;
}						t_par;

typedef struct			s_env
{
	SDL_Window			*win;
	SDL_Surface			*surf;
	int					state;
	int					nb_obj;
	int					curr_obj;
	int					nb_cam;
	int					curr_cam;
	int					nb_lum;
	t_obj				*objs;
	t_cam				*cams;
	t_lum				*lums;
	t_ray				init_rays;
	float				flou;
	char				*file;
	int					(*col_fcts[4])(t_ray *init_rays, t_obj obj);
}						t_env;

/*
**main.c
*/
void					rays(t_env *env);
int						init_ray(t_env *env, float x, float y);
int						which_obj_col(t_env *env);

/*
**vector_math.c
*/
double					vect_norm(t_v a);
t_v						vect_mult(t_v a, double n);
t_v						vect_add(t_v a, t_v b);
double					vect_scal_prod(t_v a, t_v b);
t_v						vect_prod(t_v a, t_v b);

/*
**color_math.c
*/
t_color					get_white(void);
t_color					get_black(void);
int						set_white(t_color *c);
int						set_black(t_color *c);
t_color					add_color(t_color a, t_color b);
t_color					mult_color(t_color a, float n);
int						average_color(t_color *col, float flou);

/*
**useless_functions.c
*/
double					which_pow(double num, double pow);
t_color					get_black(void);

/*
**events.c
*/
int						events(t_env *env);

/*
**parser.c
*/
void					init_scene(t_env *env);
int						putlineerr(char *str, int i);

/*
**get_scene.c
*/
t_color					get_color(char *hexa);
void					get_obj(char **arr, t_obj *objet);
void					get_cam(char **arr, t_cam *cam);
void					get_lum(char **arr, t_lum *lum);
int						get_scenelen(t_env *env);

/*
**fill_env.c
*/
int						is_valid_obj(char **str, int n_line);
int						is_valid_lum(char **str, int n_line);
int						is_valid_cam(char **str, int n_line);
void					set_list(t_env *env, char *line, t_par *par, int i);
void					set_struct(t_env *env, t_par *par);
t_v						rotation(t_v n, t_v r, float t);

/*
**distances_functions.c
*/
int						get_dist_cone(t_ray *init_rays, t_obj obj);
int						get_dist_tube(t_ray *init_rays, t_obj obj);
int						get_dist_plan(t_ray *init_rays, t_obj obj);
int						get_dist_sphere(t_ray *init_rays, t_obj obj);


#endif

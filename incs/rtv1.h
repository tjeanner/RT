/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 18:01:28 by tjeanner          #+#    #+#             */
/*   Updated: 2018/04/16 14:10:40 by tjeanner         ###   ########.fr       */
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
# include "parser.h"

# define WIN_X 1357
# define WIN_Y 867
//# define WIN_X 640
//# define WIN_Y 480
# define DIST ((int)WIN_X / tan(30.000 * TORAD))
# define BPP 32
# define FCTS "sptc"
# define S "0123456789ABCDEF"
# define TORAD M_PI / 180.000
# define TODEG 180.000 / M_PI

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
	float				k_diff;
	float				transp;
	float				k_spec;
	float				k_phong;
}						t_obj;

typedef struct			s_cam
{
	t_v					pos;
	t_v					vcam;
	t_v					v2cam;
	t_v					v3cam;	
}						t_cam;

typedef struct			s_lum
{
	t_v					pos;
	float				coef;
	t_color				col;
}						t_lum;

typedef struct			s_ray
{
	double				d1;
	double				d2;
	t_v					pos;
	t_v					dir;
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
	int					curr_lum;
	char				*filter;
	int					seuil;
	t_obj				*objs;
	t_cam				*cams;
	t_lum				*lums;
	t_ray				init_rays;
	int					flou;
	float				amb_coef;
	float				coefs_sum;
	float				constante2test;
	float				portion;
	char				*file;
	char				*name;
	int					(*col_fcts[4])(t_ray *init_rays, t_obj obj);
	t_json				*json;
}						t_env;

/*
**main.c
*/
void					rays(t_env *env);
int						init_ray(t_env *env, double x, double y);
int						which_obj_col(t_env *env);

/*
**vector_math.c
*/
double					get_vect_norm(t_v a);
t_v						vect_norm(t_v a);
t_v						vect_mult(t_v a, double n);
t_v						vect_div(t_v a, double n);
t_v						vect_add(t_v a, t_v b);
t_v						vect_sous(t_v a, t_v b);
double					vect_scal(t_v a, t_v b);
t_v						vect_prod(t_v a, t_v b);
t_v						vect_inv(t_v a);

/*
**color_math.c
*/
t_color					satur_col(t_color a, float n);
t_color					get_rand(void);
t_color					get_white(void);
t_color					get_black(void);
int						set_white(t_color *c);
int						set_black(t_color *c);
t_color					add_color(t_color a, t_color b);
t_color					mult_color(t_color a, float n);
t_color					div_color(t_color a, float n);
int						average_color(t_color *col, float flou);

/*
**useless_functions.c
*/
double					which_pow(double num, double pow);
t_color					get_black(void);
void					ft_putfloat_fd(double nbr, int fd);

/*
**raytracing.c
*/
void					rays(t_env *env);
int						which_obj_col(t_env *env);
int						init_ray(t_env *env, double x, double y);
t_v						get_norm(t_obj obj, t_ray init_rays, t_v pos_col);
t_color					get_col(t_env *env, t_v ray_dir);

/*
**events.c
*/
int						events(t_env *env);

/*
**events_sel.c
*/
int						event_cam_switch(t_env *env, unsigned int sym);
int						events_sel(t_env *env, SDL_Event event, unsigned int sym);

/*
**events_rotation.c
*/
int						events_rotation(t_env *env, unsigned int sym, t_v *norm);

/*
**events_move.c
*/
int						events_move(t_env *env, unsigned int sym, t_cam *cam, t_obj *obj);
void					mouse_move(t_env *env, SDL_Event event, t_cam *cam, t_obj *obj);

/*
**norm_manip.c
*/
t_v						norm_vect(double x, double y, double z);
int						is_norm_wchar(double x, double y, double z);
t_v						rotation(t_v n, t_v r, float t);

/*
**update_and_copy.c
*/
void					update_and_copy_r(t_env *env, int obj);
void					update_and_copy_a(t_env *env, SDL_Keycode type);

/*
**distances_functions.c
*/
int						get_dist_cone(t_ray *init_rays, t_obj obj);
int						get_dist_tube(t_ray *init_rays, t_obj obj);
int						get_dist_plan(t_ray *init_rays, t_obj obj);
int						get_dist_sphere(t_ray *init_rays, t_obj obj);

/*
**filter.c
*/
void 					set_filter(t_env *env);

void					ft_free4all(t_env *env, char *str);

#endif

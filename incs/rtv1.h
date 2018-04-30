/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 18:01:28 by tjeanner          #+#    #+#             */
/*   Updated: 2018/04/30 04:25:54 by hbouchet         ###   ########.fr       */
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
# define NB_THREADS 8
# define FCTS "sptc"
# define S "0123456789ABCDEF"
# define ABS(x) (x < 0 ? -x : x)
# define TORAD M_PI / 180.000
# define TODEG 180.000 / M_PI


enum						e_typeobj
{
	SPHERE, PLANE, CYLINDRE, CONE
}							t_typeobj;

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

typedef struct			s_line
{
	t_v					pos;
	t_v					dir;
}						t_line;

typedef struct			s_ray
{
	int					obj;
	int					prev_obj;
	double				dist;
	double				total_dist;
	t_line				from;
	t_line				to;
}						t_ray;

typedef struct			s_obj
{
	char				type;
	float				radius;
	float				radius2;
	t_v					o;
	t_v					norm;
	t_color				col;
//	double				dist;
	float				k_diff;
	float				transp;
	float				k_spec;
	float				k_phong;
	float				reflect;
	float				refract;
	unsigned int		motion;
	unsigned int		tex;
}						t_obj;

typedef struct			s_cam
{
	t_v					pos;
	t_v					vcam;
	t_v					v2cam;
	t_v					v3cam;
	t_color				col;
}						t_cam;

typedef struct			s_lum
{
	t_v					pos;
	float				coef;
	t_color				col;
}						t_lum;

typedef struct			s_objs
{
	int					nb;
	int					curr;
	t_obj				*obj;
	int					(*col_fcts[4])(t_line line, t_obj obj, double *res);
}						t_objs;

typedef struct			s_cams
{
	int					nb;
	int					curr;
	t_cam				*cam;
}						t_cams;

typedef struct			s_lums
{
	int					nb;
	int					curr;
	float				amb_coef;
	float				coefs_sum;
	t_lum				*lum;
}						t_lums;

typedef struct			s_par
{
	t_list				*lst_obj;
	t_list				*lst_cam;
	t_list				*lst_lum;
}						t_par;

typedef struct			s_effects
{
	char				alias;
	char				stereo;
	char				*filter;
	int					seuil;
	unsigned int		depth;
}						t_effects;

typedef struct			s_threads
{
	pthread_t			id;
	int					start;
	int					incr;
	t_env				*env;
}						t_threads;

typedef struct			s_display
{
	int					sur;
	SDL_Window			*win;
	SDL_Surface			*surf;
	SDL_Surface			*surf2;
}						t_display;

typedef struct			s_env
{
	int					state;
	t_objs				objs;
	t_cams				cams;
	t_lums				lums;
	t_display			display;
	t_effects			effects;
	t_threads			*threads;
	char				*file;
	char				*name;
}						t_env;

/*
**main.c
*/
void					tutu(t_env *env);
void					*rays(void *tmp);
t_ray					init_line(double x, double y, t_cam cam);


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
t_v						vect_reflect(t_v incident, t_v normal);
t_v						vect_refract(t_v incident, t_v normal, double k);

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
int						which_obj_col(t_objs *objs, t_ray *line);
t_v						get_norm(t_obj obj, t_ray *line);
t_color					get_col(t_objs *objs, t_lums *lums, t_ray *line,
																unsigned int d);
t_color					get_lum(t_objs *objs, int obj, t_lum lum, t_ray *line);

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
int						get_dist_cone(t_line line, t_obj obj, double *res);
int						get_dist_tube(t_line line, t_obj obj, double *res);
int						get_dist_plan(t_line line, t_obj obj, double *res);
int						get_dist_sphere(t_line line, t_obj obj, double *res);
int						get_dist_torus(t_line line, t_obj obj, double *res);

/*
**filter.c
*/
void 					set_filter(t_env *env);
void					stereo_filter(t_env *env);
void					motionblur_filter(t_env *env);
void					cartoon_filter(t_env *env);
void					color_filter(t_env *env, SDL_Surface *surf, t_color color);

/*
**textures.c
*/
double					checkerboard(t_ray *line);

/*
**error_mgt.c
*/
void					*error_mgt(int status);
void					ft_freeenv(t_env *env);

#endif

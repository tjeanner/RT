/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 18:01:28 by tjeanner          #+#    #+#             */
/*   Updated: 2018/05/04 07:13:29 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RT_H
# define __RT_H

# include "libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "SDL.h"
# include <string.h>
# include <stdbool.h>
# include <pthread.h>
# include "parser.h"

# define WIN_X 1080
# define WIN_Y 720
# define DIST ((int)WIN_X / tan(30.000 * TORAD))
# define BPP 32
# define NB_THREADS 8
# define S "0123456789ABCDEF"
# define TORAD M_PI / 180.000
# define TODEG 180.000 / M_PI
# define IN_OBJ 1
# define OUT_OBJ 0
# define MARGIN 0.00000001

typedef struct s_env	t_env;

typedef enum			e_typeobj
{
	NONE = -1, SPHERE, PLANE, CYLINDRE, CONE, TORUS
}						t_typeobj;

typedef enum			e_typeact
{
	NOPE, ROTATION, TRANSLATION, COLOR
}						t_typeact;

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

typedef struct			s_tri
{
	t_v					v[3];
	t_v					vt[3];
	t_v					vn[3];
}						t_tri;

typedef struct			s_pobj
{
	int					nbtri;
	int					index;
	t_v					*v;
	t_v					*vt;
	t_v					*vn;
	t_v					nb;
	t_v					i;
	t_tri				*tri;
}						t_pobj;

typedef struct			s_screen
{
	int					time;
	int					rec;
	int					play;
}						t_screen;

typedef struct			s_line
{
	t_v					pos;
	t_v					dir;
}						t_line;

typedef struct			s_ray
{
	int					obj;
	double				dist;
	double				total_dist;
	double				n1;
	double				n2;
	t_line				from;
	t_line				to;
	struct s_ray		*incident;
	char				*objs;
	int					nb_objs;
	t_color				col;
}						t_ray;

typedef struct			s_act
{
	int					action;
	int					p;
	t_v					max;
	t_v					min;
	t_v					axis;
	t_v					movedist;
	double				speed;
	double				dist;
	double				angle;
	double				start;
}						t_act;

typedef struct			s_mat
{
	unsigned int		tex;
	double				rough;
	double				plastic;
	unsigned int		scale;
}						t_mat;

typedef struct			s_obj
{
	t_typeobj			type;
	float				radius;
	float				radius2;
	t_v					o;
	t_v					norm;
	t_v					norm2;
	t_color				col;
	float				k_diff;
	float				transp;
	float				k_spec;
	float				k_phong;
	float				reflect;
	float				refract;
	t_act				act;
	t_mat				mat;
	int					link;
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
	t_v					dir;
	float				coef;
	t_color				col;
}						t_lum;

typedef struct			s_objs
{
	int					nb;
	int					curr;
	int					nbtri;
	t_obj				*obj;
	t_tri				*tri;
	int					(*col_fcts[4])(t_line line, t_obj obj, t_v *res);
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
	float				alias;
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

struct					s_env
{
	int					state;
	t_objs				objs;
	t_cams				cams;
	t_lums				lums;
	t_display			display;
	t_effects			effects;
	t_threads			*threads;
	t_screen			screen;
	char				*file;
	char				*name;
};

/*
**init.c
*/
void					data_init_and_reload(t_env *env);
t_env					*init(char *filename);
void					*rays(void *tmp);

/*
**main.c
*/
void					thread_create(t_env *env);

/*
**vector_math.c
*/
t_v						vect_sous(t_v a, t_v b);
double					vect_scal(t_v a, t_v b);
t_v						vect_prod(t_v a, t_v b);
t_v						vect_inv(t_v a);

/*
**vector_math2.c
*/
double					get_vect_norm(t_v a);
t_v						vect_norm(t_v a);
t_v						vect_mult(t_v a, double n);
t_v						vect_div(t_v a, double n);
t_v						vect_add(t_v a, t_v b);

/*
**vector_math3.c
*/
t_v						vect_reflect(t_v incident, t_v normal);
t_v						vect_refract(t_v incident, t_v normal, double k);

/*
**color_math.c
*/
t_color					add_color(t_color a, t_color b);
t_color					sub_color(t_color a, t_color b);
t_color					mult_color(t_color a, float n);
t_color					div_color(t_color a, float n);
t_color					prod_color(t_color a, t_color b);

/*
**color_math2.c
*/
t_color					get_rand(void);
t_color					get_black(void);
t_color					get_white(void);
int						set_black(t_color *c);
int						set_white(t_color *c);

/*
**color_math3.c
*/
t_color					satur_col(t_color a, float n);
t_color					average_color(t_color *col, float flou);

/*
**useful_functions.c
*/
double					which_pow(double num, double pow);
void					ft_putfloat_fd(double nbr, int fd);
void					ft_freeenv(t_env *env);

/*
**raytracing.c
*/
t_ray					init_line(double x, double y, t_cam cam);
int						which_obj_col(t_objs *objs, t_ray *line);
t_v						get_norm(t_obj obj, t_ray *line);
t_color					get_col(t_objs *objs, t_lums *lums, t_ray *line,
								unsigned int d);

/*
** next_rays.c
*/
t_color					get_refract(t_objs *objs, t_lums *lums, t_ray *line,
								unsigned int d);
t_color					get_reflect(t_objs *objs, t_lums *lums, t_ray *line,
								unsigned int d);

/*
** lum.c
*/
t_color					get_lum(t_objs *objs, int obj, t_lum lum, t_ray *line);
void					*raytrace(t_env *env, void *tmp);

/*
**events.c
*/
int						events(t_env *env);

/*
**events_sel.c
*/
int						event_cam_switch(t_env *env, unsigned int sym);
int						events_sel(t_env *env, SDL_Event event,
							unsigned int sym);
int						move_events(t_env *env, unsigned int sym);

/*
**events_rotation.c
*/
int						events_rotation(t_env *env, unsigned int sym,
							t_v *norm);

/*
**events_move.c
*/
int						events_move(t_env *env, unsigned int sym,
									t_cam *cam, t_obj *obj);
void					mouse_move(t_env *env, SDL_Event event,
									t_cam *cam, t_obj *obj);

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
void					update_and_copy_a(t_env *env, SDL_Keycode type,
															t_obj *obj);

/*
**distances_functions.c
*/
int						get_dist_cone(t_line line, t_obj obj, t_v *res);
int						get_dist_tube(t_line line, t_obj obj, t_v *res);
int						get_dist_plan(t_line line, t_obj obj, t_v *res);
int						get_dist_sphere(t_line line, t_obj obj, t_v *res);

/*
**filter.c
*/
void					set_filter(t_env *env);
void					stereo_filter(t_env *env);
void					motionblur_filter(t_env *env);
void					cartoon_filter(t_env *env);
void					color_filter(t_env *env, SDL_Surface *surf,
									t_color color);

/*
**textures.c
*/
double					checkerboard(t_ray *line);

/*
**error_mgt.c
*/
void					*error_mgt(int status);

/*
** event_screen.c
*/
void					ev_screen(t_env *env, SDL_Event event);
void					ev_screenshot(t_env *env);

/*
**action.c
*/
void					main_action(t_objs *objs, int play);
t_act					init_act(int action, t_v axis, int speed,
														t_v maxmin[2]);
void					action(t_obj *obj);
void					act_movaxis(t_obj *obj);
int						vect_equal(t_v v1, t_v v2);

void					j_print_cam(t_env *env, int i, int fd);
void					j_print_lum(t_env *env, int i, int fd);

void					create_torus(t_env *env);

#endif

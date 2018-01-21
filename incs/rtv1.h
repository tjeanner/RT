/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 18:01:28 by tjeanner          #+#    #+#             */
/*   Updated: 2018/01/21 06:07:31 by tjeanner         ###   ########.fr       */
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

# define WIN_X 640
# define WIN_Y 480
//# define WIN_X 1920
//# define WIN_Y 1080
# define DIST ((int)WIN_X / tan(30 * M_PI / 180))
# define BPP 32

typedef union			u_color
{
	unsigned int		color;
	struct
	{
		unsigned char	r;
		unsigned char	g;
		unsigned char	b;
		unsigned char	a;
	}					c;
}						t_color;

typedef struct			s_v
{
	double				x;
	double				y;
	double				z;
}						t_v;

typedef struct			s_sphere
{
	char				type;
	double				radius;
	t_v					o;
	t_v					colo;
	t_v					norm;
	t_color				col;
	double				dist;
}						t_sphere;

typedef struct			s_env
{
	SDL_Window			*win;
	SDL_Surface			*surf;
	t_v					pos_lum;
	t_v					pos_cam;
	t_v					vcam;
	t_v					v2cam;
	t_v					v3cam;
	t_v					r;
	t_v					r2;
	int					nb_obj;
	int					anti_alias;
	float				flou;
	double				v1;
	double				v2;
	t_sphere			objs[6];
	t_sphere			sphere;
	t_sphere			sphere2;
	t_sphere			sphere3;
	t_sphere			plan;
	t_sphere			plan2;
}						t_env;

double					vect_norm(t_v a);
t_v						vect_mult(t_v a, double n);
t_v						vect_add(t_v a, t_v b);
double					vect_scal_prod(t_v a, t_v b);
t_v						vect_prod(t_v a, t_v b);

#endif

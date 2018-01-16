/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 18:01:28 by tjeanner          #+#    #+#             */
/*   Updated: 2017/12/13 20:51:50 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "libft.h"
# include <fcntl.h>//open
# include <sys/types.h>//read
# include <sys/uio.h>//read
# include <unistd.h>//read, write, close
# include <stdlib.h> //malloc, free
# include <stdio.h> //perror, strerror
# include <string.h> //strerror
# include "SDL.h"
# include <string.h>
# include <stdbool.h>

# define WIN_X 640
# define WIN_Y 480
# define DIST 554
# define BPP 32

typedef union		s_color
{
	unsigned int	color;
	struct
	{
		unsigned char	r;
		unsigned char	g;
		unsigned char	b;
		unsigned char	a;
	}				c;
}					t_color;

typedef struct		s_col
{
	int				r;
	int				g;
	int				b;
	int				a;
}					t_col;

typedef struct		s_v
{
	double			x;
	double			y;
	double			z;
}					t_v;

typedef struct		s_sphere
{
	double			r;
	t_v				o;
	t_col			col;
	double			dist;
}					t_sphere;

typedef struct		s_env
{
	SDL_Window		*win;
	SDL_Surface		*surf;
	t_v				plum;
	t_v				pcam;
	t_v				vcam;
	t_v				v2cam;
	t_v				v3cam;
	t_v				r;
	t_v				r2;
	int				nb;
	double			v1;
	double			v2;
	t_sphere		objs[2];
	t_sphere		sphere;
	t_sphere		sphere2;
}					t_env;

#endif

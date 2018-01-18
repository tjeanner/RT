/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 18:01:03 by tjeanner          #+#    #+#             */
/*   Updated: 2018/01/18 03:31:31 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
 **get_dist: a function that will return 0, 1 or 2 distances between a sphere and
 **the pixel. the distance(s) is written in env->v1 and env->v2
 */

int		get_dist(t_env *env, int x, int y, t_sphere obj)
{
	t_v		u1;
	t_v		r_ini;
	double		a;
	double		b;
	double		c;
	double	tmp;

	u1 = vect_mult(vect_prod(env->vcam, env->v2cam), -1);
	r_ini = env->pos_cam;
	env->r = vect_add(vect_mult(u1, (x - WIN_X / 2) / vect_norm(u1)),
			vect_mult(env->v2cam, -1 * (y - WIN_Y / 2) / vect_norm(env->v2cam)));
	u1 = vect_add(r_ini, env->r);//pos pix - vcam*dist
	r_ini = vect_add(env->r, vect_mult(env->vcam, DIST));//v cam->pix
	env->r = vect_mult(u1, 1);//pos pix - vcam*dist
	//	env->r = vect_add(r_ini, env->pos_cam);
	u1 = vect_add(env->r, vect_mult(obj.o, -1));//rso
	env->r2 = vect_mult(r_ini, 1 / vect_norm(r_ini));//v cam->pix unit
	a = vect_scal_prod(r_ini, r_ini);
	b = 2 * vect_scal_prod(r_ini, u1);
	c = vect_scal_prod(u1, u1) - obj.radius * obj.radius;
	tmp = b * b - 4 * a * c;
	if (tmp < 0)
		return (0);
	else
	{
		env->v1 = (-b + sqrt(tmp)) / (2 * a);
		env->v2 = (-b - sqrt(tmp)) / (2 * a);
	}
	return (1);
}

/*
 **get_col: a function that will return a col structure containing color
 **corresponding for desired pixel (specified by x & y)
 */

t_color		get_col(t_env *env, int x, int y)
{
	int		i;
	int		ob;
	double	res;
	t_color	col;
	t_v		norm;
//	t_v		norm2;

	i = -1;
	while (++i < env->nb_obj)
	{
		if (get_dist(env, x, y, env->objs[i]) == 1 && (env->v1 >= 0 || env->v2 >= 0))
		{
			if (env->v1 >= 0 && env->v2 >= 0)
				env->objs[i].dist = (env->v1 < env->v2) ? env->v1 : env->v2;
			else
				env->objs[i].dist = (env->v1 >= 0) ? env->v1 : env->v2;
		}
		else
			env->objs[i].dist = -1;
	}
	i = -1;
	ob = 0;
	while (++i < env->nb_obj)
	{
		if (i == 0)
			res = env->objs[i].dist;
		else
		{
			if (env->objs[i].dist > 0 && (res == -1 || res > env->objs[i].dist))
			{
				res = env->objs[i].dist;
				ob = i;
			}
		}
	}
	col.c.a = 0;
	if (res == -1)
	{
		col.c.r = 0;
		col.c.g = 0;
		col.c.b = 0;
	}
	else
	{
		norm = vect_add(env->objs[ob].o, vect_mult(vect_add(env->r, vect_mult(env->r2, env->objs[ob].dist)), -1));
		norm = vect_mult(norm, 1 / vect_norm(norm));
			col.c.r = 255 * fabs(norm.x);
			col.c.g = 255 * fabs(norm.y);
			col.c.b = 255 * fabs(norm.z);
	}
	return (col);
}

/*
 **rays: a function that call get_col for each pixel and update window surface
 */

t_color		rays(t_env *env)
{
	int		a;
	int		b;
	t_color	col;

	a = -1;
	while (++a < WIN_Y && (b = -1) == -1)
	{
		while (++b < WIN_X)
		{
			col = get_col(env, b, a);
			((int *)env->surf->pixels)[b + a * env->surf->w] = col.color;
		}
	}
	SDL_UpdateWindowSurface(env->win);
	return (col);
}

/*
 **init: initialise la sdl, malloc et rempli la structure de donnees
 */

t_env		*init()
{
	t_env	*env;

	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		if (!(env = (t_env *)malloc(sizeof(t_env) * 1)))
			return (0);
		if (!(env->win = SDL_CreateWindow("Rtv1", SDL_WINDOWPOS_CENTERED,
						SDL_WINDOWPOS_CENTERED, WIN_X, WIN_Y, SDL_WINDOW_SHOWN)))
		{
			ft_putendl("error");
			return (NULL);
		}
		else
		{
			if (!(env->surf = SDL_GetWindowSurface(env->win)))
			{
				ft_putendl("error");
				return (NULL);
			}
		}
		env->pos_cam.x = 0;
		env->pos_cam.y = 0;
		env->pos_cam.z = 0;
		env->vcam.x = 0;
		env->vcam.y = 0;
		env->vcam.z = 1;
		env->v2cam.x = 0;
		env->v2cam.y = 1;
		env->v2cam.z = 0;
		env->pos_lum.x = 0;
		env->pos_lum.y = 1;
		env->pos_lum.z = 0;
		env->sphere.o.x = 0;
		env->sphere.o.y = 0;
		env->sphere.o.z = 800;
		env->sphere.radius = 800;
		env->sphere.col.c.r = 255;
		env->sphere.col.c.g = 255;
		env->sphere.col.c.b = 255;
		env->sphere.col.c.a = 0;
		ft_memcpy(&env->objs[0], &env->sphere, sizeof(t_sphere));
		env->sphere2.o.x = 0;
		env->sphere2.o.y = 0;
		env->sphere2.o.z = 5;
		env->sphere2.radius = 100;
		env->sphere2.col.c.r = 255;
		env->sphere2.col.c.g = 0;
		env->sphere2.col.c.b = 0;
		env->sphere2.col.c.a = 0;
		ft_memcpy(&env->objs[1], &env->sphere2, sizeof(t_sphere));
		env->nb_obj = 1;
		return (env);
	}
	ft_putendl("error in init");
	return (NULL);
}

int			main(int ac, char **av)
{
	t_env		*env;
	int			fin;
	SDL_Event	event;

	(void)ac;
	(void)av;
	if (!(env = init()))
	{
		ft_putendl("error in init");
		return (0);
	}
	fin = 0;
	//	event.type = SDL_USEREVENT;
	while (!fin)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			{
				ft_putendl("yolo");
				fin = 1;
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_w)
			{
				env->pos_cam.x += env->vcam.x * 10;
				env->pos_cam.y += env->vcam.y * 10;
				env->pos_cam.z += env->vcam.z * 10;
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
			{
				env->pos_cam.x -= env->vcam.x * 10;
				env->pos_cam.y -= env->vcam.y * 10;
				env->pos_cam.z -= env->vcam.z * 10;
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a)
			{
				env->v3cam = vect_prod(env->vcam, env->v2cam);
				env->pos_cam.x += env->v3cam.x * 10;
				env->pos_cam.y += env->v3cam.y * 10;
				env->pos_cam.z += env->v3cam.z * 10;
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d)
			{
				env->v3cam = vect_prod(env->vcam, env->v2cam);
				env->pos_cam.x -= env->v3cam.x * 10;
				env->pos_cam.y -= env->v3cam.y * 10;
				env->pos_cam.z -= env->v3cam.z * 10;
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q)
			{
				env->vcam.x -= 0.3;
				env->vcam = vect_mult(env->vcam, 1 / vect_norm(env->vcam));
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_e)
			{
				env->vcam.x += 0.3;
				env->vcam = vect_mult(env->vcam, 1 / vect_norm(env->vcam));
			}
		}
		rays(env);
	}
	//	SDL_DestroyTexture(env->textu);
	//	SDL_DestroyRenderer(env->render);
	SDL_DestroyWindow(env->win);
	free(env);
	SDL_Quit();
	return (1);
}

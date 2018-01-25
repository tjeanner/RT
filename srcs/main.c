/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 18:01:03 by tjeanner          #+#    #+#             */
/*   Updated: 2018/01/25 01:18:29 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			get_dist_cone(t_env *env, t_obj obj)
{
	t_v		ra0;
	t_v		s;
	t_v		va;
	double	h;
	double	hh;
	double	vs;
	double	w;
	double	a;
	double	b;
	double	c;
	double	tmp;

	s = vect_add(obj.o, vect_mult(obj.norm, -1.0));
	s = vect_mult(s, 1.0 / vect_norm(s));
	vs = vect_scal_prod(env->r2, s);
	hh = vect_norm(vect_add(obj.o, vect_mult(obj.norm, -1.0)));
	hh = obj.radius * obj.radius / (hh * hh);
	h = vect_scal_prod(s, vect_add(env->r2, vect_mult(obj.norm, -1.0)));
	va = vect_prod(vect_prod(s, env->r2), s);
	w = 50.0 - vect_scal_prod(s, vect_add(env->r, vect_mult(obj.norm, -1.0)));
	ra0 = vect_prod(vect_prod(s, vect_add(env->r, vect_mult(obj.norm, -1.0))), s);
	a = vect_scal_prod(va, va) - vs * vs * hh;
	b = 2 * vect_scal_prod(ra0, va) + 2 * w * vs * hh;
	c = vect_scal_prod(ra0, ra0) - w * w * hh;
	tmp = b * b - 4 * a * c;
	if (tmp < 0)//case where there's no solution for the equation, so no collision
		return (0);
	else//case where there's one solution (if tmp == 0) or 2 of them (tmp > 0)
	{
		env->v1 = (-b + sqrt(tmp)) / (2 * a);//if tmp == 0
		env->v2 = (-b - sqrt(tmp)) / (2 * a);//env->v2 will be the same as env->v1
	}
	return (1);
}

int			get_dist_tube(t_env *env, t_obj obj)
{
	t_v		va;
	t_v		ra0;
	t_v		s;
	double	a;
	double	b;
	double	c;
	double	tmp;

	s = vect_add(obj.o, vect_mult(obj.norm, -1.0));
	s = vect_mult(s, 1.0 / vect_norm(s));
	va = vect_prod(vect_prod(s, env->r2), s);//Va
	ra0 = vect_prod(vect_prod(s, vect_add(env->r, vect_mult(obj.norm, -1.0))), s);//Ra0
	a = vect_scal_prod(va, va);
	b = 2 * vect_scal_prod(va, ra0);
	c = vect_scal_prod(ra0, ra0) - obj.radius * obj.radius;
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

int			get_dist_plan(t_env *env, t_obj obj)
{
	env->v1 = -1;
	env->v2 = vect_scal_prod(obj.norm, vect_add(obj.o, vect_mult(env->r, -1))) / vect_scal_prod(obj.norm, env->r2);
	return (1);
}

/*
**get_dist: a function that will return 0, 1 or 2 distances between a sphere and
**the pixel. the distance(s) is written in env->v1 and env->v2
*/

int			get_dist_sphere(t_env *env, t_obj obj)
{
	t_v		pixel_2_sphere_center;
	double	a;
	double	b;
	double	c;
	double	tmp;

	pixel_2_sphere_center = vect_add(env->r, vect_mult(obj.o, -1));
	a = vect_scal_prod(env->r2, env->r2);
	b = 2 * vect_scal_prod(env->r2, pixel_2_sphere_center);
	c = vect_scal_prod(pixel_2_sphere_center, pixel_2_sphere_center) - obj.radius * obj.radius;
	tmp = b * b - 4 * a * c;
	if (tmp < 0)//case where there's no solution for the equation, so no collision
		return (0);
	else//case where there's one solution (if tmp == 0) or 2 of them (tmp > 0)
	{
		env->v1 = (-b + sqrt(tmp)) / (2 * a);//if tmp == 0
		env->v2 = (-b - sqrt(tmp)) / (2 * a);//env->v2 will be the same as env->v1
	}
	return (1);
}

/*
**get_col: a function that will return a col structure containing color
**corresponding for desired pixel (specified by x & y)
*/

int		init_ray(t_env *env, float x, float y)
{
	t_v		center_screen_2_pix;
	t_v		cam_2_center_screen;
	t_v		cam_2_pixel;
	t_v		cam_2_pixel_norm;

	env->cam.v3cam = vect_mult(vect_prod(env->cam.vcam, env->cam.v2cam), -1);
	cam_2_center_screen = vect_mult(env->cam.vcam, DIST);
	center_screen_2_pix = vect_add(vect_mult(env->cam.v3cam, (x - WIN_X / 2) / vect_norm(env->cam.v3cam)),
			vect_mult(env->cam.v2cam, -1 * (y - WIN_Y / 2) / vect_norm(env->cam.v2cam)));
	cam_2_pixel = vect_add(cam_2_center_screen, center_screen_2_pix);
	cam_2_pixel_norm = vect_mult(cam_2_pixel, 1 / vect_norm(cam_2_pixel));
//	env->r = vect_add(env->cam.pos_cam, cam_2_pixel);
	env->r = env->cam.pos_cam;
	env->r2 = cam_2_pixel_norm;
	return (1);
}

t_color		get_col(t_env *env, float x, float y)
{
	int		i;//index that run through all objects
	int		ob;//to store the value of the index i when we find the object
	double	res;//to store the value of the distance when we find the object
	t_color	col;
	t_v		norm;
	t_v		pos_collision;
	t_v		lum_2_collision;

	i = -1;
	while (++i < env->nb_obj && (env->objs[i].dist = -1) == -1)//we search a collision between the ray and each objects
		if (env->objs[i].type == 's' && get_dist_sphere(env,
					env->objs[i]) == 1 && (env->v1 >= 0 || env->v2 >= 0))
			if (env->v1 >= 0 && env->v2 >= 0)
				env->objs[i].dist = (env->v1 < env->v2) ? env->v1 : env->v2;
			else
				env->objs[i].dist = (env->v1 >= 0) ? env->v1 : env->v2;
		else if (env->objs[i].type == 'p' && get_dist_plan(env,
					env->objs[i]) == 1 && (env->v1 >= 0 || env->v2 >= 0))
			if (env->v1 >= 0 && env->v2 >= 0)
				env->objs[i].dist = (env->v1 < env->v2) ? env->v1 : env->v2;
			else
				env->objs[i].dist = (env->v1 >= 0) ? env->v1 : env->v2;
		else if (env->objs[i].type == 't' && get_dist_tube(env,
					env->objs[i]) == 1 && (env->v1 >= 0 || env->v2 >= 0))
			if (env->v1 >= 0 && env->v2 >= 0)
				env->objs[i].dist = (env->v1 < env->v2) ? env->v1 : env->v2;
			else
				env->objs[i].dist = (env->v1 >= 0) ? env->v1 : env->v2;
		else if (env->objs[i].type == 'c' && get_dist_cone(env,
					env->objs[i]) == 1 && (env->v1 >= 0 || env->v2 >= 0))
			if (env->v1 >= 0 && env->v2 >= 0)
				env->objs[i].dist = (env->v1 < env->v2) ? env->v1 : env->v2;
			else
				env->objs[i].dist = (env->v1 >= 0) ? env->v1 : env->v2;
		else
			env->objs[i].dist = -1;
	i = -1;
	ob = 0;
	while (++i < env->nb_obj)//we select the shortest distance in all the one we have
		if (i == 0 || (env->objs[i].dist > 0 && (res == -1 || res > env->objs[i].dist) && (ob = i) == i))
			res = env->objs[i].dist;
	col.c.a = 0;
	if (res == -1)//there has been no collision with any object
		set_black(&col);
	else
	{
	//	(void)x;
	//	(void)y;
		pos_collision = vect_add(env->r, vect_mult(env->r2, env->objs[ob].dist));//pos toucher
		norm = vect_add(pos_collision, vect_mult(env->objs[ob].o, -1.0));
		norm = vect_mult(norm, 1 / vect_norm(norm));//vect norm a toucher
		if (env->objs[ob].type != 's')
			norm = env->objs[ob].norm;
		lum_2_collision = vect_add(env->pos_lum, vect_mult(pos_collision, -1.0));
		lum_2_collision = vect_mult(lum_2_collision, 1 / vect_norm(lum_2_collision));
	//	res = vect_scal_prod(env->pos_lum, vect_mult(pos_collision, -1.0));
		res = vect_scal_prod(env->objs[ob].norm, lum_2_collision);
		col.c.r = 255 * fabs(norm.x);
		col.c.g = 255 * fabs(norm.y);
		col.c.b = 255 * fabs(norm.z);
		if (env->objs[ob].type == 'p')
		{
			col.c.b = env->objs[ob].col.c.b * res / 1;
			col.c.g = env->objs[ob].col.c.g * res / 1;
			col.c.r = env->objs[ob].col.c.r * res / 1;
		}
		else if (env->objs[ob].type == 's')
		{
			res = vect_scal_prod(norm, lum_2_collision);
			col.c.b = env->objs[ob].col.c.b * res / 1;
			col.c.g = env->objs[ob].col.c.g * res / 1;
			col.c.r = env->objs[ob].col.c.r * res / 1;
			env->r2 = lum_2_collision;
			env->r = pos_collision;
			env->v1 = 0;
			env->v2 = 0;
			if (get_dist_sphere(env, env->objs[ob]) == 1 && (env->v1 > 1 || env->v2 > 1))
				set_black(&col);
			init_ray(env, x, y);
		}
	}
	return (col);
}

/*
**rays: a function that call get_col for each pixel and update window surface
*/

int			rays(t_env *env)
{
	float	a;//go through each row
	float	b;//go through each pixel in eah row
	float	flou_square;//go through each pixel in eah row
	int		c;
	t_color	*col;

	flou_square = env->flou * env->flou;
	if ((env->flou >= 1 && !(col = (t_color *)malloc(sizeof(t_color) * 1))) ||
			!(col = (t_color *)malloc(sizeof(t_color) * 1 / flou_square)))
			return (0);
	a = 0;
	while ((b = 0) == 0 && a < WIN_Y)//for each row in the img
	{
			c = -1;
		while (++c > -1 && b < WIN_X && init_ray(env, b, a))//for each pixel in the row
		{
			c = ((int)1.0 / flou_square * (a - (int)a)) + ((int)1.0 /
					env->flou * (b - (int)b));//col is set with desired color for current pixel
			col[c] = get_col(env, b, a);//col is set with desired color for current pixel
			if (env->flou < 1 && c + 1 == 1 / flou_square &&
					average_color(col, env->flou))
				((int *)env->surf->pixels)[((int)((int)b + env->flou - 1) +
					((int)(a + env->flou - 1) * env->surf->w))] = col[0].color;
			c = -1;
			while (env->flou >= 1 && ++c < flou_square)
				((int *)env->surf->pixels)[(int)b + ((int)c % (int)env->flou)
		+ ((int)a + (int)c / (int)env->flou) * env->surf->w] = col[0].color;//we draw the color in the pixel
			if (((int)(10.0 * b + 10.0 * env->flou)) % 10 == 0)
			{
				b = (((int)(10.0 * a + 10.0 * env->flou)) % 10 == 0) ? b +
					env->flou : (int)b;
				a = (((int)(10.0 * a + 10.0 * env->flou)) % 10 == 0) ? (int)a
					: a + env->flou;
			}
			else
				b += env->flou;
		}
		a += (env->flou < 1) ? 1 : env->flou;
	}
	free(col);
	SDL_UpdateWindowSurface(env->win);
	return (1);
}

/*
**init: initialise sdl, malloc and fill the data struct (here: env)
*/

t_env		*init(void)
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
		return (fill_env(env));
	}
	ft_putendl("error in init");
	return (NULL);
}

int			main(int ac, char **av)
{
	t_env		*env;

	(void)ac;
	(void)av;
	if (!(env = init()))
	{
		ft_putendl("error in init");
		return (0);
	}
	env->state = 0;
	//	event.type = SDL_USEREVENT;
	while (!env->state)
	{
		events(env);
		rays(env);
	}
	//	SDL_DestroyTexture(env->textu);
	//	SDL_DestroyRenderer(env->render);
	SDL_DestroyWindow(env->win);
	free(env);
	SDL_Quit();
	return (1);
}

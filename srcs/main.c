/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 18:01:03 by tjeanner          #+#    #+#             */
/*   Updated: 2018/01/22 00:47:55 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			get_dist_cone(t_env *env, float x, float y, t_sphere obj)
{
	t_v		pos_pixel;
	t_v		center_screen_2_pix;
	t_v		cam_2_center_screen;
	t_v		cam_2_pixel;
	t_v		cam_2_pixel_norm;
//	t_v		pixel_2_sphere_center;
	t_v		ra0;
	t_v		s;
	t_v		va;
	double	h;
	double	hh;
	double	h0;
	double	vs;
	double	w;
	double	a;
	double	b;
	double	c;
	double	tmp;

	env->v3cam = vect_mult(vect_prod(env->vcam, env->v2cam), -1);
	cam_2_center_screen = vect_mult(env->vcam, DIST);
	center_screen_2_pix = vect_add(vect_mult(env->v3cam, (x - WIN_X / 2) / vect_norm(env->v3cam)),
			vect_mult(env->v2cam, -1 * (y - WIN_Y / 2) / vect_norm(env->v2cam)));
	cam_2_pixel = vect_add(cam_2_center_screen, center_screen_2_pix);
	cam_2_pixel_norm = vect_mult(cam_2_pixel, 1 / vect_norm(cam_2_pixel));
	pos_pixel = vect_add(env->pos_cam, cam_2_pixel);
//	pixel_2_sphere_center = vect_add(pos_pixel, vect_mult(obj.o, -1));
	env->r = pos_pixel;
	env->r2 = cam_2_pixel_norm;
	s = vect_add(obj.o, vect_mult(obj.norm, -1.0));
	s = vect_mult(s, 1.0 / vect_norm(s));
	h0 = vect_scal_prod(s, vect_add(pos_pixel, vect_mult(obj.norm, -1.0)));
	vs = vect_scal_prod(cam_2_pixel_norm, s);
	hh = vect_norm(vect_add(obj.o, vect_mult(obj.norm, -1.0)));
	h = vect_scal_prod(s, vect_add(cam_2_pixel_norm, vect_mult(obj.norm, -1.0)));
	va = vect_prod(vect_prod(s, cam_2_pixel_norm), s);
	w = 500.0 - h0;
	ra0 = vect_prod(vect_prod(s, vect_add(pos_pixel, vect_mult(obj.norm, -1.0))), s);
	a = vect_scal_prod(va, va) - vs * vs * obj.radius * obj.radius / (hh * hh);
	b = 2 * vect_scal_prod(ra0, va) + 2 * w * vs * obj.radius * obj.radius / (hh * hh);
	c = vect_scal_prod(ra0, ra0) - w * w * obj.radius * obj.radius / (hh * hh);
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

int			get_dist_tube(t_env *env, float x, float y, t_sphere obj)
{
	t_v		pos_pixel;
	t_v		center_screen_2_pix;
	t_v		cam_2_center_screen;
	t_v		cam_2_pixel;
	t_v		cam_2_pixel_norm;
	t_v		s;
	double	a;
	double	b;
	double	c;
	double	tmp;

	s = vect_add(obj.o, vect_mult(obj.norm, -1.0));
	s = vect_mult(s, 1.0 / vect_norm(s));
	env->v3cam = vect_mult(vect_prod(env->vcam, env->v2cam), -1);
	cam_2_center_screen = vect_mult(env->vcam, DIST);
	center_screen_2_pix = vect_add(vect_mult(env->v3cam, (x - WIN_X / 2) / vect_norm(env->v3cam)),
			vect_mult(env->v2cam, -1 * (y - WIN_Y / 2) / vect_norm(env->v2cam)));
	cam_2_pixel = vect_add(cam_2_center_screen, center_screen_2_pix);
	cam_2_pixel_norm = vect_mult(cam_2_pixel, 1 / vect_norm(cam_2_pixel));
	cam_2_center_screen = vect_prod(vect_prod(s, cam_2_pixel_norm), s);//Va
	pos_pixel = vect_add(env->pos_cam, cam_2_pixel);
	cam_2_pixel = vect_prod(vect_prod(s, vect_add(pos_pixel, vect_mult(obj.norm, -1.0))), s);//Ra0
//	pixel_2_sphere_center = vect_add(pos_pixel, vect_mult(obj.o, -1));
	env->r = pos_pixel;
	env->r2 = cam_2_pixel_norm;
	a = vect_scal_prod(cam_2_center_screen, cam_2_center_screen);
	b = 2 * vect_scal_prod(cam_2_center_screen, cam_2_pixel);
	c = vect_scal_prod(cam_2_pixel, cam_2_pixel) - obj.radius * obj.radius;
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

int			get_dist_plan(t_env *env, float x, float y, t_sphere obj)
{
	t_v		pos_pixel;
	t_v		center_screen_2_pix;
	t_v		cam_2_center_screen;
	t_v		cam_2_pixel;
	t_v		cam_2_pixel_norm;

	env->v3cam = vect_mult(vect_prod(env->vcam, env->v2cam), -1);
	cam_2_center_screen = vect_mult(env->vcam, DIST);
	center_screen_2_pix = vect_add(vect_mult(env->v3cam, (x - WIN_X / 2) / vect_norm(env->v3cam)),
			vect_mult(env->v2cam, -1 * (y - WIN_Y / 2) / vect_norm(env->v2cam)));
	cam_2_pixel = vect_add(cam_2_center_screen, center_screen_2_pix);
	cam_2_pixel_norm = vect_mult(cam_2_pixel, 1 / vect_norm(cam_2_pixel));
	pos_pixel = vect_add(env->pos_cam, cam_2_pixel);
	env->v1 = -1;
	env->v2 = vect_scal_prod(obj.norm, vect_add(obj.o, vect_mult(pos_pixel, -1))) / vect_scal_prod(obj.norm, cam_2_pixel_norm);
	return (1);
}

/*
**get_dist: a function that will return 0, 1 or 2 distances between a sphere and
**the pixel. the distance(s) is written in env->v1 and env->v2
*/

int			get_dist_sphere(t_env *env, float x, float y, t_sphere obj)
{
	t_v		pos_pixel;
	t_v		center_screen_2_pix;
	t_v		cam_2_center_screen;
	t_v		cam_2_pixel;
	t_v		cam_2_pixel_norm;
	t_v		pixel_2_sphere_center;
	double	a;
	double	b;
	double	c;
	double	tmp;

//env->v3cam is the "full right" camera vector (vcam is "full forward" and v2cam is "full up")
	env->v3cam = vect_mult(vect_prod(env->vcam, env->v2cam), -1);
//cam_2_center_screen is the vector from te camera to the center of the screen
	cam_2_center_screen = vect_mult(env->vcam, DIST);
//center_screen_2_pix is the vector from the center of the screen to the current pixel
	center_screen_2_pix = vect_add(vect_mult(env->v3cam, (x - WIN_X / 2) / vect_norm(env->v3cam)),
			vect_mult(env->v2cam, -1 * (y - WIN_Y / 2) / vect_norm(env->v2cam)));
//cam_2_pixel is the vector from the camera to the current pixel
	cam_2_pixel = vect_add(cam_2_center_screen, center_screen_2_pix);
//cam_2_pixel is the vector from the camera to the current pixel normalized so it's length is 1
	cam_2_pixel_norm = vect_mult(cam_2_pixel, 1 / vect_norm(cam_2_pixel));
//pos_pixel is the postion in space of the current pixel
	pos_pixel = vect_add(env->pos_cam, cam_2_pixel);
//pixel_2_sphere_center is the vector from the current pixel to the center of the sphere
	pixel_2_sphere_center = vect_add(pos_pixel, vect_mult(obj.o, -1));
	env->r = pos_pixel;
	env->r2 = cam_2_pixel_norm;
	a = vect_scal_prod(cam_2_pixel_norm, cam_2_pixel_norm);
	b = 2 * vect_scal_prod(cam_2_pixel_norm, pixel_2_sphere_center);
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
	while (++i < env->nb_obj)//we search a collision between the ray and each objects
	{
		env->objs[i].dist = -1;
		if (env->objs[i].type == 's' && get_dist_sphere(env, x, y, env->objs[i]) == 1 && (env->v1 >= 0 || env->v2 >= 0))
		{
			if (env->v1 >= 0 && env->v2 >= 0)
				env->objs[i].dist = (env->v1 < env->v2) ? env->v1 : env->v2;
			else
				env->objs[i].dist = (env->v1 >= 0) ? env->v1 : env->v2;
		}
		else if (env->objs[i].type == 'p' && get_dist_plan(env, x, y, env->objs[i]) == 1 && (env->v1 >= 0 || env->v2 >= 0))
		{
			if (env->v1 >= 0 && env->v2 >= 0)
				env->objs[i].dist = (env->v1 < env->v2) ? env->v1 : env->v2;
			else
				env->objs[i].dist = (env->v1 >= 0) ? env->v1 : env->v2;
		}
		else if (env->objs[i].type == 't' && get_dist_tube(env, x, y, env->objs[i]) == 1 && (env->v1 >= 0 || env->v2 >= 0))
		{
			if (env->v1 >= 0 && env->v2 >= 0)
				env->objs[i].dist = (env->v1 < env->v2) ? env->v1 : env->v2;
			else
				env->objs[i].dist = (env->v1 >= 0) ? env->v1 : env->v2;
		}
		else if (env->objs[i].type == 'c' && get_dist_cone(env, x, y, env->objs[i]) == 1 && (env->v1 >= 0 || env->v2 >= 0))
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
	while (++i < env->nb_obj)//we select the shortest distance in all the one we have
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
	if (res == -1)//there has been no collision with any object
	{
		col.c.r = 0;
		col.c.g = 0;
		col.c.b = 0;
	}
	else
	{
		pos_collision = vect_add(env->r, vect_mult(env->r2, env->objs[ob].dist));//pos toucher
		norm = vect_add(env->objs[ob].o, vect_mult(pos_collision, -1.0));
		norm = vect_mult(norm, 1 / vect_norm(norm));//vect norm a toucher
		if (env->objs[ob].type != 's')
			norm = env->objs[ob].colo;
		lum_2_collision = vect_add(env->pos_lum, vect_mult(pos_collision, -1.0));
	//	lum_2_collision = vect_mult(vect_add(env->pos_lum, vect_mult(pos_collision, -1.0)), 1.0);
	//	res = 90.0 - acos(3.1415 * vect_scal_prod(norm, lum_2_collision) / (180.0 * vect_norm(norm) * vect_norm(lum_2_collision))) / 3.1415 * 180.0;
		res = 90.0 - acos(3.1415 * (norm.x * lum_2_collision.x + norm.y * lum_2_collision.y + norm.z * lum_2_collision.z) / (180.0 * vect_norm(norm) * vect_norm(lum_2_collision))) / 3.1415 * 180.0;
		col.c.r = 1 / res;
		col.c.g = 1 / res;
		col.c.b = 1 / res;
		col.c.r = 255 * fabs(norm.x);
		col.c.g = 255 * fabs(norm.y);
		col.c.b = 255 * fabs(norm.z);
	}
	return (col);
}

/*
**rays: a function that call get_col for each pixel and update window surface
*/

int		rays(t_env *env)
{
	float	a;//go through each row
	float	b;//go through each pixel in eah row
	int		c;
	t_color	*col;
	t_v		colo;

	if ((a = 0) == 0 && env->flou >= 1)
	{
		if (!(col = (t_color *)malloc(sizeof(t_color) * 1)))
			return (0);
	}
	else
		if (!(col = (t_color *)malloc(sizeof(t_color) * 1 / (env->flou * env->flou))))
			return (0);
	while ((b = 0) == 0 && a < WIN_Y)//for each row in the img
	{
		while (b < WIN_X)//for each pixel in the row
		{
			c = ((int)1.0 / (env->flou * env->flou) * (a - (int)a)) + ((int)1.0 / env->flou * (b - (int)b));//col is set with desired color for current pixel
			col[c] = get_col(env, b + env->flou / 2.0, a + env->flou / 2.0);//col is set with desired color for current pixel
			if (env->flou < 1 && c + 1 == 1 / (env->flou * env->flou) && (c = 0) == 0)
			{
				colo.x = col[0].c.r * env->flou * env->flou;
				colo.y = col[0].c.g * env->flou * env->flou;
				colo.z = col[0].c.b * env->flou * env->flou;
				while (++c < 1.0 / (env->flou * env->flou))
				{
					colo.x += col[c].c.r * env->flou * env->flou;
					colo.y += col[c].c.g * env->flou * env->flou;
					colo.z += col[c].c.b * env->flou * env->flou;
				}
				col[0].c.r = colo.x;
				col[0].c.g = colo.y;
				col[0].c.b = colo.z;
				c = ((int)b + env->flou - 1) + ((int)(a + env->flou - 1) * env->surf->w);
				((int *)env->surf->pixels)[c] = col[0].color;//we draw the color in the pixel
			}
			c = 0;
			while (env->flou >= 1 && c < env->flou * env->flou)
			{
				((int *)env->surf->pixels)[(int)b + ((int)c % (int)env->flou) + ((int)a + (int)c / (int)env->flou) * env->surf->w] = col[0].color;//we draw the color in the pixel
				c++;
			}
			if (((int)(10.0 * b + 10.0 * env->flou)) % 10 == 0)
			{
				b = (((int)(10.0 * a + 10.0 * env->flou)) % 10 == 0) ? b + env->flou : (int)b;
				a = (((int)(10.0 * a + 10.0 * env->flou)) % 10 == 0) ? (int)a : a + env->flou;
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
				env->pos_cam.x += env->vcam.x * 100;
				env->pos_cam.y += env->vcam.y * 100;
				env->pos_cam.z += env->vcam.z * 100;
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
			{
				env->pos_cam.x -= env->vcam.x * 100;
				env->pos_cam.y -= env->vcam.y * 100;
				env->pos_cam.z -= env->vcam.z * 100;
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a)
			{
				env->v3cam = vect_prod(env->vcam, env->v2cam);
				env->pos_cam.x += env->v3cam.x * 100;
				env->pos_cam.y += env->v3cam.y * 100;
				env->pos_cam.z += env->v3cam.z * 100;
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d)
			{
				env->v3cam = vect_prod(env->vcam, env->v2cam);
				env->pos_cam.x -= env->v3cam.x * 100;
				env->pos_cam.y -= env->v3cam.y * 100;
				env->pos_cam.z -= env->v3cam.z * 100;
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q)
			{
				env->vcam.x -= 0.1;
				env->vcam = vect_mult(env->vcam, 1 / vect_norm(env->vcam));
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_e)
			{
				env->vcam.x += 0.1;
				env->vcam = vect_mult(env->vcam, 1 / vect_norm(env->vcam));
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r)
			{
				env->pos_lum.y += 100;
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_f)
			{
				env->pos_lum.y -= 100;
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_t)
			{
				env->flou = (env->flou * 16 > WIN_Y) ? env->flou: env->flou * 2;
				ft_putnbr(env->flou * 1000000000);
				ft_putchar('\n');
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_g)
			{
				env->flou = env->flou / 2;
				ft_putnbr(env->flou * 1000000000);
				ft_putchar('\n');
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

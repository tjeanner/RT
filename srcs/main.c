/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 18:01:03 by tjeanner          #+#    #+#             */
/*   Updated: 2018/01/21 02:54:21 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			get_dist_tube(t_env *env, float x, float y, t_sphere obj)
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

	env->v3cam = vect_mult(vect_prod(env->vcam, env->v2cam), -1);
	cam_2_center_screen = vect_mult(env->vcam, DIST);
	center_screen_2_pix = vect_add(vect_mult(env->v3cam, (x - WIN_X / 2) / vect_norm(env->v3cam)),
			vect_mult(env->v2cam, -1 * (y - WIN_Y / 2) / vect_norm(env->v2cam)));
	cam_2_pixel = vect_add(cam_2_center_screen, center_screen_2_pix);
	cam_2_pixel_norm = vect_mult(cam_2_pixel, 1 / vect_norm(cam_2_pixel));
	pos_pixel = vect_add(env->pos_cam, cam_2_pixel);
	pixel_2_sphere_center = vect_add(pos_pixel, vect_mult(obj.o, -1));
	env->r = pos_pixel;
	env->r2 = cam_2_pixel_norm;
	a = vect_scal_prod(cam_2_pixel_norm, cam_2_pixel_norm);
	b = 2 * vect_scal_prod(cam_2_pixel_norm, pixel_2_sphere_center);
	c = vect_scal_prod(pixel_2_sphere_center, pixel_2_sphere_center) - obj.radius * obj.radius;
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
		else if (env->objs[i].type == 't' && get_dist_plan(env, x, y, env->objs[i]) == 1 && (env->v1 >= 0 || env->v2 >= 0))
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
	int		r;
	int		g;
	int		b0;
	t_color	*col;

	if (env->flou >= 1)
	{
		if (!(col = (t_color *)malloc(sizeof(t_color) * 1)))
			return (0);
	}
	else
		if (!(col = (t_color *)malloc(sizeof(t_color) * 1 / (env->flou * env->flou))))
			return (0);
	a = 0;
	while (a < WIN_Y)//for each row in the img
	{
		b = 0;
		while (b < WIN_X)//for each pixel in the row
		{
			if (env->flou >= 1)
				col[0] = get_col(env, b, a);//col is set with desired color for current pixel
			else
			{
				c = ((int)1.0 / (env->flou * env->flou) * (a - (int)a)) + ((int)1.0 / env->flou * (b - (int)b));//col is set with desired color for current pixel
				col[c] = get_col(env, b + env->flou / 2.0, a + env->flou / 2.0);//col is set with desired color for current pixel
			}
			if (env->flou < 1 && c + 1 == 1 / (env->flou * env->flou))
			{
				c = 1;
				r = col[0].c.r;
				g = col[0].c.g;
				b0 = col[0].c.b;
				while (c < 1.0 / (env->flou * env->flou))
				{
					r += col[c].c.r;
					g += col[c].c.g;
					b0 += col[c].c.b;
					c++;
				}
				r = r * env->flou * env->flou;
				g = g * env->flou * env->flou;
				b0 = b0 * env->flou * env->flou;
//				d /= 1 / (env->flou * env->flou);
				c = ((int)b + env->flou - 1) + ((int)(a + env->flou - 1) * env->surf->w);
				col[0].c.g = g;
				col[0].c.r = r;
				col[0].c.b = b0;
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
	//		b = (((int)(10.0 * b + 10.0 * env->flou)) % 10 == 0 && !(((int)(10.0 * a + 10.0 * env->flou)) % 10 == 0)) ? (int)b - 1 : b + env->flou;
//			a = (((int)(10.0 * b + 10.0 * env->flou)) % 10 == 0) ? a + env->flou : a;
		}
		a += (env->flou < 1) ? 1 : env->flou;
	}
	if (env->flou == 0.25)
		ft_putendl("salut''''''''''''''''''''''''''''''''''''''''");
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
		env->flou = 2;
		env->pos_cam.x = 0;
		env->pos_cam.y = 0;
		env->pos_cam.z = -1000;
		env->vcam.x = 0;
		env->vcam.y = 0;
		env->vcam.z = 1;
		env->v2cam.x = 0;
		env->v2cam.y = 1;
		env->v2cam.z = 0;
		env->pos_lum.x = 0;
		env->pos_lum.y = 1000;
		env->pos_lum.z = -554;
		env->sphere.type = 's';
		env->sphere.o.x = 0;
		env->sphere.o.y = 0;
		env->sphere.o.z = 800;
		env->sphere.radius = 800;
		env->sphere.col.c.r = 255;
		env->sphere.col.c.g = 255;
		env->sphere.col.c.b = 255;
		env->sphere.col.c.a = 0;
		ft_memcpy(&env->objs[0], &env->sphere, sizeof(t_sphere));
		env->sphere2.type = 's';
		env->sphere2.o.x = 0;
		env->sphere2.o.y = 0;
		env->sphere2.o.z = 50;
		env->sphere2.radius = 300;
		env->sphere2.col.c.r = 255;
		env->sphere2.col.c.g = 0;
		env->sphere2.col.c.b = 0;
		env->sphere2.col.c.a = 0;
		ft_memcpy(&env->objs[1], &env->sphere2, sizeof(t_sphere));
		env->sphere3.type = 's';
		env->sphere3.o.x = 0;
		env->sphere3.o.y = -300;
		env->sphere3.o.z = 200;
		env->sphere3.radius = 250;
		env->sphere3.col.c.r = 0;
		env->sphere3.col.c.g = 255;
		env->sphere3.col.c.b = 0;
		env->sphere3.col.c.a = 0;
		ft_memcpy(&env->objs[2], &env->sphere3, sizeof(t_sphere));
		env->plan.type = 'p';
		env->plan.o.x = 2000;
		env->plan.o.y = 0;
		env->plan.o.z = 0;
		env->plan.colo.x = -1;
		env->plan.colo.y = 0;
		env->plan.colo.z = 0;
		env->plan.norm.x = -1;
		env->plan.norm.y = 0;
		env->plan.norm.z = 0;
		ft_memcpy(&env->objs[3], &env->plan, sizeof(t_sphere));
		env->plan2.type = 'p';
		env->plan2.o.x = 0;
		env->plan2.o.y = 0;
		env->plan2.o.z = 1500;
		env->plan2.colo.x = 0;
		env->plan2.colo.y = 1;
		env->plan2.colo.z = 1;
		env->plan2.norm.x = 0;
		env->plan2.norm.y = 1;
		env->plan2.norm.z = 1;
		ft_memcpy(&env->objs[4], &env->plan2, sizeof(t_sphere));
		env->sphere3.type = 't';
		env->sphere3.o.x = 0;
		env->sphere3.o.y = -500;
		env->sphere3.o.z = 200;
		env->sphere3.radius = 50;
		env->sphere3.norm.x = -1;
		env->sphere3.norm.y = 0;
		env->sphere3.norm.z = 0;
		env->sphere3.col.c.r = 0;
		env->sphere3.col.c.g = 255;
		env->sphere3.col.c.b = 0;
		env->sphere3.col.c.a = 0;
		ft_memcpy(&env->objs[5], &env->sphere3, sizeof(t_sphere));
		env->plan.type = 'p';
		env->nb_obj = 5;
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
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_g)
			{
				env->flou = (env->flou == 0.25) ? 0.25 : env->flou / 2;
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

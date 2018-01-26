/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 18:01:03 by tjeanner          #+#    #+#             */
/*   Updated: 2018/01/26 03:22:52 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


int			init_ray(t_env *env, float x, float y)
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
	//	init_rays.r = vect_add(env->cam.pos_cam, cam_2_pixel);
	env->init_rays.r = env->cam.pos_cam;
	env->init_rays.r2 = cam_2_pixel_norm;
	return (1);
}

/*
 **get_col: a function that will return a col structure containing color
 **corresponding for desired pixel (specified by x & y)
 */

t_color		get_col(t_env *env)
{
	int		i;//index that run through all objects
	int		ob;//to store the value of the index i when we find the object
	double	res;//to store the value of the distance when we find the object
	t_color	col;
	t_v		norm;
	t_v		pos_collision;
	t_v		collision_2_lum;

	i = -1;
	while (++i < env->nb_obj && (env->objs[i].dist = -1) == -1)//we search a collision between the ray and each objects
		if (env->col_fcts[ft_strchr(FCTS, env->objs[i].type) - FCTS](&env->init_rays,
					env->objs[i]) == 1 && (env->init_rays.v1 >= 0 || env->init_rays.v2 >= 0))
			if (env->init_rays.v1 >= 0 && env->init_rays.v2 >= 0)
				env->objs[i].dist = (env->init_rays.v1 < env->init_rays.v2) ? env->init_rays.v1 : env->init_rays.v2;
			else
				env->objs[i].dist = (env->init_rays.v1 >= 0) ? env->init_rays.v1 : env->init_rays.v2;
		else
			env->objs[i].dist = -1;
	i = -1;
	while (++i < env->nb_obj)//we select the shortest distance in all the one we have
	{
		if ((i == 0 || (env->objs[i].dist > 0 && (res == -1 || res > env->objs[i].dist))))
		{
			res = env->objs[i].dist;
			ob = i;
		}
	}
	if ((col.c.a = 0) != 0 || env->objs[ob].dist < 0)//there has been no collision with any object
		set_black(&col);
	else
	{
		pos_collision = vect_add(env->init_rays.r, vect_mult(env->init_rays.r2, env->objs[ob].dist));//pos toucher
		collision_2_lum = vect_add(env->lum.pos_lum, vect_mult(pos_collision, -1.0));
		collision_2_lum = vect_mult(collision_2_lum, 1 / vect_norm(collision_2_lum));
		env->init_rays.r = pos_collision;
//		ft_memcpy(((void *)&env->init_rays.r), ((void *)&pos_collision), sizeof(t_v));
		env->init_rays.r2 = collision_2_lum;
//		ft_memcpy(((void *)&env->init_rays.r2), ((void *)&collision_2_lum), sizeof(t_v));
		i = -1;
	//	while (env->objs[ob].type == 's' && ++i < env->nb_obj)//we search an object between the collision and the light source
		while (++i < env->nb_obj)//we search an object between the collision and the light source
		{
			env->init_rays.v1 = -1;
			env->init_rays.v2 = -1;
//			if (get_dist_sphere(&env->init_rays, env->objs[i]) == 1 && ((env->init_rays.v1 > 1 && env->init_rays.v1 < vect_norm(collision_2_lum)) || (env->init_rays.v2 > 1 && env->init_rays.v2 < vect_norm(collision_2_lum))))
			if (get_dist_sphere(&env->init_rays, env->objs[i]) == 1 && (env->init_rays.v1 > 1 || env->init_rays.v2 > 1))
		//	if (env->col_fcts[ft_strchr(FCTS, env->objs[i].type) - FCTS](&env->init_rays,
		//			env->objs[i]) == 1 && (env->init_rays.v1 > 1 || env->init_rays.v2 > 1))
		//	if (env->col_fcts[ft_strchr(FCTS, env->objs[i].type) - FCTS](&env->init_rays, env->objs[i]) == 1 && (env->init_rays.v1 > 1 || env->init_rays.v2 > 1))
//			if (env->col_fcts[ft_strchr(FCTS, env->objs[ob].type) - FCTS](&env->init_rays,
//				env->objs[ob]) == 1 && ((env->init_rays.v1 > 1 && env->init_rays.v1
//			< vect_norm(collision_2_lum)) || (env->init_rays.v2 > 1 &&
//			env->init_rays.v2 < vect_norm(collision_2_lum))))
			{
				set_black(&col);
				return (col);
			}
		}
		if (env->objs[ob].type == 's')
		{
			norm = vect_add(pos_collision, vect_mult(env->objs[ob].o, -1.0));
			norm = vect_mult(norm, 1 / vect_norm(norm));//vect norm a toucher
			res = vect_scal_prod(norm, collision_2_lum);
			col = mult_color(env->objs[ob].col, res);
		}
		else if (env->objs[ob].type == 'p')
		{
			res = vect_scal_prod(env->objs[ob].norm, collision_2_lum);
			col = mult_color(env->objs[ob].col, res);
		}
		else
		{
			col.c.b = env->objs[ob].col.c.b;
			col.c.g = env->objs[ob].col.c.g;
			col.c.r = env->objs[ob].col.c.r;
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
		while (++c > -1 && b < WIN_X && init_ray(env, b, a))//for each pixel in the row
		{
			c = ((int)1.0 / flou_square * (a - (int)a)) + ((int)1.0 /
					env->flou * (b - (int)b));//col is set with desired color for current pixel
			col[c] = get_col(env);//col is set with desired color for current pixel
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
		env->col_fcts[0] = get_dist_sphere;
		env->col_fcts[1] = get_dist_plan;
		env->col_fcts[2] = get_dist_tube;
		env->col_fcts[3] = get_dist_cone;
		return (fill_env(env));
	}
	ft_putendl("error in init");
	return (NULL);
}

int			main(int ac, char **av)
{
	t_env		*env;

	if (!(env = init()))
	{
		ft_putendl("error in init");
		return (0);
	}
	if (ac == 2)
		init_scene(env, av[1]);
	env->state = 0;
	//	event.type = SDL_USEREVENT;
	while (!env->state)
	{
		events(env);
	}
	//	SDL_DestroyTexture(env->textu);
	//	SDL_DestroyRenderer(env->render);
	SDL_DestroyWindow(env->win);
	free(env);
	SDL_Quit();
	return (1);
}

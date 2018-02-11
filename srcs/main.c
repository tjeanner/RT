/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 18:01:03 by tjeanner          #+#    #+#             */
/*   Updated: 2018/02/11 05:26:15 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


int			init_ray(t_env *env, float x, float y)
{
	t_v		center_screen_2_pix;
	t_v		cam_2_center_screen;
	t_v		cam_2_pixel;
	t_v		cam_2_pixel_norm;

	env->cams[env->curr_cam].v3cam = vect_mult(vect_prod(
		env->cams[env->curr_cam].vcam, env->cams[env->curr_cam].v2cam), -1.0);
	cam_2_center_screen = vect_mult(env->cams[env->curr_cam].vcam, DIST);
	center_screen_2_pix = vect_add(vect_mult(env->cams[env->curr_cam].v3cam,
	(x - WIN_X / 2.0) / vect_norm(env->cams[env->curr_cam].v3cam)),
	vect_mult(env->cams[env->curr_cam].v2cam, -1.0 * (y - WIN_Y / 2.0) /
		vect_norm(env->cams[env->curr_cam].v2cam)));
	cam_2_pixel = vect_add(cam_2_center_screen, center_screen_2_pix);
	cam_2_pixel_norm = vect_mult(cam_2_pixel, 1.0 / vect_norm(cam_2_pixel));
	env->init_rays.r = env->cams[env->curr_cam].pos_cam;
	env->init_rays.r2 = cam_2_pixel_norm;
	return (1);
}

/*
**get_col: a function that will return a col structure containing color
**corresponding for desired pixel (specified by x & y)
*/

int			which_obj_col(t_env *env)
{
	double	res;//to store the value of the distance when we find the object
	int		i;//index that run through all objects
	int		ob;//to store the value of the index i when we find the object

	i = -1;
	res = -1.0;
	while (++i < env->nb_obj && (env->objs[i].dist = -1.0) == -1.0)//we search a collision between the ray and each objects
	{
		if (env->col_fcts[ft_strchr(FCTS, env->objs[i].type) - FCTS](
					&env->init_rays, env->objs[i]) == 1 &&
				(env->init_rays.v1 > 0.0 || env->init_rays.v2 > 0.0))
			if (env->init_rays.v1 > 0.0 && env->init_rays.v2 > 0.0)
				env->objs[i].dist = (env->init_rays.v1 < env->init_rays.v2) ?
					env->init_rays.v1 : env->init_rays.v2;
			else
				env->objs[i].dist = (env->init_rays.v1 > 0.0) ?
					env->init_rays.v1 : env->init_rays.v2;
		else
			env->objs[i].dist = -1.0;
		if ((i == 0 || (env->objs[i].dist > 0.0 &&
			(res == -1.0 || res > env->objs[i].dist))) && (ob = i) == i)
			res = env->objs[i].dist;
	}
	return (ob = (res <= 0.0) ? -1 : ob);
}

t_v			get_norm(t_env *env, int ob, t_v pos_col, t_v col_2_lum_norm)
{
	double	res;
	t_v		vect;

	if (env->objs[ob].type == 's')
		vect = vect_add(pos_col, vect_mult(env->objs[ob].o, -1.0));
	else if (env->objs[ob].type == 'p')
		vect = (vect_scal_prod(env->objs[ob].norm, col_2_lum_norm) < 0.0)
			? vect_mult(env->objs[ob].norm, -1.0) : env->objs[ob].norm;
	else if (env->objs[ob].type == 't')
	{
		vect = vect_mult(env->objs[ob].norm, 1.0 / vect_norm(env->objs[ob].norm));
		res = ((double)((vect.x * (env->init_rays.r.x - env->objs[ob].o.x) +
	vect.y * (env->init_rays.r.y - env->objs[ob].o.y) + vect.z *
	(env->init_rays.r.z - env->objs[ob].o.z)) / vect_scal_prod(vect, vect)));
		vect = vect_add(env->objs[ob].o, vect_mult(vect, res));//CC
		vect = vect_add(env->init_rays.r, vect_mult(vect, -1.0));//CCPC
	}
	else
	{
		vect = vect_add(env->objs[ob].o, vect_mult(env->objs[ob].norm, -1.0));
		vect = vect_mult(vect, 1.0 / vect_norm(vect));
		res = ((double)((vect.x * (env->init_rays.r.x - env->objs[ob].norm.x) +
	vect.y * (env->init_rays.r.y - env->objs[ob].norm.y) + vect.z *
(env->init_rays.r.z - env->objs[ob].norm.z)) / vect_scal_prod(vect, vect)));
		vect = vect_add(env->objs[ob].norm, vect_mult(vect, res));
		vect = vect_add(env->init_rays.r, vect_mult(vect, -1.0));
	}
	return (vect);
}

t_color		get_col(t_env *env)
{
	int		i;//index that run through all objects
	int		ob;//to store the value of the index i when we find the object
	int		test;//to store the value of the index i when we find the object
	double	res;//to store the value of the distance when we find the object
	t_color	col;
	t_v		tmp;
	t_v		pos_col;
	t_v		col_2_lum;
	t_v		col_2_lum_norm;

	ob = which_obj_col(env);
	if ((ob < 0 || env->objs[ob].dist <= 0.0) && (col.c.a = 0) == 0)//there has been no collision with any object
		set_black(&col);
	else if ((i = -1) == -1)
	{
		pos_col = vect_add(env->init_rays.r, vect_mult(env->init_rays.r2,
					env->objs[ob].dist));//pos toucher
		col_2_lum = vect_add(env->lums[0].pos_lum, vect_mult(pos_col, -1.0));
		col_2_lum_norm = vect_mult(col_2_lum, 1.0 / vect_norm(col_2_lum));
		tmp = vect_mult(get_norm(env, ob, pos_col, col_2_lum_norm), 0.0000);
		tmp = (env->objs[ob].type == 'p' && vect_scal_prod(pos_col, env->init_rays.r2) >= 0.0) ? vect_mult(tmp, -1.000): tmp;
		pos_col = vect_add(pos_col, tmp);
		col_2_lum = vect_add(env->lums[0].pos_lum, vect_mult(pos_col, -1.0));
		col_2_lum_norm = vect_mult(col_2_lum, 1.0 / vect_norm(col_2_lum));
		env->init_rays.r = pos_col;
		tmp = env->init_rays.r2;
		env->init_rays.r2 = col_2_lum_norm;
		while ((i = (i == ob - 1) ? i + 2 : i + 1) < env->nb_obj)//we search an object between the collision and the light source
		{
			env->init_rays.v1 = -100000.0;
			env->init_rays.v2 = -100000.0;
			if ((test = env->col_fcts[ft_strchr(FCTS, env->objs[i].type) - FCTS](
	&env->init_rays, env->objs[i])) == 1 && (((env->init_rays.v1 > 0.0000001 &&
	env->init_rays.v1 < vect_norm(col_2_lum)) || ((env->init_rays.v2 >
		0.0000001 && env->init_rays.v2 < vect_norm(col_2_lum)))) || (env->objs[ob].type == 'p' && env->objs[i].type == 'p' && ((env->init_rays.v1 < -0.0000001 &&
	env->init_rays.v1 > -2.0000) || (env->init_rays.v2 <
		-0.0000001 && env->init_rays.v2 > -2.0000)))))
			{
			//	col = mult_color(env->objs[ob].col, 0.2);
			//	col = mult_color(env->objs[ob].col, 0.0);
			res = 0.00;
			col = add_color(mult_color(env->objs[ob].col, 0.15), mult_color(env->objs[ob].col, res));
			return (col);
			}
		}
		if (test == 0)
		{
			return (get_white());
		}
		pos_col = get_norm(env, ob, pos_col, col_2_lum_norm);
		pos_col = vect_mult(pos_col, 1.0 / vect_norm(pos_col));
		res = (env->objs[ob].type == 'p' && vect_scal_prod(pos_col, tmp) >= 0.0) ? 0.0 : vect_scal_prod(pos_col, col_2_lum_norm);
		res = (res < 0.0) ? 0.0 : res * 85.000 / 100.000;
		tmp = vect_add(col_2_lum_norm, vect_mult(tmp, -1.0));
		tmp = vect_mult(tmp, 1.0 / vect_norm(tmp));
//		pos_col = vect_add(env->lums[0].pos_lum, vect_mult(env->objs[ob].o, -1.0));
//		pos_col = vect_mult(pos_col, 1.0 / vect_norm(pos_col));
//		col.c.r = fmin(255, env->objs[ob].col.c.r * 0.0 + env->objs[ob].col.c.r * res + fmax(0.0, pow(vect_scal_prod(tmp, pos_col), env->objs[ob].p)));
//		col.c.g = fmin(255, env->objs[ob].col.c.g * 0.0 + env->objs[ob].col.c.g * res + fmax(0.0, pow(vect_scal_prod(tmp, pos_col), env->objs[ob].p)));
//		col.c.b = fmin(255, env->objs[ob].col.c.b * 0.0 + env->objs[ob].col.c.b * res + fmax(0.0, pow(vect_scal_prod(tmp, pos_col), env->objs[ob].p)));
	//	if (env->objs[ob].type == 's')
	//	{
	//		col.c.r = fmin(255.0, fmax(0.0, env->lums[0].col.c.r * fmin(1.0, ((1.0 - env->portion) + env->objs[ob].col.c.r * env->portion) * pow(vect_scal_prod(tmp, pos_col), env->objs[ob].p)) + env->objs[ob].col.c.r) * res);
	//		col.c.g = fmin(255.0, fmax(0.0, env->lums[0].col.c.g * fmin(1.0, ((1.0 - env->portion) + env->objs[ob].col.c.g * env->portion) * pow(vect_scal_prod(tmp, pos_col), env->objs[ob].p)) + env->objs[ob].col.c.g) * res);
	//		col.c.b = fmin(255.0, fmax(0.0, env->lums[0].col.c.b * fmin(1.0, ((1.0 - env->portion) + env->objs[ob].col.c.b * env->portion) * pow(vect_scal_prod(tmp, pos_col), env->objs[ob].p)) + env->objs[ob].col.c.b) * res);
	//	}
	//	else
			col = add_color(mult_color(env->objs[ob].col, 0.15), mult_color(env->objs[ob].col, res));
	}
	return (col);
}
//env->portion:p, env->objs.p:n(rugosite), constante2test for ksy
/*
**rays: a function that call get_col for each pixel and update window surface
*/

void		rays(t_env *env)
{
	double	a;//go through each row
	double	b;//go through each pixel in eah row
	float	flou_square;//go through each pixel in eah row
	int		c;
	t_color	col[64];

	env = (t_env *)env;
	ft_putstr("          calculating image with ");
	if (env->flou >= 1)
	{
		ft_putnbr(1);
		ft_putstr(" ray for ");
		ft_putnbr(env->flou * env->flou);
		if (env->flou == 1)
			ft_putstr("pixel.....");
		else
			ft_putstr("pixels.....");
	}
	else
	{
		ft_putnbr(1 / (env->flou * env->flou));
		ft_putstr(" rays for ");
		ft_putnbr(1);
		ft_putstr("pixel.....");
	}
	flou_square = env->flou * env->flou;
	a = 0.0;
	while ((b = 0.0) == 0.0 && a < WIN_Y)//for each row in the img
	{
		while (b < WIN_X && init_ray(env, b + env->flou / 2, a + env->flou / 2))//for each pixel in the row
		{
			c = ((int)1.0 / flou_square * (a - (int)a)) + ((int)1.0 /
					env->flou * (b - (int)b));//col is set with desired color for current pixel
			col[c] = get_col(env);//col is set with desired color for current pixel
			if (env->flou < 1 && c + 1.0 == 1.0 / flou_square &&
					average_color(col, env->flou))
				((int *)env->surf->pixels)[((int)((int)b) +
					((int)(a) * env->surf->w))] = col[0].color;
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
		a += (env->flou < 1) ? 1.0 : env->flou;
	}
	SDL_UpdateWindowSurface(env->win);
	ft_putendl("done!");
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
						SDL_WINDOWPOS_CENTERED, WIN_X, WIN_Y, SDL_WINDOW_SHOWN)))// | SDL_WINDOW_FULLSCREEN_DESKTOP)))
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
		env->flou = 4;
		env->curr_obj = -1;
		env->curr_cam = 0;
		env->state = 0;
		env->constante2test = 1.0;
		env->portion = 0.20;
		return (env);
	}
	ft_putendl("error in init");
	return (NULL);
}

int			main(int ac, char **av)
{
	int			i;
	t_env		*env;

	if (!(env = init()))
		ft_put_err("error in init");
	if (ac != 2)
		ft_put_err("usage : ./rtv1 <scene>");
	env->file = ft_strdup(av[1]);
	init_scene(env);
	i = -1;
	while (++i < env->nb_obj)
	{
		env->objs[i].p = 40.0;//ks
	}
	env->lums[0].coef = 1.0;
	rays(env);
	while (!env->state)
	{
		events(env);
	}
	SDL_DestroyWindow(env->win);
	free(env);
	SDL_Quit();
	return (1);
}

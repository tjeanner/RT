/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 18:01:03 by tjeanner          #+#    #+#             */
/*   Updated: 2018/04/06 06:02:53 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


int			init_ray(t_env *env, double x, double y)
{
	t_v		center_screen_2_pix;
	t_v		cam_2_center_screen;
	t_v		cam_2_pixel;
	t_v		cam_2_pixel_norm;

	env->cams[env->curr_cam].v3cam = vect_inv(vect_prod(
				env->cams[env->curr_cam].vcam, env->cams[env->curr_cam].v2cam));
	cam_2_center_screen = vect_mult(env->cams[env->curr_cam].vcam, DIST);
	center_screen_2_pix = vect_add(vect_mult(env->cams[env->curr_cam].v3cam,
				(x - WIN_X / 2.0) / get_vect_norm(env->cams[env->curr_cam].v3cam)),
			vect_mult(env->cams[env->curr_cam].v2cam, (WIN_Y / 2.0 - y) /
				get_vect_norm(env->cams[env->curr_cam].v2cam)));
	cam_2_pixel = vect_add(cam_2_center_screen, center_screen_2_pix);
	cam_2_pixel_norm = vect_norm(cam_2_pixel);
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
	double	res;
	int		i;
	int		ob;

	i = -1;
	res = -1.0;
	while (++i < env->nb_obj && (env->objs[i].dist = -1.0) == -1.0)
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

t_v			get_norm(t_obj obj, t_ray init_rays, t_v pos_col)
{
	double	res;
	t_v		vect;

	if (obj.type == 's' || obj.type == 'p')
		vect = (obj.type == 'p') ? vect = obj.norm : vect_sous(pos_col, obj.o);
	else if (obj.type == 't')
	{
		vect = vect_norm(obj.norm);
	//	res = ((double)((vect.x * (init_rays.r.x - obj.o.x) +
	//					vect.y * (init_rays.r.y - obj.o.y) +
	//	vect.z * (init_rays.r.z - obj.o.z)) / vect_scal_prod(vect, vect)));
	//	vect = vect_add(obj.o, vect_mult(vect, res));//CC
	//	vect = vect_sous(init_rays.r, vect);//CCPC
		res = vect_scal_prod(init_rays.r2, vect_mult(vect, obj.dist)) + vect_scal_prod(vect_sous(init_rays.r, obj.o), vect);
		vect = vect_norm(vect_sous(vect_sous(vect_mult(vect, res), obj.o), pos_col));
		vect = vect_inv(vect);
	}
	else
	{
		vect = vect_sous(obj.o, obj.norm);
		vect = vect_norm(vect);
		res = ((double)((vect.x * (init_rays.r.x - obj.norm.x) +
			vect.y * (init_rays.r.y - obj.norm.y) + vect.z *
(init_rays.r.z - obj.norm.z)) / vect_scal_prod(vect, vect)));
		vect = vect_add(obj.norm, vect_mult(vect, res));
		vect = vect_sous(init_rays.r, vect);
		vect = vect_inv(vect);
	}
	return ((vect = vect_norm(vect)));
}

t_color		*get_lums(t_env *env, int lumcur, int ob)
{
	int		i;//index that run through all objects
	double	res;//to store the value of the distance when we find the object
	t_color	*col;
	t_v		tmp;
	t_v		tmp2;
	t_v		pos_col;
	t_v		col_2_lum;
	t_v		col_2_lum_norm;

	if (!(col = (t_color *)malloc(sizeof(t_color) * 1)))
		return (NULL);
	i = -1;
	pos_col = vect_add(env->init_rays.r, vect_mult(env->init_rays.r2,
				env->objs[ob].dist));//pos toucher
	col_2_lum = vect_sous(env->lums[lumcur].pos_lum, pos_col);
	col_2_lum_norm = vect_norm(col_2_lum);
	tmp = vect_mult(get_norm(env->objs[ob], env->init_rays, pos_col), 0.000100);
	tmp = (env->objs[ob].type == 'p' && vect_scal_prod(env->objs[ob].norm, env->init_rays.r2) > 0.0) ? vect_inv(tmp): tmp;
	pos_col = vect_add(pos_col, tmp);
//	col_2_lum = vect_sous(env->lums[lumcur].pos_lum, pos_col);
//	col_2_lum_norm = vect_norm(col_2_lum);
	tmp2 = env->init_rays.r;
	env->init_rays.r = pos_col;
	tmp = env->init_rays.r2;
	env->init_rays.r2 = col_2_lum_norm;
	while (++i < env->nb_obj)//we search an object between the collision and the light source
	{
		env->init_rays.v1 = -100000.0;
		env->init_rays.v2 = -100000.0;
		if (env->col_fcts[ft_strchr(FCTS, env->objs[i].type) - FCTS](
			&env->init_rays, env->objs[i]) == 1 && (((env->init_rays.v1 > -0.0001 &&
			env->init_rays.v1 < get_vect_norm(col_2_lum) - 0.0001) || ((env->init_rays.v2 >
			-0.0001 && env->init_rays.v2 < get_vect_norm(col_2_lum) - 0.0001)))))
		{
			//	col = mult_color(env->objs[ob].col, 0.2);
			//	col = mult_color(env->objs[ob].col, 0.0);
			//	res = 0.00;
			//	col = add_color(mult_color(env->objs[ob].col, 0.15), mult_color(env->objs[ob].col, res));
			return (NULL);
		}
	}
	env->init_rays.r = tmp2;
	env->init_rays.r2 = tmp;
	pos_col = get_norm(env->objs[ob], env->init_rays, pos_col);
	pos_col = vect_norm(pos_col);
	res = (env->objs[ob].type == 'p' && vect_scal_prod(pos_col, tmp) > 0.0) ? vect_scal_prod(vect_inv(pos_col), col_2_lum_norm) : vect_scal_prod(pos_col, col_2_lum_norm);
	res = (res < 0.0) ? 0.0 : res * env->lums[lumcur].coef;
	tmp = vect_sous(col_2_lum_norm, tmp);
	tmp = vect_norm(tmp);
//	col->c.r = fmin(255.0, fmax(0.0, env->lums[lumcur].col.c.r * fmin(1.0, ((1.0 - env->portion) + env->objs[ob].col.c.r * env->portion) * pow(vect_scal_prod(tmp, pos_col), env->objs[ob].p))) * res + env->objs[ob].col.c.r * res);
//	col->c.g = fmin(255.0, fmax(0.0, env->lums[lumcur].col.c.g * fmin(1.0, ((1.0 - env->portion) + env->objs[ob].col.c.g * env->portion) * pow(vect_scal_prod(tmp, pos_col), env->objs[ob].p))) * res + env->objs[ob].col.c.g * res);
//	col->c.b = fmin(255.0, fmax(0.0, env->lums[lumcur].col.c.b * fmin(1.0, ((1.0 - env->portion) + env->objs[ob].col.c.b * env->portion) * pow(vect_scal_prod(tmp, pos_col), env->objs[ob].p))) * res + env->objs[ob].col.c.b * res);
	*col = mult_color(env->objs[ob].col, res);
	return (col);
	}
//env->portion:p, env->objs.p:n(rugosite), constante2test for ksy

t_color		get_col(t_env *env, t_v vect)
{
	t_color	colo;
	int		i;
	double	test;
	t_v		u1;
	t_v		u2;
	int		ob;
	t_color	*tmp;

	i = 0;
	ob = which_obj_col(env);
	if (env->objs[ob].type == 'p' && env->objs[ob].radius < 0.0)
		{
			u1 = (vect_scal_prod(env->init_rays.r2, env->objs[ob].norm)) > 0.000 ?
		env->objs[ob].norm : vect_inv(env->objs[ob].norm);
		//	u1 = env->init_rays.r;
			u2 = env->init_rays.r2;
			env->init_rays.r = vect_add(vect_add(env->cams[env->curr_cam].pos_cam, vect_mult(vect, env->objs[ob].dist)), vect_mult(env->init_rays.r, 0.5));
			env->init_rays.r2 = rotation(vect_inv(u2), env->objs[ob].norm, 180.000);
			ob = which_obj_col(env);
		}
	if (ob < 0 || env->objs[ob].dist <= 0.0)//there has been no collision with any object
	{
		while (i < env->nb_lum)
		{
				if (vect_scal_prod(vect, vect_norm(vect_sous(env->cams[env->curr_cam].pos_cam, env->lums[i].pos_lum))) < -0.999995)
					return (get_white());
				else
					return(get_black());
				i++;
		}
	}
	i = 0;
	test = 1.00;
	colo = get_black();
	while (i < env->nb_lum)
	{
		if ((tmp = get_lums(env, i, ob)) != NULL)
		{
			colo = add_color(colo, mult_color(*tmp, 0.500 / env->nb_lum));
			ft_bzero(tmp, sizeof(t_color));
			ft_memdel((void **)&tmp);
		}
		if (vect_scal_prod(vect, vect_norm(vect_sous(env->cams[env->curr_cam].pos_cam, env->lums[i].pos_lum))) < -0.999995)
//			test = vect_scal_prod(vect, vect_norm(vect_sous(env->cams[env->curr_cam].pos_cam, env->lums[i].pos_lum)));
			return (get_white());
		i++;
	}
	colo = mult_color(colo, 3.500 / env->nb_lum);
//	colo = add_color(colo, mult_color(env->objs[ob].col, 0.1500));
//	if (test > -0.7)
	return (colo);
//	return (satur_col(colo, 1.000 / (0.0000 - vect_scal_prod(vect, vect_norm(vect_sous(env->cams[env->curr_cam].pos_cam, env->lums[i].pos_lum))))));
//	return (satur_col(colo, -1.00 * test));
}

/*
**rays: a function that call get_col for each pixel and update window surface
*/

void		rays(t_env *env)
{
	int		i;
	int		y;
	int		x;
	int		alias_coef;
	t_color	col;

	y = 0;
	alias_coef = env->flou;
	while ((x = 0) == 0 && y < WIN_Y)
	{
		while ((i = 0) == 0 && x < WIN_X &&
				init_ray(env, x + alias_coef / 2.0, y + alias_coef / 2.0))
		{
			col = get_col(env, env->init_rays.r2);
			((int *)env->surf->pixels)[x + y * env->surf->w] = col.color;
			while (alias_coef > 1 && ++i < alias_coef * alias_coef)
				if (x + i % alias_coef < WIN_X && y + i / alias_coef < WIN_Y)
					((int *)env->surf->pixels)[x + i % alias_coef +
						(y + i / alias_coef) * env->surf->w] = col.color;
			x += alias_coef;
		}
		y += alias_coef;
	}
	set_filter(env);
	SDL_UpdateWindowSurface(env->win);
}

/*
**init: initialise sdl, malloc and fill the data struct (here: env)
*/

t_env		*init(char *filename)
{
	t_env	*env;

	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		if (!(env = (t_env *)malloc(sizeof(t_env) * 1)))
			return (0);
		env->file = ft_strdup(filename);
		j_init(env);
		if (!(env->win = SDL_CreateWindow(env->name, SDL_WINDOWPOS_CENTERED,
						SDL_WINDOWPOS_CENTERED, WIN_X, WIN_Y, SDL_WINDOW_SHOWN)))// | SDL_WINDOW_FULLSCREEN_DESKTOP)))
						{
							ft_putendl("error");
							return (NULL);
						}
		if (!(env->surf = SDL_GetWindowSurface(env->win)))
		{
			ft_putendl("error");
			return (NULL);
		}
		env->col_fcts[0] = get_dist_sphere;
		env->col_fcts[1] = get_dist_plan;
		env->col_fcts[2] = get_dist_tube;
		env->col_fcts[3] = get_dist_cone;
		env->flou = 4;
		env->curr_obj = -1;
		env->curr_cam = 0;
		env->curr_lum = 0;
		env->state = 0;
		env->constante2test = 1.0;
		env->portion = 0.0003;
		return (env);
	}
	ft_putendl("failed to init sdl");
	return (NULL);
}

int			main(int ac, char **av)
{
	int			i;
	t_env		*env;

	if (ac != 2 || !ft_strstr(av[1], ".json"))
		ft_put_err("usage : ./rtv1 <scene.json>");
	if (!(env = init(av[1])))
		ft_put_err("error in init");
//	init_scene(env);
	i = -1;
	while (++i < env->nb_lum)
	{
		env->lums[i].coef = 0.4;
	}
	rays(env);
	while (!env->state)
	{
		events(env);
	}
/*	if (ac == 2)
	{
		ft_putstr("atoi:");
		ft_putnbr(atoi(av[1]));
		ft_putstr("\natof:");
		ft_putnbr(ft_atof(av[1]));
		ft_putstr("\n1000*atof:");
		ft_putnbr(100000000 * ft_atof(av[1]));
		ft_putstr("\natof+putfloat:");
		ft_putfloat_fd(ft_atof(av[1]), 1);
		ft_putstr("\n");
	}*/
	SDL_DestroyWindow(env->win);
	free(env);
//	(void)i;
//	(void)env;
	SDL_Quit();
	return (1);
}

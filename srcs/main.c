/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 18:01:03 by tjeanner          #+#    #+#             */
/*   Updated: 2018/04/22 20:38:44 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**get_col: a function that will return a col structure containing color
**corresponding for desired pixel (specified by x & y)
*/

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
	pos_col = vect_add(env->init_rays.pos, vect_mult(env->init_rays.dir,
				env->objs[ob].dist));//pos toucher
	col_2_lum = vect_sous(env->lums[lumcur].pos, pos_col);
	col_2_lum_norm = vect_norm(col_2_lum);
//	pos_col = get_norm(env->objs[ob], env->init_rays, pos_col);
//////	pos_col = vect_norm(pos_col);
	tmp = vect_mult(get_norm(env->objs[ob], env->init_rays, pos_col), 0.000100);
//	col->c.r = 255 * fabs(pos_col.x);
//	col->c.g = 255 * fabs(pos_col.y);
//	col->c.b = 255 * fabs(pos_col.z);
//	col->c.a = 0;
//	return (col);
	tmp = (env->objs[ob].type == 'p' && vect_scal(env->objs[ob].norm, env->init_rays.dir) > 0.0) ? vect_inv(tmp): tmp;
	pos_col = vect_add(pos_col, tmp);
//	col_2_lum = vect_sous(env->lums[lumcur].pos, pos_col);
//	col_2_lum_norm = vect_norm(col_2_lum);
	tmp2 = env->init_rays.pos;
	env->init_rays.pos = pos_col;
	tmp = env->init_rays.dir;
	env->init_rays.dir = col_2_lum_norm;
	while (++i < env->nb_obj)//we search an object between the collision and the light source
	{
		env->init_rays.d1 = -100000.0;
		env->init_rays.d2 = -100000.0;
		if (env->col_fcts[ft_strchr(FCTS, env->objs[i].type) - FCTS](
			&env->init_rays, env->objs[i]) == 1 && (((env->init_rays.d1 > -0.0001 &&
			env->init_rays.d1 < get_vect_norm(col_2_lum) - 0.0001) || ((env->init_rays.d2 >
			-0.0001 && env->init_rays.d2 < get_vect_norm(col_2_lum) - 0.0001)))))
		{
			//	col = mult_color(env->objs[ob].col, 0.2);
			//	col = mult_color(env->objs[ob].col, 0.0);
			//	res = 0.00;
			//	col = add_color(mult_color(env->objs[ob].col, 0.15), mult_color(env->objs[ob].col, res));
			return (NULL);
		}
	}
	env->init_rays.pos = tmp2;
	env->init_rays.dir = tmp;
	pos_col = get_norm(env->objs[ob], env->init_rays, pos_col);
	pos_col = vect_norm(pos_col);
	res = (env->objs[ob].type == 'p' && vect_scal(pos_col, tmp) > 0.0) ? vect_scal(vect_inv(pos_col), col_2_lum_norm) : vect_scal(pos_col, col_2_lum_norm);
	res = (res < 0.0) ? 0.0 : res * env->lums[lumcur].coef;
	tmp = vect_sous(col_2_lum_norm, tmp);
	tmp = vect_norm(tmp);
//	col->c.r = fmin(255.0, fmax(0.0, env->lums[lumcur].col.c.r * fmin(1.0, ((1.0 - env->portion) + env->objs[ob].col.c.r * env->portion) * pow(vect_scal(tmp, pos_col), env->objs[ob].k_diff))) * res + env->objs[ob].col.c.r * res);
//	col->c.g = fmin(255.0, fmax(0.0, env->lums[lumcur].col.c.g * fmin(1.0, ((1.0 - env->portion) + env->objs[ob].col.c.g * env->portion) * pow(vect_scal(tmp, pos_col), env->objs[ob].k_diff))) * res + env->objs[ob].col.c.g * res);
//	col->c.b = fmin(255.0, fmax(0.0, env->lums[lumcur].col.c.b * fmin(1.0, ((1.0 - env->portion) + env->objs[ob].col.c.b * env->portion) * pow(vect_scal(tmp, pos_col), env->objs[ob].k_diff))) * res + env->objs[ob].col.c.b * res);
	*col = mult_color(env->objs[ob].col, res);
//	col->c.r = 255 * fabs(pos_col.x);
//	col->c.g = 255 * fabs(pos_col.y);
//	col->c.b = 255 * fabs(pos_col.z);
//	col->c.a = 0;
	return (col);
	}
//env->portion:p, env->objs.p:n(rugosite), constante2test for ksy

t_color		vieuget_col(t_env *env, t_v vect, t_color *colo)
{
	int		i;
	double	test;
	t_v		u1;
	t_v		u2;
	int		ob;
	t_color	*tmp;

	i = 0;
	if ((ob = which_obj_col(env)) == -1)
		return (get_black());
	else if (ob == -2)
		return (get_white());
	u1 = vect_add(env->init_rays.pos, vect_mult(env->init_rays.dir, env->objs[ob].dist));//poscol
	u2 = vect_norm(get_norm(env->objs[ob], env->init_rays, u1));
//	colo->c.r = 255 * fabs(u2.x);
//	colo->c.g = 255 * fabs(u2.y);
//	colo->c.b = 255 * fabs(u2.z);
//	colo->c.a = 0;
//	return (*colo);
/*	if (env->objs[ob].radius < 0.0)
	{
		if (env->objs[ob].type == 's')
		{
			u1 = vect_sous(vect_add(env->cams[env->curr_cam].pos, vect_mult(env->init_rays.dir, env->objs[ob].dist)), env->objs[ob].o);
//			u1 = (vect_scal(env->init_rays.dir, env->objs[ob].norm)) > 0.000 ?
//		env->objs[ob].norm : vect_inv(env->objs[ob].norm);
		//	u1 = env->init_rays.pos;
			u2 = env->init_rays.dir;
			env->init_rays.pos = vect_add(vect_add(env->cams[env->curr_cam].pos, vect_mult(env->init_rays.dir, env->objs[ob].dist)), vect_mult(env->init_rays.pos, 0.5));
			env->init_rays.dir = rotation(vect_inv(u2), u1, 180.000);
		}
		else
		{
//			u1 = vect_sous(vect_add(env->cams[env->curr_cam].pos, vect_mult(env->init_rays.dir, env->objs[ob].dist)), env->objs[ob].o);
			u1 = (vect_scal(env->init_rays.dir, env->objs[ob].norm)) > 0.000 ?
			env->objs[ob].norm : vect_inv(env->objs[ob].norm);
		//	u1 = env->init_rays.pos;
			u2 = env->init_rays.dir;
			env->init_rays.pos = vect_add(vect_add(env->cams[env->curr_cam].pos, vect_mult(env->init_rays.dir, env->objs[ob].dist)), vect_mult(u1, 0.5));
			env->init_rays.dir = rotation(vect_inv(u1), vect, 180.000);
		}
//		ob = which_obj_col(env);
		return(get_col(env, vect, colo));
	}*/
	if (ob < 0 || env->objs[ob].dist <= 0.0)//there has been no collision with any object
	{
		while (i < env->nb_lum)
		{
				if (vect_scal(vect, vect_norm(vect_sous(env->cams[env->curr_cam].pos, env->lums[i].pos))) < -0.999995)
					return (get_white());
				else
					return(get_black());
				i++;
		}
	}
	i = 0;
	test = 1.00;
	*colo = get_black();
	while (i < env->nb_lum)
	{
		if ((tmp = get_lums(env, i, ob)) != NULL)
		{
			*colo = add_color(*colo, mult_color(*tmp, 2.500 / env->nb_lum));
			ft_bzero(tmp, sizeof(t_color));
			ft_memdel((void **)&tmp);
		}
		if (vect_scal(vect, vect_norm(vect_sous(env->cams[env->curr_cam].pos, env->lums[i].pos))) < -0.999995)
//			test = vect_scal(vect, vect_norm(vect_sous(env->cams[env->curr_cam].pos, env->lums[i].pos)));
			return (get_white());
		i++;
	}
//	*colo = mult_color(*colo, 3.500 / env->nb_lum);
//	colo = add_color(colo, mult_color(env->objs[ob].col, 0.1500));
//	if (test > -0.7)
	return (*colo);
//	return (satur_col(colo, 1.000 / (0.0000 - vect_scal(vect, vect_norm(vect_sous(env->cams[env->curr_cam].pos, env->lums[i].pos))))));
//	return (satur_col(colo, -1.00 * test));
}

/*
**rays: a function that call get_col for each pixel and update window surface
*/

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
			error_mgt(8);
		if (!(env->surf = SDL_GetWindowSurface(env->win)))
			error_mgt(8);
		if (!(env->surf2 = SDL_CreateRGBSurface(0, WIN_X, WIN_Y, 32,
								   0, 0, 0, 0)))
			error_mgt(8);
		return (env);
	}
	error_mgt(8);
	return (NULL);
}

void		destrucainitialiserquonveutaussiapresreload(t_env *env)
{
	int		i;

	env->col_fcts[0] = get_dist_sphere;
	env->col_fcts[1] = get_dist_plan;
	env->col_fcts[2] = get_dist_tube;
	env->col_fcts[3] = get_dist_cone;
	env->flou = 4;
	env->curr_obj = -1;
	env->curr_cam = 0;
	env->curr_lum = 0;
	env->state = 0;
	env->portion = 3;
	env->coefs_sum = 0.0;
	i = -1;
	while (++i < env->nb_cam)
		env->cams[env->curr_cam].v3cam = vect_prod(
		env->cams[env->curr_cam].vcam, env->cams[env->curr_cam].v2cam);
	i = -1;
	while (++i < env->nb_obj)
		env->objs[i].k_diff = 1.0;
	i = -1;
	while (++i < env->nb_lum)
		env->coefs_sum += env->lums[i].coef;
}

void		tutu(t_env *env)
{
	t_cam	tmp;

	if (env->stereo)
	{
		tmp = env->cams[env->curr_cam];
		env->cams[env->curr_cam].pos.x -= 20;
		rays(env, env->surf2);
		env->cams[env->curr_cam] = tmp;
	}
	rays(env, env->surf);
	set_filter(env);
	SDL_UpdateWindowSurface(env->win);

}

int			main(int ac, char **av)
{
	t_env		*env;

	if (ac != 2 || !ft_strstr(av[1], ".json"))
		error_mgt(6);
	if (!(env = init(av[1])))
		error_mgt(6);
	tutu(env);
	while (!env->state)
	{
		events(env);
	}
	SDL_DestroyWindow(env->win);
	free(env);
	SDL_Quit();
	return (1);
}

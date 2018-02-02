/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 18:01:03 by tjeanner          #+#    #+#             */
/*   Updated: 2018/02/01 23:52:14 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


int			init_ray(t_env *env, float x, float y)
{
	t_v		center_screen_2_pix;
	t_v		cam_2_center_screen;
	t_v		cam_2_pixel;
	t_v		cam_2_pixel_norm;

	env->cams[env->curr_cam].v3cam = vect_mult(vect_prod(env->cams[env->curr_cam].vcam, env->cams[env->curr_cam].v2cam), -1.0);
	cam_2_center_screen = vect_mult(env->cams[env->curr_cam].vcam, DIST);
	center_screen_2_pix = vect_add(vect_mult(env->cams[env->curr_cam].v3cam, (x - WIN_X / 2.0) / vect_norm(env->cams[env->curr_cam].v3cam)),
			vect_mult(env->cams[env->curr_cam].v2cam, -1.0 * (y - WIN_Y / 2.0) / vect_norm(env->cams[env->curr_cam].v2cam)));
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
	while (++i < env->nb_obj && (env->objs[i].dist = -1) == -1)//we search a collision between the ray and each objects
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
			env->objs[i].dist = -1;
	i = -1;
	while (++i < env->nb_obj)//we select the shortest distance in all the one we havect
	{
		if ((i == 0 || (env->objs[i].dist > 0.0 &&
						(res == -1 || res > env->objs[i].dist))) && (ob = i) == i)
			res = env->objs[i].dist;
	}
	return (ob);
}

t_color		get_col(t_env *env)
{
	int		i;//index that run through all objects
	int		ob;//to store the value of the index i when we find the object
	double	res;//to store the value of the distance when we find the object
	t_color	col[3];
	t_v		norm;
	t_v		tmp;
	t_v		s;
	t_v		r;
	t_v		pos_collision;
	t_v		collision_2_lum;
	t_v		collision_2_lum_norm;

	ob = which_obj_col(env);
	col[0].c.a = 0;
	col[1].c.a = 0;
	col[2].c.a = 0;
	if (env->objs[ob].dist <= 0.0)//there has been no collision with any object
		set_black(&col[0]);
	else
	{
		pos_collision = vect_add(env->init_rays.r, vect_mult(env->init_rays.r2,
					env->objs[ob].dist));//pos toucher
		collision_2_lum = vect_add(env->lums[0].pos_lum,
				vect_mult(pos_collision, -1.0));
		env->init_rays.r = pos_collision;
		collision_2_lum_norm = vect_mult(collision_2_lum,
				1.0 / vect_norm(collision_2_lum));
		tmp = env->init_rays.r2;
		env->init_rays.r2 = collision_2_lum_norm;
		i = -1;
		while ((i = (i == ob - 1) ? i + 2 : i + 1) < env->nb_obj)//we search an object between the collision and the light source
		{
			env->init_rays.v1 = -1;
			env->init_rays.v2 = -1;
			if (env->col_fcts[ft_strchr(FCTS, env->objs[i].type) - FCTS](
	&env->init_rays, env->objs[i]) == 1 && ((env->init_rays.v1 > 5 &&
	env->init_rays.v1 < vect_norm(collision_2_lum)) || ((env->init_rays.v2 >
		5 && env->init_rays.v2 < vect_norm(collision_2_lum)))))
			{
				set_black(&col[0]);
	//			col[0] = mult_color(env->objs[ob].col, 0.2);
				return (col[0]);
			}
		}
		if (env->objs[ob].type == 's')
		{
			norm = vect_add(pos_collision, vect_mult(env->objs[ob].o, -1.0));
			norm = vect_mult(norm, 1.0 / vect_norm(norm));//v norm a toucher
			res = vect_scal_prod(norm, collision_2_lum_norm);
		}
		else if (env->objs[ob].type == 'p')
		{
			norm = env->objs[ob].norm;
			res = vect_scal_prod(norm, collision_2_lum_norm);
			res = (vect_scal_prod(norm, tmp) >= 0.0) ? 0.0 : res;
		}
		else
		{
			s = vect_add(env->objs[ob].o, vect_mult(env->objs[ob].norm, -1.0));
			s = vect_mult(s, 1.0 / vect_norm(s));
			res = ((double)((s.x * (env->init_rays.r.x - env->objs[ob].norm.x) +
						s.y * (env->init_rays.r.y - env->objs[ob].norm.y) +
						s.z * (env->init_rays.r.z - env->objs[ob].norm.z)) /
					vect_scal_prod(s, s)));
			norm = vect_add(env->objs[ob].norm, vect_mult(s, res));
			norm = vect_add(env->init_rays.r, vect_mult(norm, -1.0));
			norm = vect_mult(norm, 1.0 / vect_norm(norm));
			res = vect_scal_prod(norm, collision_2_lum_norm);
//			res = (vect_scal_prod(collision_2_lum_norm, tmp) > 0.0) ? 0.0 : res * 1.0;
//			col[0] = mult_color(env->objs[ob].col, 1.0);
//			return (col[0]);
		}
		res = (res < 0.0) ? 0.0 : res;
		(void)r;
	//	r = vect_add(vect_mult(collision_2_lum_norm, -1.0), vect_mult(norm, 2.0 * vect_scal_prod(norm, collision_2_lum_norm)));
	//	if (vect_scal_prod(vect_mult(r, 1.0 / vect_norm(r)), vect_mult(tmp, -1.0 / vect_norm(tmp))) < 0)
	//		set_white(&col[0]);
			//col[0] = mult_color(env->objs[ob].col, res);
	//	else
	//	{
	//		set_black(&col[0]);
	//		set_black(&col[1]);
	//		set_black(&col[2]);
	//		col[0] = mult_color( , 0.1 * );
		col[0] = mult_color(env->objs[ob].col, res);
	//	}
	//	col[0].c.a = (env->lums[0].coef * env->objs[ob].spec_coef * pow(vect_scal_prod(r, vect_mult(tmp, -1.0 / vect_norm(tmp))), env->objs[ob].surf_coef) * (1.0 - env->objs[ob].plast_coef) * (env->objs[ob].col.c.a));
	//	col[0].c.b = (env->lums[0].coef * env->objs[ob].spec_coef * pow(vect_scal_prod(r, vect_mult(tmp, -1.0 / vect_norm(tmp))), env->objs[ob].surf_coef) * (1.0 - env->objs[ob].plast_coef) * (env->objs[ob].col.c.b));
	//	col[0].c.g = (env->lums[0].coef * env->objs[ob].spec_coef * pow(vect_scal_prod(r, vect_mult(tmp, -1.0 / vect_norm(tmp))), env->objs[ob].surf_coef) * (1.0 - env->objs[ob].plast_coef) * (env->objs[ob].col.c.g));
//		col[0] = mult_color(env->objs[ob].col, 1.0 - env->objs[ob].plast_coef);
	}
	return (col[0]);
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
	t_color	col[64];

	ft_putstr("calculating image with ");
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
		while (b < WIN_X && init_ray(env, b, a))//for each pixel in the row
		{
			c = ((int)1.0 / flou_square * (a - (int)a)) + ((int)1.0 /
					env->flou * (b - (int)b));//col is set with desired color for current pixel
			col[c] = get_col(env);//col is set with desired color for current pixel
			if (env->flou < 1 && c + 1.0 == 1.0 / flou_square &&
					average_color(col, env->flou))
				((int *)env->surf->pixels)[((int)((int)b + env->flou - 1.0) +
					((int)(a + env->flou - 1.0) * env->surf->w))] = col[0].color;
			c = -1.0;
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
		env->flou = 4;
		env->state = 0;
		env->curr_cam = 0;
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
//	while (++i < env->nb_obj)
//	{
//		env->objs[i].spec_coef = 0.1;//ks
//		env->objs[i].surf_coef = 0.8;//ka
//		env->objs[i].plast_coef = 0.4;
//	}
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

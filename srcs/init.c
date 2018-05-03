/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 06:11:11 by hbouchet          #+#    #+#             */
/*   Updated: 2018/05/03 06:11:43 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_env		*init(char *filename)
{
	t_env	*env;

	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		if (!(env = (t_env *)malloc(sizeof(t_env) * 1)))
			error_mgt(0);
		if (ft_strstr((env->file = ft_strdup(filename)), ".json"))
			j_init(env);
		else if (ft_strstr(env->file, ".obj"))
			env->objs.tri = parse_main(env, filename);
		env->screen.time = 0;
		env->screen.rec = 0;
		env->screen.play = 1;
		if (!(env->display.win = SDL_CreateWindow(env->name,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WIN_X, WIN_Y, SDL_WINDOW_SHOWN)))
			error_mgt(8);
		if (!(env->display.surf = SDL_GetWindowSurface(env->display.win)))
			error_mgt(8);
		if (!(env->display.surf2 = SDL_CreateRGBSurface(0, WIN_X, WIN_Y, 32,
								0, 0, 0, 0)))
			error_mgt(8);
		return (env);
	}
	return (error_mgt(8));
}

static void	data_init(t_env *env)
{
	env->objs.col_fcts[0] = get_dist_sphere;
	env->objs.col_fcts[1] = get_dist_plan;
	env->objs.col_fcts[2] = get_dist_tube;
	env->objs.col_fcts[3] = get_dist_cone;
	env->objs.curr = -1;
	env->cams.curr = 0;
	env->lums.curr = 0;
	env->state = 0;
	env->lums.coefs_sum = 0.0;
}

void		data_init_and_reload(t_env *env)
{
	int		i;
	double	tmp;
	t_obj	obj;

	data_init(env);
	i = -1;
	while (++i < env->cams.nb)
		env->cams.cam[env->cams.curr].v3cam = vect_prod(
			env->cams.cam[env->cams.curr].vcam,
			env->cams.cam[env->cams.curr].v2cam);
	i = -1;
	while (++i < env->objs.nb)
	{
		if (env->objs.obj[i].type == PLANE)
		{
			obj = env->objs.obj[i];
			tmp = -1.0 * vect_scal(obj.norm, obj.o);
			if (obj.norm.z != 0)
			{
				obj.norm2.y = 1;
				obj.norm2.x = 1;
				obj.norm2.z = -1.0 * (obj.norm.y + obj.norm.x + tmp) / obj.norm.z;
			}
			else if (obj.norm.x != 0)
			{
				obj.norm2.y = 1;
				obj.norm2.z = 1;
				obj.norm2.x = -1.0 * (obj.norm.y + obj.norm.z + tmp) / obj.norm.x;
			}
			else if (obj.norm.y != 0)
			{
				obj.norm2.z = 1;
				obj.norm2.x = 1;
				obj.norm2.y = -1.0 * (obj.norm.z + obj.norm.x + tmp) / obj.norm.y;
			}
			obj.norm2 = vect_norm(vect_sous(obj.norm2, obj.o));
			env->objs.obj[i] = obj;
		}
	}
	i = -1;
	while (++i < env->lums.nb)
		env->lums.coefs_sum += env->lums.lum[i].coef;
	if (!(env->threads = (t_threads *)malloc(sizeof(t_threads) * NB_THREADS)))
		error_mgt(0);
	i = -1;
	while (++i < NB_THREADS)
	{
		env->threads[i].start = i;
		env->threads[i].incr = NB_THREADS;
		env->threads[i].env = env;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 18:01:03 by tjeanner          #+#    #+#             */
/*   Updated: 2018/04/28 19:51:04 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
		if (!(env->display.win = SDL_CreateWindow(env->name, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIN_X, WIN_Y, SDL_WINDOW_SHOWN)))// | SDL_WINDOW_FULLSCREEN_DESKTOP)))
			error_mgt(8);
		if (!(env->display.surf = SDL_GetWindowSurface(env->display.win)))
			error_mgt(8);
		if (!(env->display.surf2 = SDL_CreateRGBSurface(0, WIN_X, WIN_Y, 32,
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

	env->objs.col_fcts[0] = get_dist_sphere;
	env->objs.col_fcts[1] = get_dist_plan;
	env->objs.col_fcts[2] = get_dist_tube;
	env->objs.col_fcts[3] = get_dist_cone;
	env->objs.curr = -1;
	env->cams.curr = 0;
	env->lums.curr = 0;
	env->state = 0;
//	env->portion = 3;
//	env->lums.coefs_sum = 0.0;
//	env->lums.amb_coef = 0.2;
	i = -1;
	while (++i < env->cams.nb)
		env->cams.cam[env->cams.curr].v3cam = vect_prod(
		env->cams.cam[env->cams.curr].vcam, env->cams.cam[env->cams.curr].v2cam);
//	env->lums.coefs_sum = 1.0;
//	i = -1;
//	while (++i < env->objs.nb)// && (env->lums.coefs_sum += env->lums.lum[i].coef))
//		env->objs.obj[i].k_diff = 1.0;
	i = -1;
	while (++i < env->lums.nb)
		env->lums.coefs_sum += env->lums.lum[i].coef;
	if (!(env->threads = (t_threads *)malloc(sizeof(t_threads) * NB_THREADS)))
		return ;
	i = -1;
	while (++i < NB_THREADS)
	{
		env->threads[i].start = i;
		env->threads[i].incr = NB_THREADS;
		env->threads[i].env = env;
	}
}

void		tutu(t_env *env)
{
	int		i;
	t_cam	tmp;
	
	env->display.sur = 1;
	if (env->effects.stereo)
	{
		tmp = env->cams.cam[env->cams.curr];
		env->cams.cam[env->cams.curr].pos.x -= 20;
//		rays(env, env->surf2);
		env->display.sur = 2;
		i = -1;
		while (++i < NB_THREADS)
			if (pthread_create(&env->threads[i].id, NULL, rays, (void *)&env->threads[i]) != 0)
				return ;
		i = -1;
		while (++i < NB_THREADS)
			pthread_join(env->threads[i].id, NULL);
		env->cams.cam[env->cams.curr] = tmp;
	}
//	rays(env, env->surf);
	env->display.sur = 1;
	i = -1;
	while (++i < NB_THREADS)
		if (pthread_create(&env->threads[i].id, NULL, rays, (void *)&env->threads[i]) != 0)
			return ;
	i = -1;
	while (++i < NB_THREADS)
		pthread_join(env->threads[i].id, NULL);
	set_filter(env);
	SDL_UpdateWindowSurface(env->display.win);
}

int			main(int ac, char **av)
{
	t_env		*env;
	t_ui ui;

	if (ac != 2 || !ft_strstr(av[1], ".json"))
		error_mgt(6);
	if (!(env = init(av[1])))
		error_mgt(6);
//	env->objs.obj[0].reflect = 0.;
	tutu(env);
	ui = UI_main();
	env->ui = &ui;
	while (!env->state)
	{
		events(env);
		SDL_UpdateWindowSurface(env->ui->win);
	}
	ft_freeenv(env);
	SDL_Quit();
	return (1);
}

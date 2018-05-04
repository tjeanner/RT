/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 18:01:03 by tjeanner          #+#    #+#             */
/*   Updated: 2018/05/04 00:04:09 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	stereo_thread(t_env *env)
{
	int		i;
	t_cam	tmp;

	tmp = env->cams.cam[env->cams.curr];
	env->cams.cam[env->cams.curr].pos.x -= 20;
	env->display.sur = 2;
	i = -1;
	while (++i < NB_THREADS)
		if (pthread_create(&env->threads[i].id, NULL,
			rays, (void *)&env->threads[i]) != 0)
			error_mgt(10);
	i = -1;
	while (++i < NB_THREADS)
		pthread_join(env->threads[i].id, NULL);
	env->cams.cam[env->cams.curr] = tmp;
}

void		thread_create(t_env *env)
{
	int		i;

	env->display.sur = 1;
	if (env->effects.stereo)
		stereo_thread(env);
	env->display.sur = 1;
	i = -1;
	while (++i < NB_THREADS)
		if (pthread_create(&env->threads[i].id, NULL,
			rays, (void *)&env->threads[i]) != 0)
			error_mgt(10);
	i = -1;
	while (++i < NB_THREADS)
		pthread_join(env->threads[i].id, NULL);
	set_filter(env);
	if (env->screen.rec)
		ev_screenshot(env);
	SDL_UpdateWindowSurface(env->display.win);
}

int			main(int ac, char **av)
{
	t_env		*env;

	if (WIN_X < 50 || WIN_Y < 50 || WIN_X > 1920 || WIN_Y > 1080)
		error_mgt(8);
	if (ac != 2 || (!ft_strstr(av[1], ".json") && !ft_strstr(av[1], ".obj")))
		error_mgt(6);
	if (!(env = init(av[1])))
		error_mgt(6);
	thread_create(env);
	while (!env->state)
	{
		main_action(&env->objs, env->screen.play);
		events(env);
	}
	ft_freeenv(env);
	SDL_Quit();
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_sel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 06:29:51 by hbouchet          #+#    #+#             */
/*   Updated: 2018/05/04 03:25:32 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	torus_color_ch(t_env *env)
{
	int		i;
	t_color	col;

	i = -1;
	col = get_rand();
	while (++i < env->objs.nb)
		if (env->objs.obj[i].link == env->objs.obj[env->objs.curr].link)
			env->objs.obj[i].col = col;
}

int			move_events(t_env *env, unsigned int sym)
{
	if ((sym == SDLK_1 || sym == SDLK_2 || sym == SDLK_3 || sym == SDLK_4))
		update_and_copy_a(env, sym, NULL);
	else if (sym == SDLK_BACKSPACE && env->objs.curr >= 0)
		update_and_copy_r(env, env->objs.curr);
	else if (sym == SDLK_BACKSLASH)
	{
		if (env->objs.curr >= 0 && env->objs.obj[env->objs.curr].link == 0)
			env->objs.obj[env->objs.curr].col = get_rand();
		else if (env->objs.curr == -2)
			env->lums.lum[env->lums.curr].col = get_rand();
		else if (env->objs.curr >= 0 && env->objs.obj[env->objs.curr].link != 0)
			torus_color_ch(env);
	}
	else if (sym == SDLK_c && env->lums.amb_coef >= 0.020)
		env->lums.amb_coef -= 0.020;
	else if (sym == SDLK_v && env->lums.amb_coef <= 0.980)
		env->lums.amb_coef += 0.020;
	else
		return (0);
	return (1);
}

static void	events_sel_obj(t_env *env, SDL_Event event)
{
	t_ray	tmp;

	tmp = init_line(event.button.x, event.button.y,
			env->cams.cam[env->cams.curr]);
	if (which_obj_col(&env->objs, &tmp))
		env->objs.curr = tmp.obj;
}

int			events_sel(t_env *env, SDL_Event event, unsigned int sym)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (sym == SDLK_p)
			env->objs.curr = (env->objs.curr < env->objs.nb - 1)
							? env->objs.curr + 1 : 0;
		else if (sym == SDLK_SEMICOLON)
			env->lums.curr = (env->lums.curr < env->lums.nb - 1)
							? env->lums.curr + 1 : 0;
		else if (sym == SDLK_NUMLOCKCLEAR)
			env->objs.curr = (env->objs.curr < 0) ? env->objs.curr + 1 : -2;
		else
			return (0);
		return (1);
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN
		&& event.button.button == SDL_BUTTON_LEFT)
	{
		events_sel_obj(env, event);
		return (0);
	}
	else
		return (0);
	return (1);
}

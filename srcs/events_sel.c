/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_sel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 06:29:51 by hbouchet          #+#    #+#             */
/*   Updated: 2018/05/02 20:11:12 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		events_sel(t_env *env, SDL_Event event, unsigned int sym)
{
	t_ray	tmp;

	if (event.type == SDL_KEYDOWN)
	{
		if (sym == SDLK_z)
		{
			env->cams.curr = (env->cams.curr < env->cams.nb - 1)
				? env->cams.curr + 1 : 0;
			tutu(env);
		}
		else if (sym == SDLK_p)
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
		tmp = init_line(event.button.x, event.button.y, env->cams.cam[env->cams.curr]);
		if (which_obj_col(&env->objs, &tmp))
			env->objs.curr = tmp.obj;
		return (0);
	}
	else
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_sel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 06:29:51 by hbouchet          #+#    #+#             */
/*   Updated: 2018/05/01 03:12:24 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
int		event_cam_switch(t_env *env, unsigned int sym)
{
	if ()
		env->cams.curr = (env->cams.curr < env->cams.nb - 1) ? env->cams.curr + 1 : 0;
	// int		i;

	// i = 0;
	// while (i < 10)
	// {
	// 	if (sym == SDLK_KP_0 + (unsigned int)i && env->cams.curr != i)
	// 	{
	// 		env->cams.curr = i;
	// 		break 	;
	// 	}	
	// 	i++; 
	// }
	// if (sym == SDLK_KP_0 && env->cams.curr != 0)
	// 	env->cams.curr = 0;
	// else if (sym == SDLK_KP_1 && env->cams.nb > 1 && env->cams.curr != 1)
	// 	env->cams.curr = 1;
	// else if (sym == SDLK_KP_2 && env->cams.nb > 2 && env->cams.curr != 2)
	// 	env->cams.curr = 2;
	// else if (sym == SDLK_KP_3 && env->cams.nb > 3 && env->cams.curr != 3)
	// 	env->cams.curr = 3;
	// else if (sym == SDLK_KP_4 && env->cams.nb > 4 && env->cams.curr != 4)
	// 	env->cams.curr = 4;
	// else if (sym == SDLK_KP_5 && env->cams.nb > 5 && env->cams.curr != 5)
	// 	env->cams.curr = 5;
	// else if (sym == SDLK_KP_6 && env->cams.nb > 6 && env->cams.curr != 6)
	// 	env->cams.curr = 6;
	// else if (sym == SDLK_KP_7 && env->cams.nb > 7 && env->cams.curr != 7)
	// 	env->cams.curr = 7;
	// else if (sym == SDLK_KP_8 && env->cams.nb > 8 && env->cams.curr != 8)
	// 	env->cams.curr = 8;
	// else if (sym == SDLK_KP_9 && env->cams.nb > 9 && env->cams.curr != 9)
	// 	env->cams.curr = 9;
	else
		return (0);
	return (1);
//	return ((i == 10) ? 0 : 1);
}
*/
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

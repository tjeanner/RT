/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_sel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 06:29:51 by hbouchet          #+#    #+#             */
/*   Updated: 2018/02/15 08:46:29 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		event_cam_switch(t_env *env, unsigned int sym)
{
	if (sym == SDLK_KP_0 && env->curr_cam != 0)
		env->curr_cam = 0;
	else if (sym == SDLK_KP_1 && env->nb_cam > 1 && env->curr_cam != 1)
		env->curr_cam = 1;
	else if (sym == SDLK_KP_2 && env->nb_cam > 2 && env->curr_cam != 2)
		env->curr_cam = 2;
	else if (sym == SDLK_KP_3 && env->nb_cam > 3 && env->curr_cam != 3)
		env->curr_cam = 3;
	else if (sym == SDLK_KP_4 && env->nb_cam > 4 && env->curr_cam != 4)
		env->curr_cam = 4;
	else if (sym == SDLK_KP_5 && env->nb_cam > 5 && env->curr_cam != 5)
		env->curr_cam = 5;
	else if (sym == SDLK_KP_6 && env->nb_cam > 6 && env->curr_cam != 6)
		env->curr_cam = 6;
	else if (sym == SDLK_KP_7 && env->nb_cam > 7 && env->curr_cam != 7)
		env->curr_cam = 7;
	else if (sym == SDLK_KP_8 && env->nb_cam > 8 && env->curr_cam != 8)
		env->curr_cam = 8;
	else if (sym == SDLK_KP_9 && env->nb_cam > 9 && env->curr_cam != 9)
		env->curr_cam = 9;
	else
		return (0);
	return (1);
}

int		events_sel(t_env *env, SDL_Event event, unsigned int sym)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (sym == SDLK_p)
			env->curr_obj = (env->curr_obj < env->nb_obj - 1)
							? env->curr_obj + 1 : 0;
		else if (sym == SDLK_SEMICOLON)
		{
			env->curr_lum = (env->curr_lum < env->nb_lum - 1)
							? env->curr_lum + 1 : 0;
			ft_putnbr(env->curr_lum);
			ft_putnbr(env->nb_lum);
		}
		else if (sym == SDLK_NUMLOCKCLEAR)
			env->curr_obj = -1;
		else if (sym == SDLK_KP_CLEAR)
			env->curr_obj = -1;
		else 
			return (0);
		return (1);
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
	{
		init_ray(env, event.button.x, event.button.y);
		env->curr_obj = which_obj_col(env);
	}
	else 
		return (0);
	return (1);
}

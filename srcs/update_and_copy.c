/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_and_copy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 00:33:47 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/18 18:53:34 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		update_and_copy_r(t_env *env, int obj)
{
	t_obj	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(new = (t_obj *)malloc(sizeof(t_obj) * (env->nb_obj - 1))))
		error_mgt(0);
	while (i < env->nb_obj)
	{
		if (i != obj)
		{
			ft_memcpy((void *)&new[j], (void *)&env->objs[i], sizeof(t_obj));
			j++;
		}
		i++;
	}
	if (obj == env->nb_obj - 1)
		env->curr_obj--;
	env->nb_obj--;
	ft_memdel((void *)&env->objs);
	env->objs = new;
}

void		update_and_copy_a(t_env *env, SDL_Keycode type)
{
	t_obj	*new;
	int		i;

	i = -1;
	if (!(new = (t_obj *)malloc(sizeof(t_obj) * (env->nb_obj + 1))))
		error_mgt(0);
	while (++i < env->nb_obj)
		ft_memcpy((void *)&new[i], (void *)&env->objs[i], sizeof(t_obj));
	new[i].type = FCTS[type - 49];
	new[i].o = vect_add(vect_add(env->cams[env->curr_cam].pos,
		vect_mult(env->cams[env->curr_cam].vcam, 4000)),
		vect_mult(env->cams[env->curr_cam].v2cam, -300));
	new[i].norm = env->cams[env->curr_cam].v2cam;
	new[i].radius = 150;
	set_white(&new[i].col);
	env->nb_obj++;
	env->curr_obj = i;
	ft_memdel((void *)&env->objs);
	env->objs = new;
}

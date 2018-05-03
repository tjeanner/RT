/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_and_copy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 00:33:47 by hbouchet          #+#    #+#             */
/*   Updated: 2018/05/03 20:31:17 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		update_and_copy_r(t_env *env, int obj)
{
	t_obj	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(new = (t_obj *)malloc(sizeof(t_obj) * (env->objs.nb - 1))))
		error_mgt(0);
	while (i < env->objs.nb)
	{
		if (i != obj)
		{
			ft_memcpy((void *)&new[j],
				(void *)&env->objs.obj[i], sizeof(t_obj));
			j++;
		}
		i++;
	}
	if (obj == env->objs.nb - 1)
		env->objs.curr--;
	env->objs.nb--;
	ft_memdel((void *)&env->objs.obj);
	env->objs.obj = new;
}

void		update_and_copy_a(t_env *env, SDL_Keycode type, t_obj *obj)
{
	t_obj	*new;
	int		i;

	i = -1;
	if (!(new = (t_obj *)malloc(sizeof(t_obj) * (env->objs.nb + 1))))
		error_mgt(0);
	while (++i < env->objs.nb)
		ft_memcpy((void *)&new[i], (void *)&env->objs.obj[i], sizeof(t_obj));
	ft_bzero((void *)&new[i], sizeof(t_obj));
	if (obj == NULL)
	{
		new[i].type = type - 49;
		new[i].o = vect_add(vect_add(env->cams.cam[env->cams.curr].pos,
			vect_mult(env->cams.cam[env->cams.curr].vcam, 2000)),
			vect_mult(env->cams.cam[env->cams.curr].v2cam, -500));
		new[i].norm = env->cams.cam[env->cams.curr].v2cam;
		new[i].radius = (new[i].type == CONE) ? 30 : 150;
		new[i].mat.rough = 1;
		new[i].k_diff = 0.7;
		new[i].col = get_white();
	}
	else
		new[i] = *obj;
	env->objs.nb++;
	env->objs.curr = i;
	ft_memdel((void *)&env->objs.obj);
	env->objs.obj = new;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_and_copy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 00:33:47 by hbouchet          #+#    #+#             */
/*   Updated: 2018/05/04 04:52:19 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			update_and_copy_r(t_env *env, int obj)
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

static t_obj	set_new_obj(t_env *env, SDL_Keycode type)
{
	t_obj	obj;

	obj.type = type - 49;
	obj.o = vect_add(vect_add(env->cams.cam[env->cams.curr].pos,
		vect_mult(env->cams.cam[env->cams.curr].vcam, 2000)),
		vect_mult(env->cams.cam[env->cams.curr].v2cam, -500));
	obj.norm = env->cams.cam[env->cams.curr].v2cam;
	obj.radius = (obj.type == CONE) ? 30 : 150;
	obj.mat.rough = 1;
	obj.k_diff = 0.7;
	obj.k_spec = 0;
	obj.link = 0;
	obj.col = get_white();
	obj.refract = 0;
	obj.reflect = 0;
	return (obj);
}

void			update_and_copy_a(t_env *env, SDL_Keycode type, t_obj *obj)
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
		new[i] = set_new_obj(env, type);
	}
	else
		new[i] = *obj;
	env->objs.nb++;
	env->objs.curr = i;
	ft_memdel((void *)&env->objs.obj);
	env->objs.obj = new;
}

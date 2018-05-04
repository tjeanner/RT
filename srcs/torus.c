/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 00:28:26 by hbouchet          #+#    #+#             */
/*   Updated: 2018/05/04 00:47:58 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_torus(t_obj *obj, int nb)
{
	ft_bzero((void *)obj, sizeof(t_obj));
	obj->type = SPHERE;
	obj->radius = 200;
	obj->mat.rough = 1;
	obj->k_diff = 0.7;
	obj->k_spec = 0;
	obj->link = nb;
	obj->col = get_white();
}

void		create_torus(t_env *env)
{
	int			i;
	static int	nb;
	double		angle;
	t_obj		*new;
	t_v			tmp;

	nb = 1;
	i = -1;
	tmp = vect_mult(env->cams.cam[env->cams.curr].v2cam, 500);
	angle = 5;
	if (!(new = (t_obj *)malloc(sizeof(t_obj) * 1)))
		error_mgt(0);
	while (++i < 360 / angle)
	{
		init_torus(new, nb);
		tmp = rotation(tmp, vect_norm(
			vect_add(env->cams.cam[env->cams.curr].vcam,
			env->cams.cam[env->cams.curr].v2cam)), angle);
		new->o = vect_add(vect_add(env->cams.cam[env->cams.curr].pos,
			vect_mult(env->cams.cam[env->cams.curr].vcam, 8000)),
			tmp);
		update_and_copy_a(env, SDLK_1, new);
	}
	free(new);
	nb++;
}

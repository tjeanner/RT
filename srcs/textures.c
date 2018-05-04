/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 04:00:59 by tjeanner          #+#    #+#             */
/*   Updated: 2018/05/04 04:42:48 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_2nd_vect_planes(t_env *env)
{
	int		i;
	double	tmp;

	i = -1;
	while (++i < env->objs.nb)
	{
		if (env->objs.obj[i].type == PLANE)
		{
			tmp = -1.0 * vect_scal(env->objs.obj->norm, env->objs.obj->o);
			if (env->objs.obj->norm.z != 0 && (env->objs.obj->norm2.y = 1) > 0)
			{
				env->objs.obj->norm2.x = 1;
				env->objs.obj->norm2.z = -1.0 * (2.0 + tmp) /
					env->objs.obj->norm.z;
			}
			else if ((env->objs.obj->norm2.z = 1) == 1)
			{
				env->objs.obj->norm2.x = (env->objs.obj->norm.x != 0) ? -1.0 *
					(2.0 + tmp) / env->objs.obj->norm.x : 1;
				env->objs.obj->norm2.y = (env->objs.obj->norm.x != 0) ? 1 :
					-1.0 * (2.0 + tmp) / env->objs.obj->norm.y;
			}
			env->objs.obj->norm2 = vect_norm(vect_sous(env->objs.obj->norm2,
						env->objs.obj->o));
		}
	}
}

int			get_procedural_text(t_line line, t_obj obj, t_v *res)
{
	t_v		tmp;
	t_v		a;
	double	opti_a;
	double	opti_b;

	tmp = vect_sous(vect_add(line.pos, vect_mult(line.dir, res->z)), obj.o);
	a = vect_norm(obj.norm2);
	opti_b = get_vect_norm(tmp);
	opti_a = opti_b * (vect_scal(a, vect_norm(tmp)));
	opti_b = opti_b *
			(vect_scal(vect_norm(tmp), vect_norm(vect_prod(a, obj.norm))));
	if (((int)fabs(opti_b) % (obj.mat.scale * 2) < obj.mat.scale) ^
		(opti_b < 0.0) ^ ((int)fabs(opti_a) % (obj.mat.scale * 2) <
			obj.mat.scale) ^ (opti_a < 0.0))
		return (0);
	return (1);
}

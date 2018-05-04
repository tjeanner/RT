/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 04:00:59 by tjeanner          #+#    #+#             */
/*   Updated: 2018/05/04 05:15:06 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_v			get_rand_point(t_obj obj, double d)
{
	t_v		tmp;

	if (obj.norm.z != 0 && (tmp.y = 1) > 0)
	{
		tmp.x = 1;
		tmp.z = -1.0 * (2.0 + d) /
			obj.norm.z;
	}
	else if (obj.norm.x != 0 && (tmp.y = 1) > 0)
	{
		tmp.z = 1;
		tmp.x = -1.0 * (2.0 + d) /
			obj.norm.x;
	}
	else if (obj.norm.y != 0 && (tmp.x = 1) > 0)
	{
		tmp.z = 1;
		tmp.y = -1.0 * (2.0 + d) /
			obj.norm.y;
	}
	return (tmp);
}

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
			env->objs.obj->norm2 = vect_norm(vect_sous(get_rand_point(
				env->objs.obj[i], tmp), env->objs.obj->o));
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
	a = vect_norm(tmp);
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

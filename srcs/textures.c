/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 04:00:59 by tjeanner          #+#    #+#             */
/*   Updated: 2018/05/04 04:01:52 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

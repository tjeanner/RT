/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 06:10:04 by cquillet          #+#    #+#             */
/*   Updated: 2018/05/03 06:10:40 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	get_refract_index(t_objs *objs, t_ray *refr, t_ray *line)
{
	t_ray	*tmp;

	if (!line->objs || !line->nb_objs)
		refr->nb_objs = 1;
	else
		refr->nb_objs += (line->objs[line->obj] == IN_OBJ) ? -1 : 1;
	refr->objs = NULL;
	if (!refr->nb_objs)
		return ((refr->n2 = 1.0));
	if ((refr->objs = (char *)malloc(objs->nb * sizeof(char))))
		error_mgt(0);
	if (!line->objs)
	{
		ft_bzero(refr->objs, objs->nb * sizeof(char));
		refr->objs[line->obj] = IN_OBJ;
	}
	else
	{
		ft_memcpy(refr->objs, line->objs, objs->nb * sizeof(char));
		refr->objs[line->obj] = !line->objs[line->obj];
	}
	tmp = line;
	while (tmp && refr->objs[tmp->obj] == OUT_OBJ)
		tmp = tmp->incident;
	return ((refr->n2 = tmp ? objs->obj[tmp->obj].refract : 1.0));
}

t_color			get_refract(t_objs *objs, t_lums *lums, t_ray *line,
																unsigned int d)
{
	t_ray	refr;
	t_color	col;

	refr.from.pos = vect_add(line->to.pos, vect_mult(line->to.dir, -MARGIN));
	refr.n1 = line->n2;
	refr.incident = line;
	refr.total_dist = line->total_dist;
	get_refract_index(objs, &refr, line);
	refr.from.dir = vect_norm(vect_refract(line->from.dir, line->to.dir,
														refr.n1 / refr.n2));
	col = mult_color(get_col(objs, lums, &refr, d),
			objs->obj[line->obj].transp /
			(objs->obj[line->obj].transp + objs->obj[line->obj].reflect));
	col = prod_color(col, objs->obj[line->obj].col);
	if (refr.objs)
		free(refr.objs);
	refr.objs = NULL;
	return (col);
}

t_color		get_reflect(t_objs *objs, t_lums *lums, t_ray *line, unsigned int d)
{
	t_ray	refl;
	t_color	col;

	refl.from.pos = vect_add(line->to.pos, vect_mult(line->to.dir, MARGIN));
	refl.from.dir = vect_norm(vect_reflect(line->from.dir, line->to.dir));
	refl.total_dist = line->total_dist;
	refl.n1 = line->n2;
	refl.n2 = line->n2;
	refl.incident = line;
	refl.objs = line->objs;
	refl.nb_objs = line->nb_objs;
	col = mult_color(get_col(objs, lums, &refl, d), 
			objs->obj[line->obj].reflect /
			(objs->obj[line->obj].transp + objs->obj[line->obj].reflect));
	refl.objs = NULL;
	return (col);
}

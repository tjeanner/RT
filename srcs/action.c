/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 13:16:46 by vmercadi          #+#    #+#             */
/*   Updated: 2018/05/04 03:07:45 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Start the actions for all the objects
*/

void		main_action(t_objs *objs, int play)
{
	int		i;

	i = 0;
	if (play)
		while (i < objs->nb)
			action(&objs->obj[i++]);
}

/*
** To animate the scene we need to
** init_act();
** action();
*/

void		action(t_obj *obj)
{
	if (!obj->act.movedist.x && !obj->act.movedist.x && !obj->act.movedist.x)
	{
		obj->act.movedist.x =
			(obj->act.max.x - obj->act.min.x) / obj->act.speed;
		obj->act.movedist.y =
			(obj->act.max.y - obj->act.min.y) / obj->act.speed;
		obj->act.movedist.z =
			(obj->act.max.z - obj->act.min.z) / obj->act.speed;
		obj->act.angle = 1.0;
		obj->act.p = 0;
	}
	if (obj->act.action <= 0)
		return ;
	if (obj->act.action == 1)
		rotation(obj->norm, obj->act.axis, obj->act.angle);
	else if (obj->act.action == 2)
		act_movaxis(obj);
	else if (obj->act.action == 3)
		obj->col = get_rand();
}

/*
** Move inline of the axe defined and between min and max
*/

void		act_movaxis(t_obj *obj)
{
	t_v		v;
	t_v		axis;
	double	dist;
	double	nb;

	axis = vect_sous(obj->act.max, obj->act.min);
	dist = get_vect_norm(axis);
	axis = vect_norm(axis);
	v = vect_sous(obj->o, obj->act.min);
	nb = get_vect_norm(v);
	if (nb >= dist)
		obj->act.p = 0;
	else if (vect_scal(axis, v) <= 0)
		obj->act.p = 1;
	if (obj->act.p == 1)
		obj->o = vect_add(obj->o, obj->act.movedist);
	else
		obj->o = vect_sous(obj->o, obj->act.movedist);
}

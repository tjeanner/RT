/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 13:16:46 by vmercadi          #+#    #+#             */
/*   Updated: 2018/05/02 20:26:26 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Start the actions for all the objects
*/

void	main_action(t_objs *objs)
{
				// printf("MAIN_ACTION\n");
	int		i;

	i = 0;
	while (i < objs->nb)
		action(&objs->obj[i++]);
}

/*
** Init the action struct
** Action : 1 = Ellipse | 2 = axe	| 3 = color
*/

t_act	init_act(int action, t_v axis, int speed, t_v maxmin[2])
{
	t_act	act;
	t_v		movedist;

	act.action = action;
	act.speed = speed;
	act.min = maxmin[0];
	act.max = maxmin[1];
	act.axis = axis;
	act.angle = 1.0;
	act.p = 0;
	movedist.x = (maxmin[1].x - maxmin[0].x) / speed;
	movedist.y = (maxmin[1].y - maxmin[0].y) / speed;
	movedist.z = (maxmin[1].z - maxmin[0].z) / speed;
	act.movedist = movedist;
	return (act);
}

/*
** To animate the scene we need to
** init_act();
** action();
*/

void		action(t_obj *obj)
{
	if (obj->act.action <= 0)
		return ;
	if (obj->act.action == 1)
		rotation(obj->norm, obj->act.axis, obj->act.angle);
	else if (obj->act.action == 2)
		act_movaxis(obj);
	else if (obj->act.action == 3)
		act_color(obj);
}

/*
** Move inline of the axe defined and between min and max
*/

void		act_movaxis(t_obj *obj)
{
	t_v tmp;

	if (vect_equal(obj->act.min, obj->act.max))
	{
		tmp = obj->act.min;
		obj->act.min = obj->act.max;
		obj->act.max = tmp;
		obj->act.p = 0;
	}
	else
		obj->act.p = 1;
	if (obj->act.p == 1)
		vect_add(obj->o, obj->act.movedist);
	else
		vect_sous(obj->o, obj->act.movedist);
}

/*
** To change the color
*/

void		act_color(t_obj *obj)
{
	obj->col.c.r = (double)rand() / (double)RAND_MAX;
	obj->col.c.g = (double)rand() / (double)RAND_MAX;
	obj->col.c.b = (double)rand() / (double)RAND_MAX;
}

/*
** Compare 2 vect, return 1 if they are equals
*/

int		vect_equal(t_v v1, t_v v2)
{
	if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)
		return (1);
	return (0);
}

























/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useles_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 00:39:43 by tjeanner          #+#    #+#             */
/*   Updated: 2018/01/22 00:50:01 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_env	*fill_env(t_env *env)
{
	env->flou = 2;
	env->pos_cam.x = 0;
	env->pos_cam.y = 0;
	env->pos_cam.z = -1000;
	env->vcam.x = 0;
	env->vcam.y = 0;
	env->vcam.z = 1;
	env->v2cam.x = 0;
	env->v2cam.y = 1;
	env->v2cam.z = 0;
	env->pos_lum.x = 0;
	env->pos_lum.y = 1000;
	env->pos_lum.z = -554;
	env->sphere.type = 's';
	env->sphere.o.x = 0;
	env->sphere.o.y = 0;
	env->sphere.o.z = 800;
	env->sphere.radius = 800;
	env->sphere.col.c.r = 255;
	env->sphere.col.c.g = 255;
	env->sphere.col.c.b = 255;
	env->sphere.col.c.a = 0;
	ft_memcpy(&env->objs[0], &env->sphere, sizeof(t_sphere));
	env->sphere2.type = 's';
	env->sphere2.o.x = 0;
	env->sphere2.o.y = 0;
	env->sphere2.o.z = 50;
	env->sphere2.radius = 300;
	env->sphere2.col.c.r = 255;
	env->sphere2.col.c.g = 0;
	env->sphere2.col.c.b = 0;
	env->sphere2.col.c.a = 0;
	ft_memcpy(&env->objs[1], &env->sphere2, sizeof(t_sphere));
	env->sphere3.type = 's';
	env->sphere3.o.x = 0;
	env->sphere3.o.y = -300;
	env->sphere3.o.z = 200;
	env->sphere3.radius = 250;
	env->sphere3.col.c.r = 0;
	env->sphere3.col.c.g = 255;
	env->sphere3.col.c.b = 0;
	env->sphere3.col.c.a = 0;
	ft_memcpy(&env->objs[2], &env->sphere3, sizeof(t_sphere));
	env->plan.type = 'p';
	env->plan.o.x = 2000;
	env->plan.o.y = 0;
	env->plan.o.z = 0;
	env->plan.colo.x = -1;
	env->plan.colo.y = 0;
	env->plan.colo.z = 0;
	env->plan.norm.x = -1;
	env->plan.norm.y = 0;
	env->plan.norm.z = 0;
	ft_memcpy(&env->objs[3], &env->plan, sizeof(t_sphere));
	env->plan2.type = 'p';
	env->plan2.o.x = 0;
	env->plan2.o.y = 0;
	env->plan2.o.z = 1500;
	env->plan2.colo.x = 0;
	env->plan2.colo.y = 1;
	env->plan2.colo.z = 1;
	env->plan2.norm.x = 0;
	env->plan2.norm.y = 1;
	env->plan2.norm.z = 1;
	ft_memcpy(&env->objs[4], &env->plan2, sizeof(t_sphere));
	env->sphere3.type = 't';
	env->sphere3.o.x = 0;
	env->sphere3.o.y = -500;
	env->sphere3.o.z = 200;
	env->sphere3.radius = 350;
	env->sphere3.norm.x = 400;
	env->sphere3.norm.y = -500;
	env->sphere3.norm.z = 0;
	env->sphere3.colo.x = 1;
	env->sphere3.colo.y = 0;
	env->sphere3.colo.z = 1;
	ft_memcpy(&env->objs[5], &env->sphere3, sizeof(t_sphere));
	env->sphere3.type = 'c';
	env->sphere3.o.x = 0;
	env->sphere3.o.y = -500;
	env->sphere3.o.z = 200;
	env->sphere3.radius = 550;
	env->sphere3.norm.x = 400;
	env->sphere3.norm.y = 200;
	env->sphere3.norm.z = 0;
	env->sphere3.colo.x = 0;
	env->sphere3.colo.y = 1;
	env->sphere3.colo.z = 0;
	ft_memcpy(&env->objs[6], &env->sphere3, sizeof(t_sphere));
	env->nb_obj = 7;
	return (env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_json.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:58:18 by hbouchet          #+#    #+#             */
/*   Updated: 2018/03/14 11:06:07 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "rtv1.h"

int		j_is_valid_obj(t_obj *obj)
{
	if (!obj->type || obj->col.color > 16777215)
		return (0);
	if (obj->type != 's' && !vect_norm(obj->norm))
		return (0);
	if (obj->type != 'p' && obj->radius <= 0)
		return (0);
	return (1);
}

int		j_is_valid_cam(t_cam *cam)
{
	if (vect_scal_prod(cam->vcam, cam->v2cam))
		return (0);
	if (!vect_norm(cam->vcam) && !vect_norm(cam->v2cam))
		return (0);
	return (1);
}

int		j_is_valid_lum(t_lum *lum)
{
	if (lum->col.color > 16777215)
		return (0);
	return (1);
}
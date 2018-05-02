/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_cam.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 15:43:40 by hbouchet          #+#    #+#             */
/*   Updated: 2018/05/02 16:12:56 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		j_get_cam(t_json_arr *tab, t_cam *cam, t_par *par, t_env *env)
{
	t_json_arr	*p;
	t_json		*po;

	p = tab;
	while (p && (po = p->val.data.obj) != NULL)
	{
		ft_bzero(cam, sizeof(t_cam));
		while (po)
		{
			if (!ft_strcmp(po->key, "color") && po->val.type == TYPE_STRING)
				cam->col = j_get_color(po);
			else if (!ft_strcmp(po->key, "pos") && po->val.type == TYPE_OBJ)
				cam->pos = j_get_vec(po);
			else if (!ft_strcmp(po->key, "v") && po->val.type == TYPE_OBJ)
				cam->vcam = j_get_vec(po);
			else if (!ft_strcmp(po->key, "v2") && po->val.type == TYPE_OBJ)
				cam->v2cam = j_get_vec(po);
			else
				error_mgt(3);
			po = po->next;
		}
		if (j_is_valid_cam(cam) && ++env->cams.nb)
			ft_lstadd(&par->lst_cam, ft_lstnew(cam, sizeof(t_cam)));
		p = p->next;
	}
}

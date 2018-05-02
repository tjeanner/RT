/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 15:41:55 by hbouchet          #+#    #+#             */
/*   Updated: 2018/05/02 16:52:11 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	j_prep_light(t_json *obj, t_lum *lum)
{
	ft_bzero(lum, sizeof(t_lum));
	lum->coef = 0.4;
	while (obj)
	{
		if (!ft_strcmp(obj->key, "color") && obj->val.type == TYPE_STRING)
			lum->col = j_get_color(obj);
		else if (!ft_strcmp(obj->key, "pos") && obj->val.type == TYPE_OBJ)
			lum->pos = j_get_vec(obj);
		else if (!ft_strcmp(obj->key, "dir") && obj->val.type == TYPE_OBJ)
			lum->dir = j_get_vec(obj);
		else if (!ft_strcmp(obj->key, "intensity")
			&& obj->val.type == TYPE_DOUBLE)
		{
			lum->coef = fmin(1, fmax(obj->val.data.nb, 0));
		}
		else if (!ft_strcmp(obj->key, "type") && obj->val.type == TYPE_STRING)
		{
			if (ft_strcmp(obj->val.data.str, "PARALLEL"))
				ft_bzero((void *)&lum->dir, sizeof(t_v));
		}
		else
			error_mgt(2);
		obj = obj->next;
	}
}

void		j_get_lights(t_json_arr *tab, t_lum *lum, t_par *par, t_env *env)
{
	t_json_arr	*p;
	t_json		*po;

	p = tab;
	while (p)
	{
		po = p->val.data.obj;
		j_prep_light(po, lum);
		if (j_is_valid_lum(lum))
		{
			ft_lstadd(&par->lst_lum, ft_lstnew(lum, sizeof(t_lum)));
			env->lums.nb++;
		}
		p = p->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_valid_json.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 09:58:18 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/30 23:12:21 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			j_is_valid_obj(t_obj *obj)
{
	if (obj->type == NONE || obj->col.color > 16777215)
		return (0);
	if (obj->type != SPHERE && !get_vect_norm(obj->norm))
		return (0);
	if (obj->type != PLANE && obj->radius <= 0)
		return (0);
	return (1);
}

int			j_is_valid_cam(t_cam *cam)
{
	if (vect_scal(cam->vcam, cam->v2cam))
		return (0);
	if (!get_vect_norm(cam->vcam) && !get_vect_norm(cam->v2cam))
		return (0);
	return (1);
}

int			j_is_valid_lum(t_lum *lum)
{
	if (lum->col.color > 16777215)
		return (0);
	return (1);
}

int			brackets(char *str, int len)
{
	char	tab[len];
	int		i;
	int		j;
	int		cpt;

	i = -1;
	j = -1;
	cpt = 0;
	while (str[++i])
		if (str[i] == '"')
			cpt++;
		else if (str[i] == '[' || str[i] == '(' || str[i] == '{')
			tab[++j] = str[i];
		else if (str[i] == ']' || str[i] == ')' || str[i] == '}')
		{
			if ((tab[j] == '[' && str[i] == ']')
				|| (tab[j] == '{' && str[i] == '}')
				|| (tab[j] == '(' && str[i] == ')'))
				j--;
			else
				return (0);
		}
	return ((j != -1 || cpt % 2) ? 0 : 1);
}

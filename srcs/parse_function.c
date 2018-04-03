/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 14:29:16 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/03 21:23:18 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char		*parse_str(char **str)
{
	char	*tmp;

	*str += 1;
	tmp = ft_strsub(*str, 0, (ft_strchr(*str, '"') - *str));
	*str += (ft_strchr(*str, '"') - *str) + 1;
	skip_whitespaces(str);
	return (tmp);
}

float		parse_float(char **str)
{
	int		cpt;
	float	nb;

	cpt = 0;
	nb = ft_atof(*str);
	*str += 1;
	while ((**str == '.' && cpt == 0) || (**str >= '0' && **str <= '9'))
	{
		if (**str == '.')
			cpt++;
		*str += 1;
	}
	return (nb);
}

void		skip_whitespaces(char **str)
{
	while (**str == ' ' || **str == '\t' || **str == '\n')
		*str += 1;
}

int			init_json(t_json **json)
{
	if (!(*json = malloc(sizeof(t_json) * 1)))
		ft_put_err("Malloc error");
	(*json)->next = NULL;
	(*json)->key = NULL;
	return (0);
}

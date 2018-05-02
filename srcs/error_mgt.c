/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mgt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 12:02:56 by hbouchet          #+#    #+#             */
/*   Updated: 2018/05/01 02:00:18 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		*error_mgt(int status)
{
	if (status == 0)
		ft_put_err("malloc error");
	else if (status == 1)
		ft_put_err("invalid json");
	else if (status == 2)
		ft_put_err("invalid light");
	else if (status == 3)
		ft_put_err("invalid camera");
	else if (status == 4)
		ft_put_err("invalid vector");
	else if (status == 5)
		ft_put_err("invalid object");
	else if (status == 6)
		ft_put_err("usage : ./rtv1 <scene.json>");
	else if (status == 7)
		ft_put_err("error in init");
	else if (status == 8)
		ft_put_err("failed to init sdl");
	else if (status == 9)
		ft_put_err("invalid scene");
	else
		ft_put_err("error");
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mgt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 12:02:56 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/18 12:58:39 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		error_mgt(int status)
{
	if (status == 1)
		ft_put_err("invalid json");
	else if (status == 2)
		ft_put_err("invalid light");
	else if (status == 3)
		ft_put_err("invalid camera");
	else if (status == 4)
		ft_put_err("invalid vector");
	else if (status == 5)
		ft_put_err("invalid object");
	else
		ft_put_err("error");
}
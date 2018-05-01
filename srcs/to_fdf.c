/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 22:14:22 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/24 15:52:59 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** To create a FDF map of the actual scene of RT
*/

void	to_fdf(t_b *b, char *name)
{
	int	fd;
	int i;
	int j;

	if ((fd = open(name, O_RDONLY | O_WRONLY | O_CREAT)) < 0)
		error_quit(2);
	i = 0;
	while (i < b->winy)
	{
		j = 0;
		while (j < b->winx)
		{
			ft_putnbr_fd((int)b->tab_px[i][j].dist, fd);
			ft_putchar_fd(',', fd);
			ft_putnbr_fd(col2int(b->tab_px[i][j].col), fd);
			ft_putchar_fd(' ', fd);
			j += b->aliasing;
		}
		i += b->aliasing;
		ft_putchar_fd('\n', fd);
	}
	close(fd);
}

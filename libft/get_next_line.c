/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 17:27:10 by hbouchet          #+#    #+#             */
/*   Updated: 2017/12/23 02:07:15 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_next_line(const int fd, char **line)
{
	static char	*rest[OPEN_MAX];
	t_gnl		gnl;

	gnl.ret = 1;
	if (fd < 0 || !line || !BUFF_SIZE || fd > OPEN_MAX)
		return (-1);
	if (!rest[fd])
		rest[fd] = ft_strnew(0);
	while (gnl.ret > -1)
	{
		if ((gnl.tmp = ft_strchr(rest[fd], '\n'))
			|| ((gnl.tmp = ft_strchr(rest[fd], '\0')) && !gnl.ret))
		{
			*gnl.tmp = '\0';
			*line = ft_strdup(rest[fd]);
			ft_memmove(rest[fd], gnl.tmp + 1, ft_strlen(gnl.tmp + 1) + 1);
			rest[fd] = (!gnl.ret) ? ft_strdel(&rest[fd]) : rest[fd];
			return (!line[0][0] && gnl.ret == 0) ? 0 : 1;
		}
		if ((gnl.ret = read(fd, gnl.buf, BUFF_SIZE)) == -1)
			return (-1);
		gnl.buf[gnl.ret] = '\0';
		rest[fd] = ft_strjoinfree(rest[fd], gnl.buf, 'L');
	}
	return (-1);
}

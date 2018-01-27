/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 11:39:00 by tjeanner          #+#    #+#             */
/*   Updated: 2017/10/10 11:50:23 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_read_line(int fd, char *str, int *eof, int *cpt)
{
	char	*buff;
	char	*buff2;

	if ((buff = (char *)(malloc(sizeof(char) * (BUFF_SIZE + 1)))) == NULL)
		return (NULL);
	*eof = read(fd, buff, BUFF_SIZE);
	*cpt += (*eof != 0) ? 1 : 0;
	buff[*eof] = '\0';
	buff2 = str;
	str = ft_strjoin(str, buff);
	ft_strdel(&buff2);
	free(buff);
	return (str);
}

static int	ft_get_line(char *tmp, char *p_tmp, char **line)
{
	if ((p_tmp = ft_strchr(tmp, '\n')))
	{
		*p_tmp = '\0';
		*line = ft_strdup(tmp);
		ft_memmove(tmp, p_tmp + 1, ft_strlen(p_tmp + 1) + 1);
		return (1);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char	*tmp = NULL;
	char		*p_tmp;
	int			eof;
	int			cpt;

	if ((cpt = 0) != -1 && (!line || fd < 0 || BUFF_SIZE < 1))
		return (-1);
	eof = 1;
	p_tmp = NULL;
	tmp = (tmp == NULL) ? ft_strnew(0) : tmp;
	while (eof > 0)
	{
		if (ft_get_line(tmp, p_tmp, line))
			return (1);
		tmp = ft_read_line(fd, tmp, &eof, &cpt);
	}
	*line = ft_strdup(tmp);
	if (ft_strlen(tmp) > 1 && eof == 0)
	{
		ft_memmove(tmp, "\0", ft_strlen(tmp));
		return (1);
	}
	if (eof == -1)
		return (-1);
	return ((cpt != 0) ? 1 : 0);
}

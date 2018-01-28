/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 10:17:49 by tjeanner          #+#    #+#             */
/*   Updated: 2018/01/28 00:26:18 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strjoin_f(char **s1, char *s2)
{
	char	*tmp;

	if (*s1)
	{
		if (!(tmp = ft_strdup(*s1)))
			return (0);
		free(*s1);
		if (!(*s1 = ft_strjoin(tmp, s2)))
			return (0);
		free(tmp);
	}
	else if (!(*s1 = ft_strdup(s2)))
		return (0);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char		*rest = NULL;
	char			buf[BUFF_SIZE + 1];
	int				rd;
	char			*pos;

	if (fd < 0 || BUFF_SIZE <= 0 || !line)
		return (-1);
	rd = BUFF_SIZE;
	if (!(*line = (rest) ? ft_strdup(rest) : NULL) && rest)
		return (-1);
	if (rest)
		free(rest);
	while (!(pos = (*line) ? ft_strchr(*line, EOL) : NULL) && rd != 0)
	{
		if ((rd = read(fd, buf, BUFF_SIZE)) < 0)
			return (-1);
		buf[rd] = '\0';
		if (!ft_strjoin_f(line, buf))
			return (-1);
	}
	if (pos && !(*pos = '\0'))
		rest = ft_strdup(pos + 1);
	else
		rest = (!pos && rest) ? NULL : rest;
	return (rd = (ft_strlen(*line) || pos) ? 1 : 0);
}

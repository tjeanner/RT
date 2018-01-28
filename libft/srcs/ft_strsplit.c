/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 03:22:11 by hbouchet          #+#    #+#             */
/*   Updated: 2017/09/21 23:15:55 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_epurstr(const char **str, char c)
{
	while (**str == c)
		*str = *str + 1;
}

static int	ft_nb_words(const char *str, char c)
{
	int		i;
	int		result;

	i = 0;
	result = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			result++;
		i++;
	}
	return (result);
}

static int	ft_strlenc(const char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**array;
	int		nb_words;
	size_t	size;
	int		i;
	size_t	j;

	if (!s || !c)
		return (NULL);
	i = -1;
	nb_words = ft_nb_words(s, c);
	if (!(array = (char **)malloc(sizeof(*array) * (nb_words + 1))))
		return (NULL);
	while (++i < nb_words)
	{
		ft_epurstr(&s, c);
		size = ft_strlenc(s, c);
		if (!(array[i] = (char *)malloc(sizeof(char) * (size + 1))))
			return (NULL);
		j = -1;
		while (++j < size)
			array[i][j] = *s++;
		array[i][j] = '\0';
	}
	array[i] = NULL;
	return (array);
}

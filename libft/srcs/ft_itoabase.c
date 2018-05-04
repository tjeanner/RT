/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 00:22:34 by hbouchet          #+#    #+#             */
/*   Updated: 2018/05/04 07:22:26 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_base_array(char *tab, int base)
{
	int			i;

	i = -1;
	while (++i < base)
	{
		if (i < 10)
			tab[i] = '0' + i;
		else
			tab[i] = 'a' + i - 10;
	}
	tab[i] = '\0';
	return (tab);
}

static size_t	ft_len(int nbr, int base)
{
	size_t		strlen;

	strlen = 1;
	while (nbr /= base)
		strlen++;
	return (strlen);
}

char			*ft_itoabase(int n, int base)
{
	char		*str;
	int			nbr;
	char		*tab;
	size_t		str_len;

	if (!(tab = (char *)malloc(sizeof(char) * base + 1)))
		return (NULL);
	tab = ft_base_array(tab, base);
	str_len = ft_len(n, base);
	nbr = n;
	if (n < 0)
	{
		nbr = -n;
		str_len++;
	}
	if (!(str = (char *)malloc(sizeof(char) * str_len + 1)))
		return (NULL);
	str[str_len--] = '\0';
	str[str_len] = tab[nbr % base];
	while (nbr /= base)
		str[--str_len] = tab[nbr % base];
	if (n < 0)
		str[0] = '-';
	return (str);
}

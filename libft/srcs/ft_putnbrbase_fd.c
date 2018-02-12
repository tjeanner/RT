/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 04:28:29 by hbouchet          #+#    #+#             */
/*   Updated: 2018/02/12 09:20:47 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_base_array(char *tab, int base)
{
	int		i;

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

void		ft_putnbrbase_fd(int n, int base, int fd)
{
	char	*tab;

	tab = (char *)malloc(sizeof(char) * base + 1);
	if (n == -2147483648)
	{
		ft_putnbrbase_fd(n / base, base, fd);
		return (ft_putnbrbase_fd(n % base * -1, base, fd));
	}
	tab = ft_base_array(tab, base);
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n < base)
		ft_putchar_fd(tab[n], fd);
	else
	{
		ft_putnbrbase_fd(n / base, base, fd);
		ft_putnbrbase_fd(n % base, base, fd);
	}
	free(tab);
}

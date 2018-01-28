/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 23:49:03 by hbouchet          #+#    #+#             */
/*   Updated: 2016/11/23 04:18:47 by hbouchet         ###   ########.fr       */
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

void		ft_putnbrbase(int n, int base)
{
	char	*tab;

	tab = (char *)malloc(sizeof(char) * base + 1);
	if (n == -2147483648)
	{
		ft_putnbrbase(n / base, base);
		return (ft_putnbrbase(n % base * -1, base));
	}
	tab = ft_base_array(tab, base);
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n < base)
		ft_putchar(tab[n]);
	else
	{
		ft_putnbrbase(n / base, base);
		ft_putnbrbase(n % base, base);
	}
	free(tab);
}

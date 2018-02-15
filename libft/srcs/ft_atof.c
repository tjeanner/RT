/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeanner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 01:24:43 by tjeanner          #+#    #+#             */
/*   Updated: 2018/02/15 10:48:28 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_atof(char *s)
{
	int		i;
	int		j;
	int		neg;
	double	res;

	neg = 1;
	res = (double)atoi(s);
	if (ft_strchr(s, '.') && (i = ft_strchr(s, '.') - s) != 0)
	{
		j = 1;
		if (s[0] == '-')
			neg = -1;
		while (s[++i] && ft_isdigit(s[i]))
		{
			res += (res >= 0) ? ((double)(s[i] - '0') * ft_pow(10, 0 - j)) :
				-1.0 * ((double)(s[i] - '0') * ft_pow(10, 0 - j));
			j++;
		}
	}
	return (res * (double)neg);
}

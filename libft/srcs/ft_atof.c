/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 01:24:43 by tjeanner          #+#    #+#             */
/*   Updated: 2018/04/14 02:35:37 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

double		ft_atof(char *s)
{
	int		i;
	int		len;
	int		j;
	int		neg;
	double	res;

	neg = 0;
	len = 0;
	while ((s[++len] >= '0' && s[len] <= '9') || (s[len] == '.' && neg == 0))
		if (s[len] == '.')
			neg++;
	res = (double)ft_atoi(s);
	if (ft_strchr(s, '.') && (i = ft_strchr(s, '.') - s) != 0 && i < len)
	{
		j = 1;
		neg = (s[0] == '-') ? -1 : 1;
		while (s[++i] && ft_isdigit(s[i]))
		{
			res += (neg == 1) ? ((double)(s[i] - '0') * ft_pow(10, 0 - j)) :
				((double)-1.00 * (s[i] - '0') * ft_pow(10, 0 - j));
			j++;
		}
	}
	return (res);
}

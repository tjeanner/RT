/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 22:31:53 by hbouchet          #+#    #+#             */
/*   Updated: 2016/11/23 05:34:00 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while ((little[j] != '\0') && (big[i + j] != '\0')
		&& (big[i + j] == little[j]))
			j++;
		if (little[j] == '\0' && i + j <= len)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}

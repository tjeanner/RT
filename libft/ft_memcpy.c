/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 21:12:42 by hbouchet          #+#    #+#             */
/*   Updated: 2016/11/23 05:27:12 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*ptr_dst;
	char const	*ptr_src;

	ptr_dst = (char *)dst;
	ptr_src = (char const *)src;
	i = 0;
	while (i < n)
	{
		i++;
		*ptr_dst++ = *ptr_src++;
	}
	return (dst);
}

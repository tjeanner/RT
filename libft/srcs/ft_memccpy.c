/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 22:00:51 by hbouchet          #+#    #+#             */
/*   Updated: 2016/11/23 05:26:36 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*ptr_dst;
	unsigned char		*ptr_src;

	ptr_dst = (unsigned char *)dst;
	ptr_src = (unsigned char *)src;
	while (n--)
	{
		*ptr_dst = *ptr_src;
		if (*ptr_src == (unsigned char)c)
			return (ptr_dst + 1);
		ptr_dst++;
		ptr_src++;
	}
	return (NULL);
}

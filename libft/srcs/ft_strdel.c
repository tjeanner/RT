/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 02:30:38 by hbouchet          #+#    #+#             */
/*   Updated: 2016/11/17 00:57:47 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdel(char **ass)
{
	if (!ass)
		return (NULL);
	ft_memdel((void **)ass);
	*ass = NULL;
	return (*ass);
}

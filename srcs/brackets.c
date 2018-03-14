/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 07:51:42 by hbouchet          #+#    #+#             */
/*   Updated: 2018/03/14 11:08:02 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			brackets(char *str, int len)
{
	char    tab[len];
    int     i = 0;
    int     j = -1;
    int     cpt = 0;

    while (str[i])
    {
        if (str[i] == '"')
            cpt++;
        else if (str[i] == '[' || str[i] == '(' || str[i] == '{')
            tab[++j] = str[i];
        else if (str[i] == ']' || str[i] == ')' || str[i] == '}')
        {
            if ((tab[j] == '[' && str[i] == ']')
                || (tab[j] == '{' && str[i] == '}')
                || (tab[j] == '(' && str[i] == ')'))
                j--;
            else
                return (0);
        }
        i++;
    }
    if (j != -1 || cpt % 2)
		return (0);
    else
        return (1);
}
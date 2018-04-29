/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:41:19 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/28 15:14:36 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UTILS_H
# define __UTILS_H

typedef struct			s_v
{
	double				x;
	double				y;
	double				z;
}						t_v;

/*
** struct for a basic list of vectors
*/

typedef struct				s_vl
{
	t_v						v;
	int						id;
	struct s_vl				*next;
}							t_vl;

/*
** Color struct
*/

typedef struct				s_col
{
	double					r;
	double					g;
	double					b;
}							t_col;

/*
**	Pixel struct
*/

typedef struct				s_px
{
	int						id;
	int						x;
	int						y;
	t_col					col;
	double					dist;
}							t_px;

/*
** Struct for a 3x3 matrice
*/

typedef struct				s_matrice
{
	double					data[3][3];
}							t_matrice;

#endif
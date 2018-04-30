/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:32:18 by cquillet          #+#    #+#             */
/*   Updated: 2017/10/23 17:11:28 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_H
# define QUATERNION_H

# ifndef TYPEDEF_CPLX
#  define TYPEDEF_CPLX

typedef long double t_re;
typedef long double t_im;

# endif

typedef struct	s_quat
{
	t_re		r;
	t_re		i;
	t_re		j;
	t_re		k;
}				t_quat;

t_quat			quat_conj(t_quat x);
t_re			quat_mod(t_quat x);
t_quat			quat_scalar(t_quat x, t_re a);
t_quat			quat_inv(t_quat x);

t_quat			quat_add(t_quat x, t_quat y);
t_quat			quat_mul(t_quat x, t_quat y);
t_quat			quat_div(t_quat x, t_quat y);

void			quat_print(t_quat q);

#endif

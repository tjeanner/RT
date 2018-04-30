/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_vector.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquillet <cquillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 12:18:55 by cquillet          #+#    #+#             */
/*   Updated: 2017/10/23 17:13:09 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUAT_VECTOR_H
# define QUAT_VECTOR_H

# include "quaternion.h"
# include "vector.h"

t_quat		vect_to_quat(t_re a, t_vector v);
t_vector	quat_to_vect(t_quat q);
t_quat		quat_rot(t_vector axis, t_re angle);
t_vector	vect_rot(t_vector v, t_quat rot);

#endif

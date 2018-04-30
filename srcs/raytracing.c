/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 19:12:29 by tjeanner          #+#    #+#             */
/*   Updated: 2018/04/30 20:01:35 by cquillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray			init_line(double x, double y, t_cam cam)
{
	t_ray	ray;

	ray.from.dir = vect_norm(vect_add(vect_mult(cam.vcam, DIST),
				vect_add(vect_mult(vect_inv(cam.v3cam),
						(double)((x - WIN_X / 2.0) / get_vect_norm(cam.v3cam))),
					vect_mult(cam.v2cam, (double)((WIN_Y / 2.0 - y) /
							get_vect_norm(cam.v2cam))))));
	ray.from.pos = cam.pos;
	ray.dist = 0.0;
	ray.total_dist = 0.0;
	ray.obj = -1;
//	ray.objs = ft_lstnew(&ray.obj, sizeof(int));
	ray.n2 = 1.0;
	ray.incident = NULL;
	ray.objs = NULL;
	ray.nb_objs = 0;
	return (ray);
}

t_v			get_norm(t_obj obj, t_ray *line)
{
	double	res;
	t_v		vect;

	obj.norm = vect_norm(obj.norm);
	if (obj.type == PLANE)
		vect = obj.norm;
	else
		vect = vect_sous(line->to.pos, obj.o);
	if (obj.type == CONE || obj.type == CYLINDRE)
	{
		res = vect_scal(vect, obj.norm);
		if (obj.type == CONE)
			res *= (1.0 + pow(tan(obj.radius * TORAD), 2.0));
		vect = vect_sous(vect, vect_mult(obj.norm, res));
	}
	else if (obj.type == 'd')
	{
		res = vect_scal(vect, obj.norm);
		vect = vect_sous(line->to.pos, vect_mult(obj.norm, res));
		res = sqrt(obj.radius2 * obj.radius2 - res * res);
		vect = vect_norm(vect_sous(
					vect_sous(line->to.pos, vect),
					vect_mult(vect_sous(obj.o, vect), res / (obj.radius + res))
					));
	}
	return (vect_norm(vect_scal(vect, line->from.dir) > 0.000 ? vect_inv(vect) : vect));
//	return (vect = (obj.type == 'p' && vect_scal(vect, line->from.dir) > 0.000)
//			? vect_norm(vect_inv(vect)) : vect_norm(vect));
}

int			which_obj_col(t_objs *objs, t_ray *line)
{
	double	tmp;
	double	tutu;
	int		i;
	int		ob;

	//line->prev_obj = line->obj;
	line->total_dist += line->dist;
	i = -1;
	tmp = -1.0;
	while (++i < objs->nb)
	{
		if (objs->col_fcts[(int)objs->obj[i].type]
				(line->from, objs->obj[i], &tutu) == 1 && (i == 0 || (tutu > 0.0 &&
							(tmp == -1.0 || tmp > tutu))) && (ob = i) == i)
				tmp = tutu;
	}
	if (tmp < 0.0 || objs->nb == 0)
		return (0);
	line->obj = ob;
	line->to.pos = vect_add(line->from.pos, vect_mult(line->from.dir, tmp));
	line->to.dir = get_norm(objs->obj[ob], line);
	line->dist += tmp;
	return (1);
}

t_color		get_lum(t_objs *objs, int obj, t_lum lum, t_ray *line)
{
	int		i;
	t_v		col_2_lum;
	double	res;
	double	tmp;
	t_ray	tutu;

	col_2_lum = vect_sous(lum.pos, line->to.pos);
	tmp = get_vect_norm(col_2_lum);
	tutu.from.dir = vect_norm(col_2_lum);
	tutu.from.pos = vect_add(line->to.pos, vect_mult(line->to.dir, 0.00000001));
	i = -1;
	while (++i < objs->nb && (res = -1.0) < 0)
		if (objs->col_fcts[(int)objs->obj[i].type](tutu.from, objs->obj[i], &res) == 1 &&
				(((res > 0.0 && res < tmp))))
			return (get_black());
	res = fmax(0.0, vect_scal(line->to.dir, tutu.from.dir));
	return (mult_color(objs->obj[obj].col, res));
}

t_color		get_reflect(t_objs *objs, t_lums *lums, t_ray *line, unsigned int d)
{
	t_ray	refl;
	t_color	col;

	refl.from.pos = vect_add(line->to.pos, vect_mult(line->to.dir, 0.00000001));
	refl.from.dir = vect_norm(vect_reflect(line->from.dir, line->to.dir));
	refl.total_dist = line->total_dist;
	refl.n1 = line->n2;
	refl.n2 = line->n2;
	refl.incident = line;
	refl.objs = line->objs;
	refl.nb_objs = line->nb_objs;
	col = mult_color(get_col(objs, lums, &refl, d), objs->obj[line->obj].reflect);
	refl.objs = NULL;
	return (col);
}

t_color		get_refract(t_objs *objs, t_lums *lums, t_ray *line, unsigned int d)
{
	t_ray	refr;
//	double	k;
	t_ray	*tmp;
	t_color	col;

	refr.from.pos = vect_add(line->to.pos, vect_mult(line->to.dir, -0.00000001));
	refr.n1 = line->n2;
	refr.incident = line;
	refr.total_dist = line->total_dist;
	if (!line->objs)
		refr.nb_objs = 1;
	else
		refr.nb_objs += (line->objs[line->obj] == IN_OBJ) ? -1 : 1;
	refr.objs = NULL;
	if (refr.nb_objs > 0)
	{
		refr.objs = (char *)malloc(objs->nb * sizeof(char));
		if (!line->objs)
		{
			ft_bzero(refr.objs, objs->nb * sizeof(char));
			refr.objs[line->obj] = IN_OBJ;
		}
		else
		{
			ft_memcpy(refr.objs, line->objs, objs->nb *sizeof(char));
			refr.objs[line->obj] = !line->objs[line->obj];
		}
	}
	if (!refr.objs)
		refr.n2 = 1.0;
	else
	{
		tmp = line;
		while (tmp && refr.objs[tmp->obj] == OUT_OBJ)
			tmp = tmp->incident;
		refr.n2 = objs->obj[tmp->obj].refract;
	}
	refr.from.dir = vect_norm(vect_refract(line->from.dir, line->to.dir, refr.n1 / refr.n2));
	col = mult_color(get_col(objs, lums, &refr, d), objs->obj[line->obj].transp);
	if (refr.objs)
		free(refr.objs);
	refr.objs = NULL;
	return (col);
}

void		calc_refract(t_objs *objs, t_ray *line)
{
//	t_list	*l;
	t_list	*tmp;
	int		*id;

//	l = line->objs;
	tmp = NULL;
	id = NULL;
/*	while (l)
	{
		id = l->content;
		if (id && *id == line->obj)
			break;
		tmp = l;
		l = l->next;
		id = NULL;
	}*/
	if (!objs)
	line->n1 = line->n2;
/*	if (!l || !id)
	{
		l = ft_lstnew(&line->obj, sizeof(int));
		l->next = line->objs;
		line->objs = l;
		line->n2 = objs->obj[line->obj].refract;
	}
	else
	{
		if (l == line->objs)
			line->objs = line->objs->next;
		else
			tmp->next = l->next;
		id = line->objs->content;
		line->n2 = id ? objs->obj[*id].refract : 1.0;
		free(l->content);
		free(l);
	}
	l = line->objs;
	while (l)
	{
		id = l->content;
		if (id)
			printf("%d: %f ->\n", *id , objs->obj[line->obj].refract);
		l = l->next;
	}*/
}

t_color		next_rays(t_objs *objs, t_lums *lums, t_ray *line, unsigned int d)
{
	t_color	col;
	double	k;
	double	r[3];
	double	c[2];

	//TO_DO chercher les objets les plus proches qui ont de la refraction
	col = get_black();
	if (!d || !objs || !lums || !line || !line->objs)
		return (col);
//	calc_refract(objs, line);
	r[2] = 0.0;
	c[0] = 0.0;
	k = 0.;
	if (objs->obj[line->obj].transp > 0.0)
	{
//		if (line->prev_obj == line->obj)
//			line->n2 = 1.0;
		k = line->n1 / line->n2;
		c[0] = -vect_scal(vect_norm(line->from.dir), vect_norm(line->to.dir));
		c[1] = sqrt(1.0 - k * k * (1.0 - c[0] * c[0]));
		r[0] = (line->n1 * c[0] - line->n2 * c[1]) / (line->n1 * c[0] + line->n2 * c[1]);
		r[0] = r[0] * r[0];
		r[1] = (line->n2 * c[0] - line->n1 * c[1]) / (line->n2 * c[0] + line->n1 * c[1]);
		r[1] = r[1] * r[1];
		r[2] = (r[0] + r[1]) / 2.0;
		col = mult_color(get_refract(objs, lums, line, d), r[2]);
		if (r[2] < 1.0 && objs->obj[line->obj].reflect == 0.0)
			objs->obj[line->obj].reflect = 1.0 - r[2];
	}
	if (objs->obj[line->obj].reflect > 0.0)
		col = add_color(col, mult_color(
											get_reflect(objs, lums, line, d),
											objs->obj[line->obj].reflect));
	return (col);
}

t_color		get_col(t_objs *objs, t_lums *lums, t_ray *line, unsigned int d)
{
	int		i;
	t_color	ambi_col;
	t_color	cols[3];

	if (!d || !objs || !lums || which_obj_col(objs, line) == 0)
		return (get_black());
	if (lums->amb_coef < 1.000)
	{
		ambi_col = mult_color(objs->obj[line->obj].col, lums->amb_coef);
		cols[0] = get_black();
		cols[1] = get_black();
		i = -1;
		while (++i < lums->nb)
		{
			cols[1] = get_lum(objs, line->obj, lums->lum[i], line);
			cols[0].c.r = fmin(255, cols[0].c.r + cols[1].c.r * lums->lum[i].coef / lums->coefs_sum);
			cols[0].c.g = fmin(255, cols[0].c.g + cols[1].c.g * lums->lum[i].coef / lums->coefs_sum);
			cols[0].c.b = fmin(255, cols[0].c.b + cols[1].c.b * lums->lum[i].coef / lums->coefs_sum);
		}
		if (objs->obj[line->obj].tex == 1 && objs->obj[line->obj].type == PLANE)
			ambi_col = mult_color(ambi_col, checkerboard(line));
		if (objs->obj[line->obj].motion == 1)
		{
			;
		}
		cols[0] = mult_color(cols[0], 1.000 - lums->amb_coef);
		cols[0] = add_color(cols[0], ambi_col);
	}
	else
		cols[0] = objs->obj[line->obj].col;
//	objs->obj[line->obj].ext = line->obj_in;
	cols[0] = mult_color(cols[0], 1.0);
//	line->n2 = objs->obj[line->obj].refract;
	if (objs->obj[line->obj].reflect > 0.0)
		cols[0] = add_color(
				mult_color(cols[0], 1.0 - 0.9 * objs->obj[line->obj].reflect),
				get_reflect(objs, lums, line, d - 1));
	else if (objs->obj[line->obj].transp > 0.0)
		cols[0] = add_color(
				mult_color(cols[0], 1.0 - 0.9 * objs->obj[line->obj].transp),
				get_refract(objs, lums, line, d - 1));
	return (cols[0]);
}

void		*rays(void *tmp)
{
	int		i;
	int		y;
	int		x;
	t_color	col;
	t_env *env;
	t_ray tutu;

	env = ((t_threads *)tmp)->env;
	y = ((t_threads *)tmp)->start;
	i = ((t_threads *)tmp)->incr;
	while (y < WIN_Y)
	{
		x = -1;
		while (++x < WIN_X)
		{
			tutu = init_line((double)(x + 0.5), (double)(y + 0.5), env->cams.cam[env->cams.curr]);
			col = get_col(&env->objs, &env->lums, &tutu, 4);//env->effects.depth);
			if (env->display.sur == 1)
				((int *)env->display.surf->pixels)[x + y * env->display.surf->w] = col.color;
			else
				((int *)env->display.surf2->pixels)[x + y * env->display.surf->w] = col.color;
		}
		y += i;
	}
	return (env);
}

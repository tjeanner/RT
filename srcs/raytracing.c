/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 19:12:29 by tjeanner          #+#    #+#             */
/*   Updated: 2018/05/03 03:36:22 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	return (vect_norm(vect_scal(vect, line->from.dir) > 0.000 ? vect_inv(vect) : vect));
}

int			which_obj_col(t_objs *objs, t_ray *line)
{
	double	tmp;
	t_v		tutu;
	int		i;
	int		ob;

	i = -1;
	tmp = -1.0;
	while (++i < objs->nb)
	{
		if (objs->obj[i].type != NONE && objs->col_fcts[(int)objs->obj[i].type]
				(line->from, objs->obj[i], &tutu) == 1)//&& ((tmp > tutu.x || tmp > tutu.y) || tmp < 0.0))
		{
			if(tutu.y > 0.0 && (tutu.y < tmp || tmp < 0.0) && (ob = i) == i)
				tmp = tutu.y;
			if(tutu.x > 0.0 && (tutu.x < tmp || tmp < 0.0) && (ob = i) == i)
				tmp = tutu.x;
		}
	}
	if (tmp < 0.0 || objs->nb == 0)
		return (0);
	line->obj = ob;
	line->to.pos = vect_add(line->from.pos, vect_mult(line->from.dir, tmp));
	line->to.dir = get_norm(objs->obj[ob], line);
	line->dist = tmp;
	line->total_dist += line->dist;
	return (1);
}

t_color		get_specular(t_obj obj, t_ray ray)
{
	double	res;
	t_v		half;
	t_v		to_eye;
	t_color	plastic;

	if (obj.k_spec == 0.0)
		return (get_black());
	to_eye = (*(ray.incident)).to.dir;
	half = vect_norm(vect_sous(ray.from.dir, ray.incident->from.dir));
	if ((res = vect_scal(ray.to.dir, half)) < 0.0)
		return (get_black());
	plastic = mult_color(get_white(), obj.mat.plastic);
	plastic = add_color(plastic, mult_color(obj.col, 1.0 - obj.mat.plastic));
	if (obj.mat.rough == 1.0)
		return (mult_color(obj.col,
			res * obj.k_spec / (obj.k_diff + obj.k_spec)));
	return (mult_color(obj.col,
			pow(res, obj.mat.rough) * obj.k_spec / (obj.k_diff + obj.k_spec)));
}

t_color		get_diffuse(t_obj obj, t_ray ray)
{
	double	res;

	if (obj.k_diff == 0.0)
		return (get_black());
	if ((res = vect_scal(ray.to.dir, ray.from.dir)) < 0.0)
		return (get_black());
	return (mult_color(obj.col, res * obj.k_diff / (obj.k_diff + obj.k_spec)));
}

t_color		get_lum(t_objs *objs, int obj, t_lum lum, t_ray *line)
{
	int		i;
	t_v		res;
	t_ray	tutu;
	t_color	col;
	double	tmp;

	tutu.to.pos = lum.pos;
	tutu.from.dir = vect_sous(lum.pos, line->to.pos);
	tmp = get_vect_norm(tutu.from.dir);
	tutu.from.dir = vect_norm(get_vect_norm(lum.dir) ? vect_inv(lum.dir) : tutu.from.dir);
	tutu.from.dir = vect_norm(tutu.from.dir);
	tutu.from.pos = vect_add(line->to.pos, vect_mult(line->to.dir, MARGIN));
	tutu.incident = line;
	line->col = get_white();
	i = -1;
	while (++i < objs->nb)
		if (objs->obj[i].type != NONE && (objs->col_fcts[(int)objs->obj[i].type]
				(tutu.from, objs->obj[i], &res) == 1) &&
			((res.x > 0.0 && res.x < tmp) || (res.y > 0.0 && res.y < tmp)))
		{
			if (objs->obj[i].transp == 0.0)
				return ((line->col = get_black()));
			lum.coef *= (res.x > 0.0 && res.x < tmp) ? objs->obj[i].transp : 1.0;
			lum.coef *= (res.y > 0.0 && res.y < tmp) ? objs->obj[i].transp : 1.0;
			line->col = prod_color(line->col, objs->obj[i].col);
		}
	tutu.to.dir = line->to.dir;
	col = get_diffuse(objs->obj[obj], tutu);
	col = add_color(col, get_specular(objs->obj[obj], tutu));
	col = prod_color(col, line->col);
	return (col);
}

t_color		get_reflect(t_objs *objs, t_lums *lums, t_ray *line, unsigned int d)
{
	t_ray	refl;
	t_color	col;

	refl.from.pos = vect_add(line->to.pos, vect_mult(line->to.dir, MARGIN));
	refl.from.dir = vect_norm(vect_reflect(line->from.dir, line->to.dir));
	refl.total_dist = line->total_dist;
	refl.n1 = line->n2;
	refl.n2 = line->n2;
	refl.incident = line;
	refl.objs = line->objs;
	refl.nb_objs = line->nb_objs;
	col = mult_color(get_col(objs, lums, &refl, d), 
			objs->obj[line->obj].reflect /
			(objs->obj[line->obj].transp + objs->obj[line->obj].reflect));
	refl.objs = NULL;
	return (col);
}

t_color		get_refract(t_objs *objs, t_lums *lums, t_ray *line, unsigned int d)
{
	t_ray	refr;
	t_ray	*tmp;
	t_color	col;

	refr.from.pos = vect_add(line->to.pos, vect_mult(line->to.dir, -MARGIN));
	refr.n1 = line->n2;
	refr.incident = line;
	refr.total_dist = line->total_dist;
	if (!line->objs || !line->nb_objs)
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
			ft_memcpy(refr.objs, line->objs, objs->nb * sizeof(char));
			refr.objs[line->obj] = !line->objs[line->obj];
		}
	}
	refr.n2 = 1.0;
	if (refr.objs)
	{
		tmp = line;
		while (tmp && refr.objs[tmp->obj] == OUT_OBJ)
			tmp = tmp->incident;
		refr.n2 = tmp ? objs->obj[tmp->obj].refract : 1.0;
	}
	refr.from.dir = vect_norm(vect_refract(line->from.dir, line->to.dir,
														refr.n1 / refr.n2));
	col = mult_color(get_col(objs, lums, &refr, d),
			objs->obj[line->obj].transp /
			(objs->obj[line->obj].transp + objs->obj[line->obj].reflect));
	col = prod_color(col, objs->obj[line->obj].col);
	if (refr.objs)
		free(refr.objs);
	refr.objs = NULL;
	return (col);
}

t_color		get_col(t_objs *objs, t_lums *lums, t_ray *line, unsigned int d)
{
	int		i;
	t_color	ambi_col;
	t_color	col;
	t_obj	obj;

	if (!d || !objs || !lums || which_obj_col(objs, line) == 0)
		return (get_black());
	obj = objs->obj[line->obj];
	if (lums->amb_coef < 1.000)
	{
		ambi_col = mult_color(obj.col, lums->amb_coef);
		col = get_black();
		i = -1;
		while (++i < lums->nb)
			col = add_color(col, mult_color(
							get_lum(objs, line->obj, lums->lum[i], line),
							lums->lum[i].coef / lums->coefs_sum));
//		if (objs->obj[line->obj].tex == 1 && objs->obj[line->obj].type == PLANE)
//			ambi_col = mult_color(ambi_col, checkerboard(line));
//		if (objs->obj[line->obj].motion == 1)
//		{
//			;
//		}
		col = mult_color(col, 1.000 - lums->amb_coef);
		col = add_color(col, ambi_col);
	}
	else
		col = obj.col;
	col = mult_color(col, (1.0 - objs->obj[line->obj].reflect) * (1.0 - objs->obj[line->obj].transp));
	if (obj.transp > 0.0)
		col = add_color(col, get_refract(objs, lums, line, d - 1));
	if (obj.reflect > 0.0)
		col = add_color(col, get_reflect(objs, lums, line, d - 1));
	return (col);
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
			col = get_col(&env->objs, &env->lums, &tutu, env->effects.depth);
			if (env->display.sur == 1)
				((unsigned int *)env->display.surf->pixels)[x + y * env->display.surf->w] = col.color;
			else
				((unsigned int *)env->display.surf2->pixels)[x + y * env->display.surf->w] = col.color;
		}
		y += i;
	}
	return (env);
}

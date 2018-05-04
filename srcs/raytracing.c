/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 19:12:29 by tjeanner          #+#    #+#             */
/*   Updated: 2018/05/04 05:30:16 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_color	eekkkf(t_lums *lums, t_color col, t_objs *objs, t_ray *line)
{
	int i;

	i = -1;
	while (++i < lums->nb)
		col = add_color(col, mult_color(
						get_lum(objs, line->obj, lums->lum[i], line),
						lums->lum[i].coef / lums->coefs_sum));
	return (col);
}

t_color			get_col(t_objs *objs, t_lums *lums, t_ray *line, unsigned int d)
{
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
		col = eekkkf(lums, col, objs, line);
		col = add_color(mult_color(col, 1.000 - lums->amb_coef), ambi_col);
	}
	else
		col = obj.col;
	col = mult_color(col, (1.0 - objs->obj[line->obj].reflect) *
			(1.0 - objs->obj[line->obj].transp));
	if (obj.transp > 0.0)
		col = add_color(col, get_refract(objs, lums, line, d - 1));
	if (obj.reflect > 0.0)
		col = add_color(col, get_reflect(objs, lums, line, d - 1));
	return (col);
}

t_color			get_anti_alias_col(t_env *env, int x, int y)
{
	int		i;
	t_color *cols;
	t_ray	ray;
	double	delta;
	double	alias;
	double	alias2;

	i = -1;
	alias = (int)env->effects.alias;
	alias2 = alias * alias;
	delta = 1.0 / alias;
	if (!(cols = (t_color *)malloc(sizeof(t_color) * alias2)))
		error_mgt(0);
	while (++i < alias2)
	{
		ray = init_line(
			(double)(x + delta / 2.0 + (double)(i % (int)alias) * delta),
			(double)(y + delta / 2.0 + (double)((int)(i / (int)alias) * delta)),
			env->cams.cam[env->cams.curr]);
		cols[i] = get_col(&env->objs, &env->lums, &ray, env->effects.depth);
	}
	return (average_color(cols, (double)(1.0 / alias2)));
}

void			*rays(void *tmp)
{
	int		i;
	int		y;
	int		x;
	t_color	col;
	t_env	*env;
	t_ray	tutu;

	env = ((t_threads *)tmp)->env;
	y = ((t_threads *)tmp)->start;
	i = ((t_threads *)tmp)->incr;
	while (y < WIN_Y)
	{
		x = -1;
		while (++x < WIN_X)
		{
			if (env->effects.alias <= 1)
				tutu = init_line((double)(x + 0.5 / env->effects.alias),
		(double)(y + 0.5 / env->effects.alias), env->cams.cam[env->cams.curr]);
			col = (env->effects.alias != 1) ? get_anti_alias_col(env, x, y) :
				get_col(&env->objs, &env->lums, &tutu, env->effects.depth);
			if (env->display.sur == 1)
				((unsigned int *)env->display.surf->pixels)
					[x + y * env->display.surf->w] = col.color;
			else
				((unsigned int *)env->display.surf2->pixels)
					[x + y * env->display.surf->w] = col.color;
		}
		y += i;
	}
	return (env);
}

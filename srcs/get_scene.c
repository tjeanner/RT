/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 01:32:15 by hbouchet          #+#    #+#             */
/*   Updated: 2018/02/12 03:19:08 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color	get_color(char *hexa)
{
	t_color	col;
	char	*s;
	int		tmp;

	s = ft_strdup("0123456789ABCDEF");
	tmp = (int)(ft_strchr(s, ft_toupper(hexa[0])) - s) * 16
		+ (int)(ft_strchr(s, ft_toupper(hexa[1])) - s);
	col.c.r = tmp;
	tmp = (int)(ft_strchr(s, ft_toupper(hexa[2])) - s) * 16
		+ (int)(ft_strchr(s, ft_toupper(hexa[3])) - s);
	col.c.g = tmp;
	tmp = (int)(ft_strchr(s, ft_toupper(hexa[4])) - s) * 16
		+ (int)(ft_strchr(s, ft_toupper(hexa[5])) - s);
	col.c.b = tmp;
	return (col);
}

void	get_obj(char **arr, t_obj *objet)
{
	objet->type = ft_strtrim(arr[0])[0];
	objet->o.x = ft_atof(arr[1]) + ft_atof(arr[7]);
	objet->o.y = ft_atof(arr[2]) + ft_atof(arr[8]);
	objet->o.z = ft_atof(arr[3]) + ft_atof(arr[9]);
	objet->norm = norm_vect(ft_atof(arr[4]), ft_atof(arr[5]), ft_atof(arr[6]));
	if (objet->type != 's')
		objet->norm = rotation(objet->norm, norm_vect(ft_atof(arr[11]),
						ft_atof(arr[12]), ft_atof(arr[13])), ft_atof(arr[14]));
	else
		objet->norm = (t_v){0, 0, 0};
	objet->radius = ft_atof(arr[10]);
	objet->col = get_color(arr[15]);
}

void	get_lum(char **arr, t_lum *lum)
{
	lum->pos_lum.x = ft_atof(arr[1]);
	lum->pos_lum.y = ft_atof(arr[2]);
	lum->pos_lum.z = ft_atof(arr[3]);
	lum->coef = 1.0;
//	set_white(&lum->col);
	lum->col = get_color(arr[4]);
}

void	get_cam(char **arr, t_cam *cam)
{
	cam->pos_cam.x = ft_atof(arr[1]);
	cam->pos_cam.y = ft_atof(arr[2]);
	cam->pos_cam.z = ft_atof(arr[3]);
	cam->vcam.x = ft_atof(arr[4]);
	cam->vcam.y = ft_atof(arr[5]);
	cam->vcam.z = ft_atof(arr[6]);
	cam->v2cam.x = ft_atof(arr[7]);
	cam->v2cam.y = ft_atof(arr[8]);
	cam->v2cam.z = ft_atof(arr[9]);
}

int		get_scenelen(t_env *env)
{
	int		fd;
	char	buf;
	int		len;

	len = 0;
	if ((fd = open(env->file, O_RDONLY)) < 0)
		ft_put_err("Can't open scene");
	if ((read(fd, NULL, 0)) < 0)
		ft_put_err("Can't open scene");
	while (read(fd, &buf, 1))
		if (buf == '\n')
			len++;
	close(fd);
	return (len);
}

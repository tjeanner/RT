/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 02:03:21 by hbouchet          #+#    #+#             */
/*   Updated: 2018/01/26 06:18:01 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color	get_color(char *hexa)
{
	t_color	col;
//	char *tmp;
	char *s;
	int tmp;

	s = ft_strdup("0123456789ABCDEF");
	tmp = (int)(ft_strchr(s, hexa[0]) - s) * 16
		+ (int)(ft_strchr(s, hexa[1]) - s);
	col.c.r = tmp;
	tmp = (int)(ft_strchr(s, hexa[2]) - s) * 16
		+ (int)(ft_strchr(s, hexa[3]) - s);
	col.c.g = tmp;
	tmp = (int)(ft_strchr(s, hexa[4]) - s) * 16
		+ (int)(ft_strchr(s, hexa[5]) - s);
	col.c.b = tmp;
	return (col);
}

/*t_obj	get_plane(char **arr)
{
	t_obj	objet;

	objet.type = 'p';
	objet.o.x = ft_atoi(arr[1]);
	objet.o.y = ft_atoi(arr[2]);
	objet.o.z = ft_atoi(arr[3]);
	objet.norm.x = ft_atoi(arr[4]);
	objet.norm.y = ft_atoi(arr[5]);
	objet.norm.z = ft_atoi(arr[6]);
	objet.col = get_color(arr[11]);
	return (objet);
}

t_obj	get_tube(char **arr)
{
	t_obj	objet;

	objet.type = 't';
	objet.o.x = ft_atoi(arr[1]);
	objet.o.y = ft_atoi(arr[2]);
	objet.o.z = ft_atoi(arr[3]);
	objet.norm.x = ft_atoi(arr[4]);
	objet.norm.y = ft_atoi(arr[5]);
	objet.norm.z = ft_atoi(arr[6]);
	objet.radius = ft_atoi(arr[10]);
	objet.col = get_color(arr[11]);
	return (objet);
}

t_obj	get_sphere(char **arr)
{
	t_obj	objet;

	objet.type = 's';
	objet.o.x = ft_atoi(arr[1]);
	objet.o.y = ft_atoi(arr[2]);
	objet.o.z = ft_atoi(arr[3]);
	objet.col = get_color(arr[11]);
	objet.radius = ft_atoi(arr[10]);
	return (objet);
}

t_obj	get_cone(char **arr)
{
	t_obj	objet;

	objet.type = 'c';
	objet.o.x = ft_atoi(arr[1]);
	objet.o.y = ft_atoi(arr[2]);
	objet.o.z = ft_atoi(arr[3]);
	objet.norm.x = ft_atoi(arr[4]);
	objet.norm.y = ft_atoi(arr[5]);
	objet.norm.z = ft_atoi(arr[6]);
	objet.radius = ft_atoi(arr[10]);
	objet.col = get_color(arr[11]);
	return (objet);
}
*/

t_obj	get_obj(char **arr)
{
	t_obj	objet;

	objet.type = arr[0][0];
	objet.o.x = ft_atof(arr[1]);
	objet.o.y = ft_atof(arr[2]);
	objet.o.z = ft_atof(arr[3]);
	objet.norm.x = ft_atof(arr[4]);
	objet.norm.y = ft_atof(arr[5]);
	objet.norm.z = ft_atof(arr[6]);
	objet.radius = ft_atof(arr[10]);
	objet.col = get_color(arr[11]);
	return (objet);

/*	if (ft_strstr(arr[0], "plane"))
		return (get_plane(arr));
	else if (ft_strstr(arr[0], "tube"))
		return (get_tube(arr));
	else if (ft_strstr(arr[0], "cone"))
		return (get_cone(arr));
	else
		return (get_sphere(arr));
*/
}

t_lum	get_lum(char **arr)
{
	t_lum	lum;

	lum.pos_lum.x = ft_atof(arr[1]);
	lum.pos_lum.y = ft_atof(arr[2]);
	lum.pos_lum.z = ft_atof(arr[3]);
	lum.coef = 1.0;
	set_white(&lum.col);
	return (lum);
}

t_cam	get_cam(char **arr)
{
	t_cam	cam;

	cam.pos_cam.x = ft_atof(arr[1]);
	cam.pos_cam.y = ft_atof(arr[2]);
	cam.pos_cam.z = ft_atof(arr[3]);
	cam.vcam.x = ft_atof(arr[4]);
	cam.vcam.y = ft_atof(arr[5]);
	cam.vcam.z = ft_atof(arr[6]);
	cam.v2cam.x = ft_atof(arr[7]);
	cam.v2cam.y = ft_atof(arr[8]);
	cam.v2cam.z = ft_atof(arr[9]);
	return (cam);
}

void	init_scene(t_env *env, char *scene)
{
	int		fd;
	int		ret;
	char	*line;
//	t_obj	*obj;
	char	**tmp;
	int		i = 0;
	char	flag;

	if ((fd = open(scene, O_RDONLY)) == -1)
		exit(0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ft_strstr(line, "#OBJ# "))
		{
			flag = 'o';
			env->nb_obj = ft_atoi(line + 6);
			if (!(env->objs = (t_obj *)malloc(sizeof(t_obj) * env->nb_obj + 1)))
				exit (0);
		}
		else if (ft_strstr(line, "#CAM#"))
		{
			flag = 'c';
			env->nb_cam = ft_atoi(line + 6);
			if (!(env->cams = (t_cam *)malloc(sizeof(t_cam) * env->nb_cam) + 1))
				exit (0);
		}
		else if (ft_strstr(line, "#LUM#"))
		{
			flag = 'l';
			env->nb_lum = ft_atoi(line + 6);
			if (!(env->lums = (t_lum *)malloc(sizeof(t_lum) * env->nb_lum) + 1))
				exit (0);		
		}
		else
		{
			tmp = ft_strsplit(line, '\t');
			if (flag == 'o' && (ft_strstr(tmp[0], "tube") || ft_strstr(tmp[0], "plane")
					 || ft_strstr(tmp[0], "sphere") || ft_strstr(tmp[0], "cone")))
			{
				env->objs[i] = get_obj(tmp);
				i++;
			}
			else if (flag == 'c' && ft_strstr(tmp[0], "cam"))
			{
				env->cams[0] = get_cam(tmp);
				i++;
			}
			else if (flag == 'l' && ft_strstr(tmp[0], "lum"))
			{
				env->lums[0] = get_lum(tmp);
				i++;
			}
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 02:03:21 by hbouchet          #+#    #+#             */
/*   Updated: 2018/01/25 21:52:38 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color	get_color(char *hexa)
{
	t_color	col;
	char *tmp;

	tmp = ft_strsub(hexa, 0, 2);
	col.c.r = (int)strtol(tmp, NULL, 16); //-42
	tmp = ft_strsub(hexa, 2, 2);
	col.c.g = (int)strtol(tmp, NULL, 16);
	tmp = ft_strsub(hexa, 4, 2);
	col.c.b = (int)strtol(tmp, NULL, 16);
	col.c.a = 0;

//	printf("h : %d\n", (int)strtol(tmp, NULL, 16));
	return (col);
}

t_obj	get_plane(char **arr)
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
//	objet.col = get_color(arr[11]);
	return (objet);
}

t_obj	get_obj(char **arr)
{
	if (ft_strstr(arr[0], "plane"))
		return (get_plane(arr));
	else if (ft_strstr(arr[0], "tube"))
		return (get_tube(arr));
	else if (ft_strstr(arr[0], "cone"))
		return (get_cone(arr));
	else
		return (get_sphere(arr));
}

void	init_scene(t_env *env, char *scene)
{
	int		fd;
	int		ret;
	char	*line;
	t_obj	*obj;
	char **tmp;
	int		i = 1;

	if ((fd = open(scene, O_RDONLY)) == -1)
		exit(0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ft_strstr(line, "## "))
		{
			env->nb_obj = ft_atoi(line + 3) + 1;
			if (!(obj = (t_obj *)malloc(sizeof(t_obj) * env->nb_obj)))
				exit (0);
		}
		else
		{
			tmp = ft_strsplit(line, '\t');
			if (ft_strstr(tmp[0], "tube") || ft_strstr(tmp[0], "plane")
				|| ft_strstr(tmp[0], "sphere") || ft_strstr(tmp[0], "cone"))
			{
				env->objs[i] = get_obj(tmp);
//				if (ft_strstr(tmp[0], "sphere"))				
//					printf("-- %d : %f\n", i, env->objs[i].o.x);
				i++;
			}
		}
	}
}

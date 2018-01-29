/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 02:03:21 by hbouchet          #+#    #+#             */
/*   Updated: 2018/01/29 01:32:03 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_scene(t_env *env)
{
	int		fd;
	int		ret;
	char	*line;
	t_par	par;

	env->nb_obj = 0;
	env->nb_cam = 0;
	env->nb_lum = 0;
	if ((fd = open(env->file, O_RDONLY)) == -1)
		exit(0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ft_strlen(line) != 0)
			set_list(env, line, &par);
		free(line);
	}
	if (!(env->objs = (t_obj *)malloc(sizeof(t_obj) * env->nb_obj)))
		exit(0);
	if (!(env->cams = (t_cam *)malloc(sizeof(t_cam) * env->nb_cam)))
		exit(0);
	if (!(env->lums = (t_lum *)malloc(sizeof(t_lum) * env->nb_lum)))
		exit(0);
	set_struct(env, &par);
}

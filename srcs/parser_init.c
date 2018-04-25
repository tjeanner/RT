/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 16:46:03 by hbouchet          #+#    #+#             */
/*   Updated: 2018/04/25 18:15:19 by tjeanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			destrucainitialiserquonveutaussiapresreload(t_env *env);

static void		j_init_env_var(t_env *env)
{
	env->objs.nb = 0;
	env->cams.nb = 0;
	env->lums.nb = 0;
	env->name = ft_strdup("RT");
	env->effects.filter = ft_strdup("NONE");
	env->lums.amb_coef = 0.2;
}

void			j_init_env_struc(t_env *env)
{
	t_par	par;
	t_json	*fjson;

	fjson = env->json;
	j_fill_env(fjson, &par, env);
	if (env->cams.nb == 0)
		error_mgt(9);
	malloc_env(env);
	set_struct(env, &par);
	ft_parser_free(env->json);
	env->effects.stereo = (!ft_strcmp(env->effects.filter, "3D")) ? 1 : 0;
	destrucainitialiserquonveutaussiapresreload(env);
}

void			j_init(t_env *env)
{
	int		ret;
	int		fd;
	char	*line;
	char	*tmp;
	int		nb_char;

	nb_char = 0;
	j_init_env_var(env);
	if (!(fd = open(env->file, O_RDONLY)))
		error_mgt(6);
	tmp = ft_strnew(0);
	if ((ret = get_next_line(fd, &line)) > 0)
		tmp = (line[0] != '{') ? error_mgt(1) : ft_strjoinfree(tmp, line, 'B');
	while ((ret = get_next_line(fd, &line)) > 0 && nb_char < 1000)
	{
		nb_char += ret;
		tmp = ft_strjoinfree(tmp, line, 'B');
	}
	free(line);
	line = tmp;
	if (!brackets(tmp, ft_strlen(tmp)))
		error_mgt(1);
	env->json = parse_json(&tmp);
	free(line);
	j_init_env_struc(env);
}

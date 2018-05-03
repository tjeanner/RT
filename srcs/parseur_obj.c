/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 20:35:12 by vmercadi          #+#    #+#             */
/*   Updated: 2018/05/03 21:33:13 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Free a tab
*/

void		free_tab(void **tab)
{
	char	**tmp;

	tmp = (char **)tab;
	while (*tmp)
	{
		if (tmp)
			ft_strdel(tmp);
		tmp++;
	}
	free(tab);
	tab = NULL;
}

/*
** Vect init
*/

t_v			init_vect(double x, double y, double z)
{
	t_v	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

/*
** donne le nombre de str dans un char**
*/

int			tab_len(char **tab)
{
	int		i;

	if (!tab || !*tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

/*
** Return the 3 values needed for malloc
** (Now return only one value (for v ))
*/

t_v			get_nblines(char *av)
{
	t_v		v;
	int		fd;
	char	*s;

	s = NULL;
	v.x = 0;
	if ((fd = open(av, O_RDONLY)) < 0)
		parse_error(0, ": Open failed.");
	while (get_next_line(fd, &s) > 0)
	{
		if (ft_strstr(s, "v "))
			v.x++;
		free(s);
	}
	close(fd);
	return (v);
}

void		init_pobj(t_pobj *pobj, char *av)
{
	int i;

	pobj->tri = NULL;
	pobj->nbtri = 0;
	pobj->index = 0;
	pobj->nb = get_nblines(av);
	if (pobj->nb.x &&
		(!(pobj->v = (t_v *)malloc(sizeof(t_v) * pobj->nb.x + 1)) ||
		!(pobj->tri = (t_tri *)malloc(sizeof(t_tri) * pobj->nbtri + 1))))
		parse_error(6, NULL);
	if (!pobj->nb.x)
		parse_error(0, "Not enough vector faces (v -0.79 -0.42 0.23).");
	i = -1;
	while (++i <= pobj->nb.x)
		pobj->v[i] = init_vect(0.0, 0.0, 0.0);
	pobj->i.x = 1;
}

/*
** Start the parsing
*/

t_tri		*parse_main(t_env *env, char *av)
{
	int		fd;
	char	*s;
	t_pobj	pobj;

	env->name = ft_strdup(av);
	init_pobj(&pobj, av);
	if ((fd = open(av, O_RDONLY)) < 0)
		parse_error(0, ": Open failed.");
	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		s = ft_strtrim(s);
		if ((s[0] == 'v' && s[1] == ' ') || (s[0] == 'f' && s[1] == ' '))
			parse_redirect(&pobj, s);
		free(s);
	}
	close(fd);
	env->objs.nbtri = pobj.nbtri;
							exit(1);
	return (pobj.tri);
}

/*
** Redirect to the parsor needed (v, vt, vn, f, mtl)
*/

void		parse_redirect(t_pobj *pobj, char *s)
{
	char **tab;

	if (!ft_strlen(s))
		return ;
	if (s[ft_strlen(s) - 1] == 13)
		s[ft_strlen(s) - 1] = '\0';
	tab = ft_strsplit(s, ' ');
	if (tab_len(tab) != 4)
		parse_error(4, s);
	else if (!(ft_strcmp(tab[0], "v")))
		pobj->v[(int)pobj->i.x++] = parse_vect(s + 1);
	else if (!(ft_strcmp(tab[0], "f")))
		pobj->tri[pobj->index++] = parse_f(pobj, &tab[1]);
	else
		parse_error(0, s);
}

/*
** Check if the line got all we need to fill the tri struct
*/

void		check_f(char **tab)
{
	char	**ntab;
	int		i;
	int		j;

	if (tab_len(tab) != 3)
		parse_error(5, tab[0]);
	j = -1;
	while (++j < 3)
	{
		ntab = ft_strsplit(tab[j], '/');
		if (tab_len(ntab) < 1)
		{
			free_tab((void **)ntab);
			parse_error(5, tab[0]);
		}
		i = -1;
		while (ntab[++i])
		{
			if (!ft_isnum(ntab[i]) && ntab[i][0] != '-')
			{
				free_tab((void **)ntab);
				parse_error(4, tab[j]);
			}
		}
		free_tab((void **)ntab);
	}
}

/*
** Make a negative int postive
*/

int			bepos(int nb)
{
	if (nb >= 0)
		return (nb);
	else
		return (nb * -1);
}

/*
** Parsing for f lines
*/

t_tri		parse_f(t_pobj *pobj, char **tab)
{
	t_tri	tri;
	char	**tab2;

	check_f(tab);
	tab2 = ft_strsplit(tab[0], '/');
	tri.v[0] = pobj->v[bepos(ft_atoi(tab2[0]))];
	free_tab((void**)tab2);
	tab2 = ft_strsplit(tab[1], '/');
	tri.v[1] = pobj->v[bepos(ft_atoi(tab2[0]))];
	free_tab((void**)tab2);
	tab2 = ft_strsplit(tab[2], '/');
	tri.v[2] = pobj->v[bepos(ft_atoi(tab2[0]))];
	free_tab((void**)tab2);
	return (tri);
}

/*
** Return 1 if string only contain digit
*/

int			ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	return (1);
}

/*
** Errors for parsing
*/

void		parse_error(int e, char *s)
{
	if (!s)
		s = ft_strdup(" ");
	if (e == 0)
		ft_putendl("ERROR");
	else if (e == 2)
		ft_putendl("./RT exemple.obj");
	else if (e == 3)
		ft_putendl("File is empty or doesn't exist.");
	else if (e == 4)
		ft_putstr("Format error at : ");
	else if (e == 5)
		ft_putstr("Wrong arg number for the face : ");
	else if (e == 6)
		ft_putstr("Malloc failed.");
	if (s)
		ft_putendl(s);
	exit(0);
}

void		parse_err(int e, char *s)
{
	if (e == 0)
		ft_putstr("Error in obj name : ");
	else if (e == 1)
		ft_putstr("Some double is not well formated : ");
	else if (e == 2)
		ft_putstr("Some vector is not well formated : ");
	else if (e == 3)
		ft_putstr("The file given is not a scene : ");
	else if (e == 0 && ft_strchr(s, '\t'))
		ft_putstr("The file given is not a scene : ");
	if (s)
		ft_putendl(s);
	exit(1);
}

/*
** Check and convert a string to a vector
*/

t_v			parse_vect(char *s)
{
	t_v		v;
	int		i;
	char	*c;
	char	**tab;

	tab = ft_strsplit(s, ' ');
	i = -1;
	while (tab[++i])
	{
		if ((c = ft_strchr(tab[i], 'e')))
			*c = '\0';
		parse_double(tab[i]);
	}
	v = init_vect(ft_atof(tab[0]), ft_atof(tab[1]),
		(i == 3 ? ft_atof(tab[2]) : 0));
	free_tab((void **)tab);
	return (v);
}

/*
** Check if a str is a correct double then atof() it
*/

double		parse_double(char *s)
{
	int		i;
	int		p;
	int		p2;

	p = 0;
	p2 = 0;
	i = -1;
	while (s[++i])
	{
		if (ft_isdigit(s[i]) || (s[i] == '.' && p == 0) ||
			(s[i] == '-' && p2 == 0) || s[i] == 13)
		{
			if (s[i] == '.')
				p = 1;
			if (s[i] == '-')
				p2 = 1;
		}
		else
			parse_err(1, s);
	}
	return (ft_atof(s));
}

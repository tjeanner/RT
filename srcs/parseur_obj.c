/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 20:35:12 by vmercadi          #+#    #+#             */
/*   Updated: 2018/05/01 18:18:06 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Free a tab
*/

void	free_tab(void **tab)
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

int		tab_len(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

/*
** return the 3 values needed for malloc
*/

t_v		get_nblines(t_pobj *pobj, char *av)
{
							printf("get_nblines()\n");
	t_v		v;
	int		fd;
	char	*s;

	v.x = 0;
	v.y = 0;
	v.z = 0;
	if ((fd = open(av, O_RDONLY)) < 0)
		parse_error(0, ": Open failed.");
	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		if (ft_strstr(s, "v "))
			v.x++;
		else if (ft_strstr(s, "vt "))
			v.y++;
		else if (ft_strstr(s, "vn "))
			v.z++;
		else if (ft_strstr(s, "f "))
			pobj->nbtri++;
		free(s);

	}
	close(fd);
	return (v);
}

void	init_pobj(t_pobj *pobj, char *av)
{
							printf("init_pobj()\n");
	int i;

	pobj->tri = NULL;
	pobj->nbtri = 0;
	pobj->index = 0;
	pobj->nb = get_nblines(pobj, av);
			printf("1111nbtri = %d\n", pobj->nbtri);
	if (pobj->nb.x && pobj->nb.y && pobj->nb.z &&
		(!(pobj->v = (t_v *)malloc(sizeof(t_v) * pobj->nb.x + 1)) ||
		 !(pobj->vt = (t_v *)malloc(sizeof(t_v) * pobj->nb.y + 1)) ||
		 !(pobj->tri = (t_tri *)malloc(sizeof(t_tri) * pobj->nbtri + 1)) ||
		 !(pobj->vn = (t_v *)malloc(sizeof(t_v) * pobj->nb.z + 1))))
		parse_error(6, NULL);
	i = -1;
	while (++i <= pobj->nb.x)
		pobj->v[i] = init_vect(0.0, 0.0, 0.0);
	i = -1;
	while (++i <= pobj->nb.y)
		pobj->vt[i] = init_vect(0.0, 0.0, 0.0);
	i = -1;
	while (++i <= pobj->nb.z)
		pobj->vn[i] = init_vect(0.0, 0.0, 0.0);
	pobj->i.x = 1;
	pobj->i.y = 1;
	pobj->i.z = 1;
}

/*
** Start the parsing
*/

t_tri	*parse_main(t_env *env, char *av)
{
							printf("parse_main()\n");
	int		fd;
	char	*s;
	t_pobj	pobj;

	init_pobj(&pobj, av);
	if ((fd = open(av, O_RDONLY)) < 0)
		parse_error(0, ": Open failed.");
	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		s = ft_strtrim(s);
		if (s[0] != '#' && (s[0] != '/' && s[1] != '/'))
			parse_redirect(&pobj, s);
		free(s);
	}
	close(fd);
	env->objs.nbtri = pobj.nbtri;
	return (pobj.tri);
}

/*
** Redirect to the parsor needed (v, vt, vn, f, mtl)
*/

void	parse_redirect(t_pobj *pobj, char *s)
{
							// printf("parse_redirect()\n");
	char **tab;

	if (s[ft_strlen(s) - 1] == 13)
		s[ft_strlen(s) - 1] = '\0';
	tab = ft_strsplit(s, ' ');
	if (tab_len(tab) > 4)
		parse_error(4, s);
	if (ft_strstr(tab[0], "mtl") || ft_strstr(tab[0], "g"))
		;//parse_mtl(s);
	else if (!(ft_strcmp(tab[0], "v")))
		pobj->v[(int)pobj->i.x++] = parse_vect(s+1);
	else if (!(ft_strcmp(tab[0], "vt")))
		pobj->vt[(int)pobj->i.y++] = parse_vect(s+3);
	else if (!(ft_strcmp(tab[0], "vn")))
		pobj->vn[(int)pobj->i.z++] = parse_vect(s+3);
	else if (!(ft_strcmp(tab[0], "f")))
		pobj->tri[pobj->index++] = parse_f(pobj, &tab[1]);
	else
		parse_error(0, s);
}

/*
** Check if the line got all we need to fill the s_face struct
*/

void	check_f(char **tab)
{
							// printf("check_f()\n");
	char	**ntab;
	int		i;
	int		j;

	if (tab_len(tab) != 3)
		parse_error(5, tab[0]);
	j = -1;
	while (++j < 3)
	{
		ntab = ft_strsplit(tab[j], '/');
		if (tab_len(ntab) < 3)
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
	}
	free_tab((void **)ntab);
}

/*
** Make a negative int postive
*/

int		bepos(int nb)
{
	if (nb >= 0)
		return (nb);
	else
		return (nb * -1);
}

/*
** Parsing for f lines
*/

t_tri	parse_f(t_pobj *pobj, char **tab)
{
							// printf("parse_f()\n");
	t_tri	tri;
	char	**tab2;
	int		j;

	check_f(tab);
	j = 0;
	tab2 = ft_strsplit(tab[0], '/');
	tri.v[0] = pobj->v[bepos(ft_atoi(tab2[0]))];
	tri.v[1] = pobj->v[bepos(ft_atoi(tab2[1]))];
	tri.v[2] = pobj->v[bepos(ft_atoi(tab2[2]))];
	free_tab((void**)tab2);
	tab2 = ft_strsplit(tab[1], '/');
	tri.vt[0] = pobj->vt[bepos(ft_atoi(tab2[0]))];
	tri.vt[1] = pobj->vt[bepos(ft_atoi(tab2[1]))];
	tri.vt[2] = pobj->vt[bepos(ft_atoi(tab2[2]))];
	free_tab((void**)tab2);
	tab2 = ft_strsplit(tab[2], '/');
	tri.vn[0] = pobj->vn[bepos(ft_atoi(tab2[0]))];
	tri.vn[1] = pobj->vn[bepos(ft_atoi(tab2[1]))];
	tri.vn[2] = pobj->vn[bepos(ft_atoi(tab2[2]))];
	free_tab((void**)tab2);
	return (tri);
}

/*
** Return 1 if string only contain digit
*/

int		ft_isnum(char *str)
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
** Implode a tab in an str separating with the given char then free it
*/

char	*ft_implode(char **tab, char c)
{
							printf("ft_implode()\n");
	int 	size;
	int		i;
	int		j;
	int		k;
	char	*str;

	i = -1;
	k = -1;
	size = tab_len(tab);
	str = ft_strnew(0);
	while (tab[++i])
	{
		j = -1;
		while (tab[i][++j])
			str[++k] = tab[i][j];
		str[++k] = c;
	}
	str[++k] = '\0';
	free_tab((void**)tab);
	return (str);
}

/*
** Errors for parsing
*/

void	parse_error(int e, char *s)
{
	if (!s)
		s = ft_strdup(" ");
	if (e == 0)
		ft_putendl("ERROR");
	else if (e == 2)
		ft_putendl("./RTv1 exemple.obj");
	else if (e == 3)
		ft_putendl("Le fichier est vide ou n'existe pas.");
	else if (e == 4)
		ft_putstr("Erreur formatage à : ");
	else if (e == 5)
		ft_putstr("Mauvais nombre d'arguments pour la face : ");
	else if (e == 6)
		ft_putstr("Malloc failed.");
	if (s)
		ft_putendl(s);
	exit(0);
}

void	parse_err(int e, char *s)
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
** Parse for the mtl files
*/

// void	parse_mtl(char *s)
// {

// }


char		**decoupe(char *s)
{
	char	**tab;

	tab = ft_strsplit(s, '/');
	if (tab_len(tab) != 3)
	{
		parse_err(2, s);
		free_tab((void **)tab);
	}
	return (tab);
}

/*
** Check and convert a string to a vector
*/

t_v			parse_vect(char *s)
{
							// printf("parse_vect()\n");
	t_v		v;
	int		i[2];
	int		p;
	char	*c;
	char	**tab;

	tab = ft_strsplit(s, ' ');
	i[0] = -1;
	while (tab[++i[0]])
	{
		i[1] = -1;
		p = 0;
		if ((c = ft_strchr(tab[i[0]], 'e')))
			*c = '\0';
		while (tab[i[0]][++i[1]])
		{
			if (ft_isdigit(tab[i[0]][i[1]]) || (tab[i[0]][i[1]] == '.' && !p)
											|| tab[i[0]][i[1]] == '-' || tab[i[0]][i[1]] == 13)
				p = (tab[i[0]][i[1]] == '.') ? 1 : 0;
			else
				parse_err(2, s);
		}
	}
	v = init_vect(ft_atof(tab[0]), ft_atof(tab[1]), (i[0] == 3 ? ft_atof(tab[2]) : 0));
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

	p = 0;
	i = -1;
	while (s[++i])
	{
		if (ft_isdigit(s[i]) || (s[i] == '.' && p == 0) || s[i] == '-')
		{
			if (s[i] == '.')
				p = 1;
		}
		else
			parse_err(1, s);
	}
	return (ft_atof(s));
}





























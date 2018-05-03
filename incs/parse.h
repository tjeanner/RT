/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 15:08:55 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/30 01:44:47 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PARSE_H
# define __PARSE_H


/*
** Struct for triangles
*/

// typedef struct			s_tri
// {
// 	t_v					v[3];
// 	t_v					vt[3];
// 	t_v					vn[3];
// 	struct s_tri		*next;
// }						t_tri;

/*
** Parsing .obj base
*/

// typedef struct			s_pobj
// {
// 	t_v					*v;
// 	t_v					*vt;
// 	t_v					*vn;
// 	t_v					nb;
// 	t_v					i;
// 	s_tri				*tri;
// }						t_pobj;

/*
** to stock the MTL files values
*/

// typedef struct				s_mtl
// {
// 	t_col					Ka;			//couleur ambiante (la couleur de l'objet sans lumière directe)
// 	t_col					Kd;			//couleur diffuse (la couleur de l'objet sous lumière blanche)
// 	t_col					Ks;			//couleur spéculaire
// 	t_col					Ke;			//couleur émissive
// 	double					Ni;			//densité optique
// 	double					Ns;			//specular exponent entre 0 et 100
// 	double					d;			//transparence entre 0 et 1 (aucune transparence)
// 	double					illum;		//paramètres de lumières
// 	// double				map_kd;		//(ks, ka) pour la texture utilisé diffuse (specular, ambiante)
// 	struct s_mtl			*next;
// }							t_mtl;

/*
** Obj parsing							| parseur.c
*/

// void						parse_main(t_env *env, char *av);
// void						parse_error(int e, char *s);
// void						parse_mtl(char *s);
// void						init_pobj(t_pobj *pobj, char *av);
// void						parse_redirect(t_pobj *pobj, char *s);
// void						check_f(char **tab);
// char						*ft_implode(char **tab, char c);
// char						*ft_implode(char **tab, char c);
// int							ft_isnum(char *str);
// t_v							get_nblines(char *av);
// t_tri						parse_f(t_pobj *pobj, char **tab);
// t_tri						*add_tri(t_pobj *pobj, t_tri tri);
// char						**decoupe(char *s);
// t_v							parse_vect(char *s);
// double						parse_double(char *s);

#endif
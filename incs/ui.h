/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 18:24:41 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/26 15:44:52 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UI_H
# define __UI_H
# include <SDL.h>
# include <SDL_ttf.h>
# include "utils.h"
# include "color.h"
# include "libft.h"
# define OPEN_SANS_REGULAR "lib/font/open-sans/OpenSans-Regular.ttf"
# define OPEN_SANS_BOLD "lib/font/open-sans/OpenSans-Bold.ttf"
# define OPEN_SANS_EXTRABOLD "lib/font/open-sans/OpenSans-ExtraBold.ttf"
# define OPEN_SANS_ITALIC "lib/font/open-sans/OpenSans-Italic.ttf"
# define OPEN_SANS_LIGHT "lib/font/open-sans/OpenSans-Light.ttf"

/*
** UI base struct
** id1 is for obj onglet
** id2 is for scene onglet
** id3 is for help onglet
*/

typedef struct			s_uipx
{
	int					id1;
	int					id2;
	int					id3;
}						t_uipx;

/*
** Input struct
*/

typedef struct			s_in
{
	SDL_Rect			r;
	SDL_Color			color;
	int					onglet;
	char				*text;
	int					id;
	struct s_in			*next;
}						t_in;

/*
** Button struct
*/

typedef struct			s_btn
{
	SDL_Color 			col_text;
	SDL_Color			col_btn;
	TTF_Font			*font;
	SDL_Surface 		*texSurface;
	SDL_Texture			*tex;
	SDL_Renderer		*renderer;
	SDL_Rect			textRect;
	SDL_Rect			r;
	int					fontsize;
	char				*text;
	int					x;
	int					y;
	int					onglet;
	int					font_size;
	int					id;
	struct s_btn		*next;
}						t_btn;

/*
** Create a zone
*/

typedef struct			s_area
{
	t_col				col;
	double				size;
	int					x;
	int					y;
	int					x2;
	int					y2;
}						t_area;

/*
** UI base struct
*/

typedef struct			s_ui
{
	int					winx;
	int					winy;
	int					maxid;
	t_uipx				**btn_px;
	t_uipx				**in_px;
	t_btn				*btn;
	t_area				*area;
	t_in				*in;
	SDL_Window			*win;
}						t_ui;

/*
** User interface main					| UI_main.c
*/

t_ui					UI_main();
void					create_btn(t_ui *ui, t_btn btn, int x, int y);
void					create_area(int x1, int y1, int x2, int y2);
void					set_btnid2(t_ui *ui, t_btn *btn, int id);
void					set_btnid(t_ui *ui, int id);

/*
** Inits for the UI						| UI_init.c
*/

void					UI_init(t_ui *ui);
t_btn					init_btn(int size, char *text, SDL_Color coltx, SDL_Color colbtn);
SDL_Color				init_sdlcolor(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
SDL_Rect				init_rect(int x, int y, int h, int w);
t_uipx					**init_px_tab(t_ui *ui, t_uipx **tab);
t_in					init_input(t_ui *ui, SDL_Rect r, SDL_Color col);


/*
** Button add, delete, search			| UI_button.c
*/

t_btn					*add_btn(t_ui *ui, t_btn btn, int onglet);
t_btn					*search_btn(t_ui *ui, int id);
void					delete_btn(t_ui *ui, int id);

/*
** Input add, delete, search
*/

t_in					*add_in(t_ui *ui, t_in in, int onglet);
t_in					*search_in(t_ui *ui, int id);
void					delete_in(t_ui *ui, int id);

/*
** Set the btn and inputs id
*/

void					set_inid2(t_ui *ui, t_in *in, int id);
void					set_inid(t_ui *ui, int id);

/*
** Errors for UI						| UI_error.c
*/

void					UI_init_error(int e);


#endif
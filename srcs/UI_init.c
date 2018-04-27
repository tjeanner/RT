/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UI_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 20:28:26 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/26 19:30:21 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

/*
** Init the interface window & values
*/

void	UI_init(t_ui *ui)
{
	ui->winx = 500;
	ui->winy = 1200;
	ui->maxid = 0;
	ui->btn = NULL;
	if (!(ui->win = SDL_CreateWindow("Interface", 0, 0, ui->winx, ui->winy, SDL_WINDOW_SHOWN)))
		UI_init_error(2);
	ui->btn_px = init_px_tab(ui, ui->btn_px);
	ui->in_px = init_px_tab(ui, ui->in_px);
}

/*
** Init a SDL_rect
*/

SDL_Rect	init_rect(int x, int y, int h, int w)
{
	SDL_Rect	rect;

	rect.x = x;
	rect.y = y;
	rect.h = h;
	rect.w = w;
	return (rect);
}

/*
** Init a px_tab for ui
*/

t_uipx		**init_px_tab(t_ui *ui, t_uipx **tab)
{
	int i;
	int j;

	if (!(tab = (t_uipx**)malloc(sizeof(t_uipx*) * ui->winy)))
		UI_init_error(1);
	i = -1;
	while (++i < ui->winy)
		if (!(tab[i] = (t_uipx*)malloc(sizeof(t_uipx) * ui->winx)))
			UI_init_error(1);
	i = -1;
	while (++i < ui->winy)
	{
		j = -1;
		while (++j < ui->winx)
		{
			tab[i][j].id1 = 0;
			tab[i][j].id2 = 0;
			tab[i][j].id3 = 0;
		}
	}
	return (tab);
}

/*
** Init an input struct
*/

t_in	init_input(t_ui *ui, SDL_Rect r, SDL_Color col)
{
	t_in	in;

	in.r = r;
	in.id = ++ui->maxid;
	in.color = col;
	return (in);
}

/*
** To init the new button values
*/

t_btn	init_btn(int size, char *text, SDL_Color coltx, SDL_Color colbtn)
{
	t_btn	btn;

	btn.fontsize = size;
	btn.text = text;
	btn.col_text = coltx;
	btn.col_btn = colbtn;
	btn.r = init_rect(0, 0, 0, 0);
	btn.renderer = NULL;
	btn.tex = NULL;
	btn.texSurface = NULL;
	btn.font = NULL;
	btn.textRect.x = 0;
	btn.textRect.y = 0;
	return (btn);
}

/*
** Iniit for a SDL_color
*/

SDL_Color	init_sdlcolor(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	SDL_Color color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color);
}

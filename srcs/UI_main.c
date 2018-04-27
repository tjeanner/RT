/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UI_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 17:29:27 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/26 16:21:40 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

/*
** Cout the number of words in a phrase
*/

int		count_word(char *s)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		while (s[i] && s[i] != ' ' && s[i] != '\t')
			i++;
		nb++;
		i++;
	}
	return (nb);
}

/*
** Where the differents buttons for UI OBJ are created
*/

void	UI_btn1(t_ui *ui)
{
	SDL_Color col;

	col = init_sdlcolor(255, 255, 255, 255);
	create_btn(ui, *add_btn(ui, init_btn(20, "yolo", col, col), 1), 10, 10);
	create_btn(ui, *add_btn(ui, init_btn(20, "yolo", col, col), 1), 10, 30);
	set_btnid(ui, 1);
}

/*
** Where the differents buttons for UI SCENE are created
*/

void	UI_btn2(t_ui *ui)
{
	SDL_Color	col;

	col = init_sdlcolor(255, 255, 255, 255);
	create_btn(ui, *add_btn(ui, init_btn(20, "yolo", col, col), 2), 10, 10);
	set_btnid(ui, 2);
}

/*
** Where the differents buttons for UI HELP are created
*/

void	UI_btn3(t_ui *ui)
{
	SDL_Color	col;

	col = init_sdlcolor(255, 255, 255, 255);
	create_btn(ui, *add_btn(ui, init_btn(20, "yolo", col, col), 3), 10, 10);
	create_btn(ui, *add_btn(ui, init_btn(20, "yolo", col, col), 3), 10, 20);
	create_btn(ui, *add_btn(ui, init_btn(20, "yolo", col, col), 3), 10, 30);
	create_btn(ui, *add_btn(ui, init_btn(20, "yolo", col, col), 3), 10, 40);
	set_btnid(ui, 3);
}

/*
** Return an int value of a percentage
*/

int 	percent(int nb, int percent)
{
	if (!percent)
		return (0);
	return ((int)((double)(nb * percent / 100)));
}

t_ui	UI_main()
{
	t_ui			ui;

	SDL_StartTextInput();
	UI_init(&ui);
	UI_btn1(&ui);
	// UI_btn2(&ui);
	// UI_btn3(&ui);
	return (ui);
}

/*
** Create input area for user
** ID is to know the type of input (double, int, col..)
*/

// void	create_input(int id)
// {
// 	SDL_SetTextInputRect()
// }

/*
** Set and display all
*/

void	create_btn(t_ui *ui, t_btn btn, int x, int y)
{
	btn.x = x;
	btn.y = y;
	btn.renderer = SDL_CreateRenderer(ui->win, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(btn.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(btn.renderer);
    SDL_SetRenderDrawColor(btn.renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
	TTF_Init();
	btn.r = init_rect(x, y, (btn.fontsize), (ft_strlen(btn.text) * 10));
	btn.font = TTF_OpenFont(OPEN_SANS_REGULAR, btn.fontsize);
	btn.col_text =  init_sdlcolor(144, 77, 255, 255);
	btn.texSurface = TTF_RenderText_Solid(btn.font, btn.text, btn.col_text);
	btn.tex = SDL_CreateTextureFromSurface(btn.renderer, btn.texSurface);
	SDL_QueryTexture(btn.tex, NULL, NULL, &btn.textRect.w, &btn.textRect.h);
	SDL_RenderCopy(btn.renderer, btn.tex, NULL, &btn.textRect);
	SDL_RenderPresent(btn.renderer);
	SDL_FreeSurface(btn.texSurface);
	SDL_DestroyTexture(btn.tex);
	ui->btn = &btn;
}

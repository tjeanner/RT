/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UI_onglet.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 16:09:21 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/26 16:22:50 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

/*
** Where the differents buttons for UI OBJ are created
*/

void	UI_onglet(t_ui *ui)
{
	SDL_Color color;

	color = init_sdlcolor(255, 255, 0, 255);
	// create_btn(ui, *add_btn(ui, init_btn(10, "Objects", color, color), 4));
	// // btn->
	// create_btn(ui, *add_btn(ui, init_btn(10, "Scene", color, color), 4));
	// // btn->
	// create_btn(ui, *add_btn(ui, init_btn(10, "Help", color, color), 4));
	// // btn->
	set_btnid(ui, 4);
}
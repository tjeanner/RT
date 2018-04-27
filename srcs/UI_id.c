/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UI_id.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 17:32:36 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/26 15:07:27 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

/*
** Set the tab_px var and store the id by position
*/

void	set_btnid2(t_ui *ui, t_btn *btn, int id)
{
	int		x;
	int		y;

	y = btn->r.y;
	while (y < (btn->r.y + btn->r.h) && y < ui->winy)
	{
		x = btn->r.x;
		while (x < (btn->r.x + btn->r.w) && x < ui->winx)
		{
			if (id == 1)
				ui->btn_px[y][x].id1 = btn->id;
			else if (id == 2)
				ui->btn_px[y][x].id2 = btn->id;
			else if (id == 3)
				ui->btn_px[y][x].id3 = btn->id;
			x++;
		}
		y++;
	}
}

void	set_btnid(t_ui *ui, int id)
{
	t_btn	*btn;

	btn = ui->btn;
	while (btn && btn->id == 0)
		btn = btn->next;
	while (btn)
	{
		set_btnid2(ui, btn, id);
		btn = btn->next;
	}
}

/*
** Set the tab_px var and store the id by position
*/

void	set_inid2(t_ui *ui, t_in *in, int id)
{
	int		x;
	int		y;

	y = in->r.y;
	while (y <= in->r.y + in->r.h && y < ui->winy)
	{
		x = in->r.x;
		while (x <= in->r.x + in->r.w && x < ui->winx)
		{
			if (id == 1)
				ui->in_px[y][x].id1 = in->id;
			else if (id == 2)
				ui->in_px[y][x].id2 = in->id;
			else if (id == 3)
				ui->in_px[y][x].id3 = in->id;
			x++;
		}
		y++;
	}
}

void	set_inid(t_ui *ui, int id)
{
	t_in	*in;

	in = ui->in;
	while (in && in->id == 0)
		in = in->next;
	while (in)
	{
		set_inid2(ui, in, id);
		in = in->next;
	}
}

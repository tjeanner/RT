/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UI_button.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 18:40:56 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/26 15:01:28 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

/*
**	Add a btn to the list
*/

t_btn	*add_btn(t_ui *ui, t_btn btn, int onglet)
{
			ft_putendlcolor("add_btn", MAGENTA);
	t_btn	*l;

	if (!ui)
		return (NULL);
	if (!(l = ui->btn))
	{
		ui->btn = (t_btn *)malloc(sizeof(t_btn));
		*(ui->btn) = btn;
		ui->btn->id = ++ui->maxid;
		ui->btn->onglet = onglet;
		ui->btn->next = NULL;
		return (ui->btn);
	}
	while (l->next)
		l = l->next;
	l->next = (t_btn *)malloc(sizeof(t_btn));
	l = l->next;
	*l = btn;
	l->id = ++ui->maxid;
	l->onglet = onglet;
	l->next = NULL;
	return (l);
}

/*
** Search a btn in the list
*/

t_btn	*search_btn(t_ui *ui, int id)
{
			ft_putendlcolor("search_btn", MAGENTA);
	t_btn	*l;

	if (id <= 0 || !ui)
		return (NULL);
	l = ui->btn;
	while (l && l->id != id)
		l = l->next;
	if (!l)
		return (NULL);
	return (l);
}

/*
** To delete a selected btn
*/

void	delete_btn(t_ui *ui, int id)
{
			ft_putendlcolor("delete_btn", MAGENTA);

	t_btn	*btn;
	t_btn	*btn2;

	if ((btn = search_btn(ui, id - 1)))
	{
		if (btn->next->next)
			btn2 = btn->next->next;
		else
			btn2 = NULL;
		free(btn->next);
		btn->next = NULL;
		btn->next = btn2;
	}
	else if (!(btn = search_btn(ui, id)))
		return ;
	else
	{
		if (btn->next)
			btn2 = btn->next;
		else
			btn2 = NULL;
		free(btn);
		btn = NULL;
		ui->btn = btn2;
	}
}

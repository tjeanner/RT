/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UI_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:37:50 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/28 14:54:12 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

/*
**	Add a in to the list
*/

t_in	*add_in(t_ui *ui, t_in in, int onglet)
{
	t_in	*l;

	if (!ui)
		return (NULL);
	if (!(l = ui->in))
	{
		ui->in = (t_in *)malloc(sizeof(t_in));
		*(ui->in) = in;
		ui->in->id = ++ui->maxid;
		ui->btn->onglet = onglet;
		ui->in->next = NULL;
		return (ui->in);
	}
	while (l->next)
		l = l->next;
	l->next = (t_in *)malloc(sizeof(t_in));
	l = l->next;
	*l = in;
	l->id = ++ui->maxid;
	l->onglet = onglet;
	l->next = NULL;
	return (l);
}

/*
** Search a in in the list
*/

t_in	*search_in(t_ui *ui, int id)
{
	t_in	*l;

	if (id <= 0 || !ui)
		return (NULL);
	l = ui->in;
	while (l && l->id != id)
		l = l->next;
	if (!l)
		return (NULL);
	return (l);
}

/*
** To delete a selected in
*/

void	delete_in(t_ui *ui, int id)
{

	t_in	*in;
	t_in	*in2;

	if ((in = search_in(ui, id - 1)))
	{
		if (in->next->next)
			in2 = in->next->next;
		else
			in2 = NULL;
		free(in->next);
		in->next = NULL;
		in->next = in2;
	}
	else if (!(in = search_in(ui, id)))
		return ;
	else
	{
		if (in->next)
			in2 = in->next;
		else
			in2 = NULL;
		free(in);
		in = NULL;
		ui->in = in2;
	}
}

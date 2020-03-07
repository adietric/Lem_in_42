/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_bfs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafonso <flafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:04:57 by flafonso          #+#    #+#             */
/*   Updated: 2019/11/14 15:56:42 by flafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	reset_queue(t_info *inf_b, t_room **queue)
{
	int		j;

	j = 0;
	while (j < inf_b->nb_r && queue[j] != NULL)
	{
		queue[j]->mass = -1;
		if (queue[j]->status == 1)
			queue[j]->mass = 0;
		queue[j]->modif = 0;
		queue[j]->skip = 0;
		queue[j]->preview = NULL;
		queue[j] = NULL;
		j++;
	}
}

void	maj_mass(t_info *inf_b, t_room *room, t_link *link)
{
	if (link->room_link->modif == 0)
	{
		if (link->flux == 0)
			link->room_link->mass = room->mass + 1;
		else if (link->flux == -1)
			link->room_link->mass = room->mass - 1;
		link->room_link->modif = 1;
	}
}

int		is_free(t_room *room)
{
	t_link	*link;
	int		pos;

	pos = 0;
	link = room->link;
	while (link)
	{
		if (link->flux == 1)
			pos++;
		link = link->next;
	}
	if (pos > 0)
		return (1);
	return (0);
}

int		need_it(t_info *inf_b, t_room *room, t_link *link)
{
	while (link != NULL && link->room_link != room->preview)
		link = link->next;
	if (link && link->flux == 1)
		return (1);
	link = room->link;
	while (link)
	{
		if (link->flux == -1)
			return (0);
		link = link->next;
	}
	return (1);
}

void	rev_flux(t_room *room, t_room *room_prev, int flux)
{
	t_link	*link;

	link = room_prev->link;
	while (link != NULL && link->room_link != room)
		link = link->next;
	link->flux = flux;
}

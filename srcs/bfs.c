/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafonso <flafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:05:28 by adietric          #+#    #+#             */
/*   Updated: 2019/11/14 16:07:18 by flafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		check_links(t_info *inf_b, t_room **queue, t_room *room, int i)
{
	t_link	*link;
	int		flux;

	link = room->link;
	flux = need_it(inf_b, room, link);
	while (link != NULL && room->skip == 0)
	{
		if (link->room_link->in_queue != inf_b->det_qvalue
			&& link->flux != 1 && flux != link->flux)
		{
			link->room_link->in_queue = inf_b->det_qvalue;
			link->room_link->preview = room;
			queue[++i] = link->room_link;
			if (flux == 0)
				room->skip = 1;
		}
		link = link->next;
	}
	return (i);
}

void	init_flux(t_info *inf_b, t_room *room, t_link *link)
{
	while (room != NULL && room->status != 1)
	{
		while (link != NULL && link->room_link != room->preview)
			link = link->next;
		if (link == NULL)
			return ;
		if (link->flux == 0)
		{
			link->flux = -1;
			rev_flux(room, room->preview, 1);
		}
		else if (link->flux == 1)
		{
			link->flux = 0;
			rev_flux(room, room->preview, 0);
		}
		room = room->preview;
		link = room->link;
	}
	stock_path(inf_b);
}

int		bfs_loop(t_info *inf_b, t_room **queue, t_room *room, t_link *link)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < inf_b->nb_r && queue[j] != NULL)
	{
		link = room->link;
		if (queue[j]->status == -1)
		{
			init_flux(inf_b, room, link);
			return (TRUE);
		}
		i = check_links(inf_b, queue, room, i);
		j++;
		room = queue[j];
	}
	return (FALSE);
}

int		det_max_chm(t_room *start, t_room *end)
{
	int		i;
	int		j;
	t_link	*slink;
	t_link	*elink;

	slink = start->link;
	elink = end->link;
	i = 0;
	j = 0;
	while (slink)
	{
		i++;
		slink = slink->next;
	}
	while (elink)
	{
		j++;
		elink = elink->next;
	}
	if (i < j)
		return (i);
	else
		return (j);
}

void	bfs_start(t_info *inf_b)
{
	t_room		**queue;
	t_room		*room;
	t_link		*link;
	int			i;

	i = det_max_chm(inf_b->the_start, inf_b->the_end);
	if (!(queue = (t_room**)malloc(sizeof(t_room) * inf_b->nb_r)))
		error(inf_b, "Malloc error", NULL);
	ft_bzero(queue, sizeof(t_room**) * inf_b->nb_r);
	while (i != 0)
	{
		queue[0] = inf_b->the_start;
		queue[0]->in_queue = inf_b->det_qvalue;
		room = queue[0];
		link = queue[0]->link;
		bfs_loop(inf_b, queue, room, link);
		reset_queue(inf_b, queue);
		i--;
		inf_b->det_qvalue++;
	}
	free(queue);
}

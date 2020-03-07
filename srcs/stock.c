/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafonso <flafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:06:51 by adietric          #+#    #+#             */
/*   Updated: 2019/11/14 16:11:03 by flafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_path	*new_path(t_info *inf_b, t_room *room)
{
	t_path	*new;

	if (!(new = (t_path*)malloc(sizeof(t_path))))
		error(inf_b, "Error malloc !", NULL);
	new->next = NULL;
	new->room = room;
	new->rep_f = 0;
	new->maj = 0;
	new->t_ch = 0;
	new->ban = 0;
	return (new);
}

int		fill_it(t_info *inf_b, t_path *path, t_room *room, int t_ch)
{
	t_link	*link;

	link = room->link;
	if (room->status == -1)
		return (t_ch + 1);
	while (link)
	{
		if (link->flux == 1)
		{
			path->next = new_path(inf_b, link->room_link);
			return (fill_it(inf_b, path->next, link->room_link, t_ch + 1));
		}
		link = link->next;
	}
	return (0);
}

void	fill_path(t_info *inf_b, t_stock *stock)
{
	t_link	*link;
	int		i;

	i = 0;
	link = inf_b->the_start->link;
	while (link)
	{
		if (link->flux == 1)
		{
			stock->path[i]->next = new_path(inf_b, link->room_link);
			stock->path[i]->t_ch = fill_it(inf_b, stock->path[i]->next
			, link->room_link, 0);
			stock->tot_t_ch += stock->path[i]->t_ch;
			i++;
		}
		link = link->next;
	}
}

void	stock_path(t_info *inf_b)
{
	int		i;
	int		det;

	i = sum_flux(inf_b);
	det = 0;
	if (inf_b->stock[0].path != NULL)
		det = 1;
	if (!(inf_b->stock[det].path = (t_path**)malloc(sizeof(t_path) * i + 1)))
		error(inf_b, "Error malloc !", NULL);
	inf_b->stock[det].path[i] = NULL;
	inf_b->stock[det].p_index = i;
	inf_b->stock[det].nb_ch = i;
	i = -1;
	while (++i < inf_b->stock[det].p_index)
		inf_b->stock[det].path[i] = new_path(inf_b, inf_b->the_start);
	fill_path(inf_b, &inf_b->stock[det]);
	sum_rep_f(inf_b, &inf_b->stock[det]);
	maj_rep_f(inf_b, &inf_b->stock[det], 0);
	inf_b->stock[det].step = sum_step(&inf_b->stock[det]);
	choose(inf_b);
}

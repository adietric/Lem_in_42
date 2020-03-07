/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adietric <adietric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 12:23:56 by flafonso          #+#    #+#             */
/*   Updated: 2019/11/15 12:54:30 by adietric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_room	*find_room(char *gnl, t_info *inf_b, int len)
{
	t_room				*room;
	unsigned long long	index_hach;

	index_hach = hachage(gnl, len);
	room = inf_b->hach_table[index_hach];
	while (room->next != NULL && ft_strncmp(gnl, room->name, len) != 0)
		room = room->next;
	return (room);
}

void	link_it(char *gnl, t_room *room, t_info *inf_b, int i)
{
	t_link	*link;

	link = room->link;
	while (link->next != NULL)
	{
		if ((i == 1 && ft_strncmp(&gnl[inf_b->len[0] + 1],
			link->room_link->name, inf_b->len[1]) == 0 && (ft_strlen(gnl)
			- ft_strlen(&gnl[inf_b->len[0] + 1])) == inf_b->len[1]) || (i == 2
			&& ft_strncmp(gnl, link->room_link->name, inf_b->len[0]) == 0))
			return ;
		link = link->next;
	}
	if ((i == 2 && ft_strncmp(&gnl[inf_b->len[0] + 1], link->room_link->name,
		inf_b->len[1]) == 0) || (i == 1
		&& ft_strncmp(gnl, link->room_link->name, inf_b->len[0]) == 0))
		return ;
	if (!(link->next = (t_link*)malloc(sizeof(t_link))))
		error(inf_b, "error malloc\n", gnl);
	link->next->room_link = (i == 1) ? (find_room(&gnl[inf_b->len[0] + 1],
		inf_b, inf_b->len[1])) : (find_room(gnl, inf_b, inf_b->len[0]));
	link->next->next = NULL;
	link->next->flux = 0;
}

void	fill_link(char *gnl, t_info *inf_b, int i)
{
	unsigned long long	index_hach;
	t_room				*room;
	char				*str;
	int					len;

	str = (i == 1) ? (gnl) : (&gnl[inf_b->len[0] + 1]);
	len = (i == 1) ? (inf_b->len[0]) : (inf_b->len[1]);
	index_hach = (i == 1) ? (hachage(gnl, inf_b->len[0]))
		: (hachage(&gnl[inf_b->len[0] + 1], inf_b->len[1]));
	room = inf_b->hach_table[index_hach];
	while (room->next != NULL && ft_strncmp(str, room->name, len) != 0)
		room = room->next;
	room->nb_link++;
	if (room->link == NULL)
	{
		if (!(room->link = (t_link*)malloc(sizeof(t_link))))
			error(inf_b, "ERROR\n", gnl);
		room->link->room_link = (i == 1) ? (find_room(&gnl[inf_b->len[0] + 1],
			inf_b, inf_b->len[1])) : (find_room(gnl, inf_b, inf_b->len[0]));
		room->link->next = NULL;
		room->link->flux = 0;
	}
	else
		link_it(gnl, room, inf_b, i);
}

int		parcing_tube(char *gnl, t_info *inf_b)
{
	inf_b->len[0] = 0;
	inf_b->len[1] = 0;
	if (gnl[0] == '#')
	{
		if (commande(inf_b, gnl) != 0)
			error(inf_b, "ERROR\n", gnl);
		return (1);
	}
	if (inf_b->room_status != 0 || valid_line(gnl) != -1
		|| false_name_tube(gnl, inf_b, 1, 0) == FALSE)
		return (-1);
	if (ft_strncmp(gnl, &gnl[inf_b->len[0] + 1], inf_b->len[0]) == 0
		&& ft_strlen(&gnl[inf_b->len[0] + 1]) == inf_b->len[0])
		return (-1);
	fill_link(gnl, inf_b, 1);
	fill_link(gnl, inf_b, 2);
	return (1);
}

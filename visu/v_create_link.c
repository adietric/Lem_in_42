/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_create_link.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafonso <flafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 12:23:56 by flafonso          #+#    #+#             */
/*   Updated: 2019/11/14 14:57:54 by flafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visu.h"

t_room	*find_room(char *gnl, t_info *inf_b, int len)
{
	t_room	*room;
	int		i;

	i = 0;
	while (inf_b->room[i] != NULL && i < MAX_R
		&& ft_strncmp(gnl, inf_b->room[i]->name, len) != 0)
		i++;
	room = inf_b->room[i];
	return (room);
}

void	link_it(char *gnl, t_room *room, t_info *inf_b, int i)
{
	t_link	*link;

	link = room->link;
	while (link->next != NULL)
	{
		if ((i == 1 && ft_strncmp(&gnl[inf_b->len[0] + 1],
			link->room_l->name, inf_b->len[1]) == 0) || (i == 2
			&& ft_strncmp(gnl, link->room_l->name, inf_b->len[0]) == 0))
			return ;
		link = link->next;
	}
	if ((i == 1 && ft_strncmp(&gnl[inf_b->len[0] + 1],
		link->room_l->name, inf_b->len[1]) == 0) || (i == 2
		&& ft_strncmp(gnl, link->room_l->name, inf_b->len[0]) == 0))
		return ;
	if (!(link->next = (t_link*)malloc(sizeof(t_link))))
		v_error(inf_b, "Error: malloc\n");
	link->next->room_l = (i == 1) ? (find_room(&gnl[inf_b->len[0] + 1],
		inf_b, inf_b->len[1])) : (find_room(gnl, inf_b, inf_b->len[0]));
	link->next->next = NULL;
}

void	fill_link(char *gnl, t_info *inf_b, int i)
{
	t_room	*room;
	char	*str;
	int		len;
	int		j;

	j = 0;
	str = (i == 1) ? (gnl) : (&gnl[inf_b->len[0] + 1]);
	len = (i == 1) ? (inf_b->len[0]) : (inf_b->len[1]);
	while (inf_b->room[j] && j < MAX_R
		&& ft_strncmp(str, inf_b->room[j]->name, len) != 0)
		j++;
	room = inf_b->room[j];
	if (room->link == NULL)
	{
		if (!(room->link = (t_link*)malloc(sizeof(t_link))))
			v_error(inf_b, "Error: malloc\n");
		room->link->room_l = (i == 1) ? (find_room(&gnl[inf_b->len[0] + 1],
			inf_b, inf_b->len[1])) : (find_room(gnl, inf_b, inf_b->len[0]));
		room->link->next = NULL;
	}
	else
		link_it(gnl, room, inf_b, i);
}

void	v_parcing_tube(char *gnl, t_info *inf_b)
{
	if (gnl[0] == '#')
	{
		if (v_commande(inf_b, gnl) != 0)
			v_error(inf_b, "Error: invalid line\n");
		return ;
	}
	if (inf_b->status != 0 || v_valid_line(gnl) != -1
		|| v_false_name_tube(gnl, inf_b, 1, 0) == FALSE)
		v_error(inf_b, "Error: invalid line\n");
	if (ft_strncmp(gnl, &gnl[inf_b->len[0] + 1], inf_b->len[0]) == 0
		&& ft_strlen(&gnl[inf_b->len[0] + 1]) == inf_b->len[0])
		v_error(inf_b, "Error: invalid line\n");
	fill_link(gnl, inf_b, 1);
	fill_link(gnl, inf_b, 2);
}

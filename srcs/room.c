/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adietric <adietric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 18:30:35 by adietric          #+#    #+#             */
/*   Updated: 2019/11/14 12:23:29 by adietric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		create_room(t_info *inf_b, char *gnl, int index_hach, int i)
{
	t_room				*room;

	room = NULL;
	if (inf_b->hach_table[index_hach] != NULL)
	{
		room = inf_b->hach_table[index_hach];
		while (inf_b->hach_table[index_hach]->next != NULL)
		{
			if (ft_strncmp(gnl, inf_b->hach_table[index_hach]->name, i) == 0)
				error(inf_b, "ERROR\n", gnl);
			inf_b->hach_table[index_hach] = inf_b->hach_table[index_hach]->next;
		}
		if (ft_strncmp(gnl, inf_b->hach_table[index_hach]->name, i) == 0)
			error(inf_b, "ERROR\n", gnl);
		inf_b->hach_table[index_hach]->next = new_room(inf_b, gnl, i);
		if (inf_b->hach_table[index_hach]->next->name[0] == 'L')
			error(inf_b, "ERROR\n", gnl);
		inf_b->hach_table[index_hach] = room;
	}
	else
	{
		inf_b->hach_table[index_hach] = new_room(inf_b, gnl, i);
		if (inf_b->hach_table[index_hach]->name[0] == 'L')
			error(inf_b, "ERROR\n", gnl);
	}
}

t_room		*new_room_n(t_info *inf_b, char *gnl, int length, t_room *new)
{
	while (gnl[length] && gnl[length] == ' ')
		length++;
	while (gnl[length] && gnl[length] != ' ')
		length++;
	new->x_y[1] = ft_atoi(&gnl[length]);
	new->preview = NULL;
	if (new->status == 1)
		new->mass = 0;
	if (new->status == 1)
		new->l_here = 1;
	if (new->status == 1)
		inf_b->the_start = new;
	if (new->status == -1)
		inf_b->the_end = new;
	return (new);
}

t_room		*new_room(t_info *inf_b, char *gnl, int length)
{
	t_room *new;

	if (!(new = (t_room*)malloc(sizeof(t_room))))
		error(inf_b, "error malloc\n", gnl);
	new->next = NULL;
	new->link = NULL;
	new->name = ft_strsub(gnl, 0, length);
	new->in_queue = 0;
	new->l_here = 0;
	new->nb_link = 0;
	new->mass = -1;
	new->modif = 0;
	new->skip = 0;
	new->rep_f = 0;
	new->taille_chemin = 0;
	new->t_ch_real = 0;
	new->status = inf_b->room_status;
	inf_b->room_status -= new->status;
	new->x_y[0] = ft_atoi(&gnl[length + 1]);
	length++;
	new = new_room_n(inf_b, gnl, length, new);
	return (new);
}

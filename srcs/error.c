/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adietric <adietric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 16:13:02 by flafonso          #+#    #+#             */
/*   Updated: 2019/11/12 17:08:55 by adietric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	free_stock(t_info *inf_b)
{
	int	i;
	int	det;

	i = -1;
	det = 0;
	if (inf_b->stock[0].path == NULL)
		det = 1;
	while (inf_b->stock[det].path && inf_b->stock[det].path[++i])
		free_path(inf_b->stock[det].path[i]);
	if (inf_b->stock[det].path)
		free(inf_b->stock[det].path);
	inf_b->stock[det].path = NULL;
}

void	free_link(t_link *link)
{
	if (link != NULL)
	{
		if (link->next != NULL)
			free_link(link->next);
		link->room_link = NULL;
		free(link);
	}
	return ;
}

void	free_hachcase(t_room *room)
{
	if (room->next != NULL)
		free_hachcase(room->next);
	if (room != NULL)
	{
		free_link(room->link);
		ft_strdel(&(room->name));
		room->preview = NULL;
		free(room);
	}
}

void	free_all(t_info *inf_b)
{
	int		i;
	char	*gnl;

	i = 0;
	free_stock(inf_b);
	while (i < BUF_HACH)
	{
		if (inf_b->hach_table[i] != NULL)
			free_hachcase(inf_b->hach_table[i]);
		i++;
	}
	ft_strdel(&(inf_b->map));
	while (get_next_line(0, &gnl) == 1)
		ft_strdel(&gnl);
}

void	error(t_info *inf_b, char *str, char *gnl)
{
	ft_strdel(&gnl);
	ft_putstr(str);
	free_all(inf_b);
	exit(EXIT_FAILURE);
}

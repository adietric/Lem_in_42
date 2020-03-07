/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adietric <adietric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 19:17:45 by adietric          #+#    #+#             */
/*   Updated: 2019/10/05 14:53:13 by adietric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	reset(t_stock *stock)
{
	stock->step = 0;
	stock->tot_t_ch = 0;
	stock->p_index = 0;
	stock->nb_ch = 0;
}

void	free_path(t_path *path)
{
	if (path->next != NULL)
	{
		if (path->room->status == 1)
			path->next->room->rep_f = 0;
		free_path(path->next);
	}
	if (path != NULL)
	{
		path->room = NULL;
		free(path);
	}
}

void	choose(t_info *inf_b)
{
	int		i;
	int		det;

	i = 0;
	det = 0;
	if (!(inf_b->stock[0].path && inf_b->stock[1].path))
		return ;
	if (inf_b->stock[0].step < inf_b->stock[1].step)
		det = 1;
	while (i < inf_b->stock[det].p_index)
	{
		free_path(inf_b->stock[det].path[i]);
		i++;
	}
	free(inf_b->stock[det].path);
	inf_b->stock[det].path = NULL;
	reset(&inf_b->stock[det]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lem_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adietric <adietric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 15:07:54 by flafonso          #+#    #+#             */
/*   Updated: 2019/11/14 14:27:12 by adietric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void		lem_forward_2(t_info *inf_b, t_path *path, t_room *from)
{
	if (from->status == 1 && (int)path->rep_f > 0)
	{
		if (path->room->status == -1)
			inf_b->nb_on_end++;
		path->room->l_here = inf_b->l_name;
		inf_b->l_name++;
		path->rep_f--;
		print_lem(path->room, inf_b);
	}
	else if (path->room->status == -1 && from->l_here != 0)
	{
		path->room->l_here = from->l_here;
		inf_b->nb_on_end++;
		from->l_here = 0;
		print_lem(path->room, inf_b);
	}
	else if (from->status != 1 && path->room->status != -1 && from->l_here != 0)
	{
		path->room->l_here = from->l_here;
		from->l_here = 0;
		print_lem(path->room, inf_b);
	}
}

void			run_2(t_info *inf_b, t_path *path, t_path *from)
{
	if (path == NULL)
		return ;
	if (path->next == NULL || path->room->status == -1)
	{
		if (from->room->l_here != 0)
			lem_forward_2(inf_b, path, from->room);
		return ;
	}
	run_2(inf_b, path->next, path);
	if (from->room->l_here != 0)
		lem_forward_2(inf_b, path, from->room);
}

void			new_lem_run(t_info *inf_b)
{
	int		i;
	int		det;

	det = 0;
	if (inf_b->stock[0].path == NULL)
		det = 1;
	if (inf_b->stock[1].path == NULL && inf_b->stock[0].path == NULL)
		return ;
	ft_putchar('\n');
	while (inf_b->nb_on_end != inf_b->nb_f)
	{
		i = 0;
		inf_b->grrr = 0;
		while (i < inf_b->stock[det].p_index)
		{
			if (inf_b->stock[det].path[i]->ban != 1)
				run_2(inf_b, inf_b->stock[det].path[i]->next,
				inf_b->stock[det].path[i]);
			i++;
		}
		ft_putchar('\n');
	}
}

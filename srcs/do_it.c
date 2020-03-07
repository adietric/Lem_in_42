/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_it.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adietric <adietric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 11:36:27 by flafonso          #+#    #+#             */
/*   Updated: 2019/11/14 14:13:26 by adietric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	maj(t_info *inf_b, float tot_rep_f)
{
	t_link	*link;

	tot_rep_f = 0;
	link = inf_b->the_start->link;
	while (link != NULL)
	{
		if (link->room_link->rep_f <= 0 && link->room_link->taille_chemin != 0)
		{
			inf_b->tot_t_ch -= link->room_link->taille_chemin;
			link->room_link->taille_chemin = 0;
			inf_b->nb_chemin -= 1;
		}
		link = link->next;
	}
}

float	do_it(t_info *inf_b, float tot_rep_f, t_link *link)
{
	tot_rep_f = 0;
	while (link)
	{
		if (link->room_link->taille_chemin > 0)
		{
			link->room_link->rep_f = (((double)inf_b->nb_f
			+ (double)inf_b->tot_t_ch - ((double)inf_b->nb_chemin
			* (double)link->room_link->taille_chemin))
			/ (double)inf_b->nb_chemin);
			tot_rep_f = (int)(link->room_link->rep_f) + (int)tot_rep_f;
			if (link->room_link->rep_f <= 0)
			{
				link->room_link->rep_f = 0;
				inf_b->wrong = 1;
			}
		}
		link = link->next;
	}
	if (inf_b->wrong == 1)
	{
		inf_b->wrong = 0;
		maj(inf_b, tot_rep_f);
		tot_rep_f = do_it(inf_b, tot_rep_f, inf_b->the_start->link);
	}
	return ((int)tot_rep_f);
}

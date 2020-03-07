/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sum.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafonso <flafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 16:09:33 by flafonso          #+#    #+#             */
/*   Updated: 2019/11/14 16:13:36 by flafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	del_bad_path(t_stock *stock, int i)
{
	stock->path[i]->ban = 1;
	stock->nb_ch--;
	stock->tot_t_ch -= stock->path[i]->t_ch;
}

int		sum_flux(t_info *inf_b)
{
	int		i;
	t_link	*link;

	link = inf_b->the_start->link;
	i = 0;
	while (link)
	{
		if (link->flux == 1)
			i++;
		link = link->next;
	}
	return (i);
}

int		sum_step(t_stock *stock)
{
	int		step;
	int		tmp;
	int		i;

	step = 0;
	tmp = 0;
	i = 0;
	while (i < stock->p_index)
	{
		if (stock->path[i]->ban != 1)
		{
			tmp = (int)stock->path[i]->next->rep_f + stock->path[i]->t_ch - 1;
			if (tmp > step)
				step = tmp;
		}
		i++;
	}
	return (step);
}

void	sum_rep_f(t_info *inf_b, t_stock *stock)
{
	int		i;

	i = 0;
	while (i < stock->p_index)
	{
		if (stock->path[i]->ban != 1)
		{
			stock->path[i]->next->rep_f = (((double)inf_b->nb_f +
			(double)stock->tot_t_ch - ((double)stock->nb_ch *
			(double)stock->path[i]->t_ch)) / (double)stock->nb_ch);
			if ((int)stock->path[i]->next->rep_f <= 0)
			{
				del_bad_path(stock, i);
				return (sum_rep_f(inf_b, stock));
			}
		}
		i++;
	}
	return ;
}

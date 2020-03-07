/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adietric <adietric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 11:59:13 by adietric          #+#    #+#             */
/*   Updated: 2019/11/12 16:31:09 by adietric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	init_n(t_info *inf_b)
{
	inf_b->the_start = NULL;
	inf_b->the_end = NULL;
	inf_b->buf_map = 1024;
	inf_b->stock[0].nb_ch = 0;
	inf_b->stock[0].tot_t_ch = 0;
	inf_b->stock[0].step = 0;
	inf_b->stock[0].p_index = 0;
	inf_b->stock[0].path = NULL;
	inf_b->stock[1].nb_ch = 0;
	inf_b->stock[1].tot_t_ch = 0;
	inf_b->stock[1].step = 0;
	inf_b->stock[0].p_index = 1;
	inf_b->stock[1].path = NULL;
	if (!(inf_b->map = ft_strnew(inf_b->buf_map)))
		error(inf_b, "error malloc map_buf\n", NULL);
	inf_b->index_buf = 0;
}

void	init(t_info *inf_b)
{
	int		i;

	i = -1;
	while (++i < BUF_HACH)
		inf_b->hach_table[i] = NULL;
	inf_b->l_name = 1;
	inf_b->tot_t_ch = 0;
	inf_b->nb_f = 0;
	inf_b->nb_r = 0;
	inf_b->first = 0;
	inf_b->nb_chemin = 0;
	inf_b->nb_on_end = 0;
	inf_b->wrong = 1;
	inf_b->grrr = 1;
	inf_b->det_qvalue = 1;
	inf_b->len[0] = 0;
	inf_b->len[1] = 0;
	inf_b->room_start = 0;
	inf_b->room_status = 0;
	inf_b->room_end = 0;
	init_n(inf_b);
}

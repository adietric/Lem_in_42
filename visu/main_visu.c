/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafonso <flafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 16:24:48 by adietric          #+#    #+#             */
/*   Updated: 2019/11/14 16:47:27 by flafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visu.h"

int		ft_nbrlen(int n_cpy)
{
	int nbrlen;

	nbrlen = 0;
	if (n_cpy == 0)
		return (1);
	while (n_cpy != 0)
	{
		n_cpy = n_cpy / 10;
		nbrlen++;
	}
	return (nbrlen);
}

void	create_ant(t_info *inf_b)
{
	int		i;
	int		j;

	j = 0;
	i = -1;
	if (inf_b->nb_f <= 0)
		v_error(inf_b, "Error: invalid ant number\n");
	if (!(inf_b->ant = (t_ant *)malloc(sizeof(t_ant) * inf_b->nb_f)))
		v_error(inf_b, "Error: malloc\n");
	while (j < MAX_R && inf_b->room[j]->status != 1)
		j++;
	while (++i < inf_b->nb_f)
	{
		inf_b->ant[i].name = i + 1;
		inf_b->ant[i].room = inf_b->room[j];
		inf_b->ant[i].vec[0] = 0;
		inf_b->ant[i].vec[1] = 0;
		inf_b->ant[i].x = (float)inf_b->room[j]->x;
		inf_b->ant[i].y = (float)inf_b->room[j]->y;
		inf_b->ant[i].need_move = 0;
		inf_b->ant[i].angle = 0;
	}
}

void	v_new_room(t_info *inf_b, char *str, unsigned int len)
{
	t_room *new;

	if (!(new = (t_room *)malloc(sizeof(t_room))))
		v_error(inf_b, "Error: malloc\n");
	new->name = ft_strsub(str, 0, len);
	new->x = ft_atoi(&str[len]);
	new->y = ft_atoi(&str[len + ft_nbrlen(new->x) + 1]);
	if (new->x > inf_b->tab_xy[2])
		inf_b->tab_xy[2] = new->x;
	if (new->y > inf_b->tab_xy[3])
		inf_b->tab_xy[3] = new->y;
	if (new->x < inf_b->tab_xy[0])
		inf_b->tab_xy[0] = new->x;
	if (new->y < inf_b->tab_xy[1])
		inf_b->tab_xy[1] = new->y;
	new->just_one = 0;
	new->status = inf_b->status;
	inf_b->status = 0;
	new->link = NULL;
	if (inf_b->r_index >= MAX_R)
		v_error(inf_b, "Error: excess room\n");
	inf_b->room[inf_b->r_index] = new;
	inf_b->r_index++;
}

int		main(void)
{
	t_info	inf_b;
	int		i;
	int		max_mix;
	int		may_miy;

	i = -1;
	init(&inf_b);
	if (v_read_file(&inf_b) != 1)
		v_error(&inf_b, "Error: invalid map\n");
	create_ant(&inf_b);
	max_mix = inf_b.tab_xy[2] - inf_b.tab_xy[0];
	may_miy = inf_b.tab_xy[3] - inf_b.tab_xy[1];
	inf_b.tab_xy[4] = (2000 - 600) / ((max_mix != 0) ? (max_mix) : (1));
	inf_b.tab_xy[5] = (1300 - 200) / ((may_miy != 0) ? (may_miy) : (1));
	while (++i < MAX_R && inf_b.room[i])
		set_rect_first(&inf_b, inf_b.room[i]);
	lem_move(&inf_b, &inf_b.sdl);
	endsdl(&inf_b.sdl, &inf_b);
	return (0);
}

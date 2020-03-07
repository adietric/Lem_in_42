/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sum.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafonso <flafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 12:34:32 by flafonso          #+#    #+#             */
/*   Updated: 2019/11/11 16:50:20 by flafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visu.h"

int			f_norme(t_info *inf_b)
{
	inf_b->s_e_ok[0] = 0;
	return (0);
}

void		give_inf_to_ant(t_info *inf_b, int lem, int part)
{
	t_room	*room;

	room = NULL;
	if (lem >= inf_b->s_e_ok[1] || lem < 0)
		sdl_failure(inf_b, &(inf_b->sdl));
	if (part == 1)
	{
		inf_b->ant[lem].x = (float)inf_b->ant[lem].room->x;
		inf_b->ant[lem].y = (float)inf_b->ant[lem].room->y;
	}
	else
	{
		room = inf_b->room[inf_b->s_e_ok[0]];
		inf_b->ant[lem].room = room;
		inf_b->ant[lem].vec[0] = ((float)room->x - inf_b->ant[lem].x) / 40;
		inf_b->ant[lem].vec[1] = ((float)room->y - inf_b->ant[lem].y) / 40;
		inf_b->ant[lem].need_move = 1;
	}
}

void		sum_angle(t_info *inf_b, int lem)
{
	float	x;
	float	y;

	x = inf_b->ant[lem].vec[0];
	y = inf_b->ant[lem].vec[1];
	inf_b->ant[lem].angle = y < 0 ? -acos(x / (sqrt((x * x) + (y * y)) + 1)) :
										acos(x / (sqrt((x * x) + (y * y)) + 1));
	inf_b->ant[lem].angle *= (180 / 3.14159265358979323846);
}

int			sum_vec(t_info *inf_b, t_my_sdl *sdl, char *gnl, int i)
{
	SDL_Rect	dst;
	t_room		*room;
	int			j;
	int			lem;

	j = f_norme(inf_b);
	while (gnl[i] && gnl[i] != 'L')
		i++;
	lem = ft_atoi(&gnl[i + 1]) - 1;
	give_inf_to_ant(inf_b, lem, 1);
	i += (ft_nbrlen(lem + 1) + 1);
	dst = give_rect(50, 50, inf_b->ant[lem].x, inf_b->ant[lem].y);
	while (gnl[i + j] && gnl[i + j] != ' ')
		j++;
	while (inf_b->s_e_ok[0] < inf_b->r_index && ft_strncmp(&gnl[i + 1],
			inf_b->room[inf_b->s_e_ok[0]]->name, j - 1) != 0)
		inf_b->s_e_ok[0]++;
	if (inf_b->s_e_ok[0] >= inf_b->r_index)
		sdl_failure(inf_b, sdl);
	give_inf_to_ant(inf_b, lem, 2);
	i += j;
	sum_angle(inf_b, lem);
	SDL_RenderCopyEx(sdl->renderer, sdl->texture, NULL, &dst,
					inf_b->ant[lem].angle, NULL, SDL_FLIP_NONE);
	return (i);
}

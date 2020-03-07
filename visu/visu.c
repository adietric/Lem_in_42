/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafonso <flafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:51:46 by flafonso          #+#    #+#             */
/*   Updated: 2019/11/14 15:02:04 by flafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visu.h"

void	set_rect_first(t_info *inf_b, t_room *room)
{
	room->x = 50 + inf_b->tab_xy[4] * (room->x - inf_b->tab_xy[0]);
	room->y = 50 + inf_b->tab_xy[5] * (room->y - inf_b->tab_xy[1]);
}

void	set_rect(t_info *inf_b, t_room *room, t_my_sdl *sdl)
{
	sdl->rect.x = room->x;
	sdl->rect.y = room->y;
	sdl->rect.h = 50;
	sdl->rect.w = 50;
}

void	make_link(t_info *inf_b, t_my_sdl *sdl)
{
	int		i;
	t_link	*link;

	link = NULL;
	i = -1;
	while (++i < MAX_R && inf_b->room[i])
	{
		link = inf_b->room[i]->link;
		while (link != NULL)
		{
			if (SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255) != 0)
				v_error(inf_b, "Error: sdl_color\n");
			if (SDL_RenderDrawLine(sdl->renderer, 25 + inf_b->room[i]->x
				, 25 + inf_b->room[i]->y, 25 + link->room_l->x
				, 25 + link->room_l->y) != 0)
				v_error(inf_b, "Error: DrawLine\n");
			link = link->next;
		}
	}
}

void	fill_map(t_info *inf_b, t_my_sdl *sdl)
{
	int		i;

	i = -1;
	make_link(inf_b, sdl);
	while (++i < MAX_R && inf_b->room[i])
	{
		set_rect(inf_b, inf_b->room[i], sdl);
		if (SDL_SetRenderDrawColor(sdl->renderer, 100, 100, 100, 255) != 0)
			v_error(inf_b, "Error: sdl_color\n");
		if (inf_b->room[i]->status == -1
			&& SDL_SetRenderDrawColor(sdl->renderer, 255, 0, 0, 255) != 0)
			v_error(inf_b, "Error: sdl_color\n");
		if (inf_b->room[i]->status == 1
			&& SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 255, 255) != 0)
			v_error(inf_b, "Error: sdl_color\n");
		if (SDL_RenderFillRect(sdl->renderer, &(sdl->rect)))
			v_error(inf_b, "Error: sdl_rect\n");
	}
	sdl->rect = give_rect(1300, 450, 1550, 0);
	if ((SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255) != 0)
		|| (SDL_RenderFillRect(sdl->renderer, &(sdl->rect))))
		v_error(inf_b, "Error: sdl_color || sdl_rect\n");
}

void	print_visu(t_info *inf_b, t_my_sdl *sdl)
{
	if (sdl_event(sdl, inf_b) == 1)
		v_error(inf_b, "");
	if (SDL_SetRenderDrawColor(sdl->renderer, 111, 111, 135, 255) != 0)
		v_error(inf_b, "Error: sdl_color\n");
	if (SDL_RenderClear(sdl->renderer) != 0)
		v_error(inf_b, "Error: sdl_clear\n");
	fill_map(inf_b, sdl);
	print_text(inf_b, sdl);
	sdl->rect = give_rect(2, 350, 1600, 400);
	if (SDL_SetRenderDrawColor(sdl->renderer, 255, 255, 255, 255) != 0)
		v_error(inf_b, "Error: sdl_color\n");
	if (SDL_RenderFillRect(sdl->renderer, &(sdl->rect)))
		v_error(inf_b, "Error: sdl_rect\n");
	sdl->rect.y = 900;
	if (SDL_RenderFillRect(sdl->renderer, &(sdl->rect)))
		v_error(inf_b, "Error: sdl_rect\n");
}

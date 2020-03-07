/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafonso <flafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:10:22 by flafonso          #+#    #+#             */
/*   Updated: 2019/11/14 14:59:23 by flafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visu.h"

void	suc_or_fail(t_info *inf_b, t_my_sdl *sdl)
{
	SDL_Rect	text_rect;
	SDL_Color	color_bg;

	text_rect.y = 575;
	text_rect.x = 775;
	color_bg = give_rgba(0, 255, 0, 255);
	print_visu(inf_b, sdl);
	if (inf_b->nb_f == 0)
		print_end(sdl, color_bg, text_rect, " Success ");
	else
	{
		color_bg.r = 255;
		color_bg.g = 0;
		print_end(sdl, color_bg, text_rect, " Failure ");
	}
	SDL_RenderPresent(sdl->renderer);
	SDL_Delay(250);
	print_visu(inf_b, sdl);
	SDL_RenderPresent(sdl->renderer);
	SDL_Delay(250);
}

void	load_image(t_info *inf_b, char *str)
{
	SDL_Surface		*tmp;
	Uint32			colorkey;
	SDL_Texture		*texture;

	tmp = NULL;
	tmp = SDL_LoadBMP(str);
	if (tmp == NULL)
		v_error(inf_b, "Error: create_surface\n");
	colorkey = SDL_MapRGB(tmp->format, 13, 255, 0);
	SDL_SetColorKey(tmp, SDL_TRUE, colorkey);
	inf_b->sdl.texture = SDL_CreateTextureFromSurface(inf_b->sdl.renderer, tmp);
	SDL_FreeSurface(tmp);
	if (inf_b->sdl.texture == NULL)
		v_error(inf_b, "Error: create_texture\n");
}

void	reset_pos(t_info *inf_b, int nb_ff)
{
	int		j;

	j = -1;
	while (++j < nb_ff)
		if (inf_b->ant[j].need_move == 1)
		{
			inf_b->ant[j].need_move = 0;
			inf_b->ant[j].x = (float)inf_b->ant[j].room->x;
			inf_b->ant[j].y = (float)inf_b->ant[j].room->y;
		}
}

void	lem_fps(t_info *inf_b, t_my_sdl *sdl, int nb_ff)
{
	SDL_Rect	dst;
	int			i;
	int			j;

	i = -1;
	dst = give_rect(50, 50, 0, 0);
	while (++i < 40)
	{
		print_visu(inf_b, sdl);
		j = -1;
		while (++j < nb_ff)
			if (inf_b->ant[j].need_move == 1)
			{
				inf_b->ant[j].x += inf_b->ant[j].vec[0];
				inf_b->ant[j].y += inf_b->ant[j].vec[1];
				dst.x = (int)inf_b->ant[j].x;
				dst.y = (int)inf_b->ant[j].y;
				SDL_RenderCopyEx(sdl->renderer, sdl->texture, NULL, &dst,
								inf_b->ant[j].angle, NULL, SDL_FLIP_NONE);
				if (inf_b->ant[j].room->status == -1 && i == 39)
					inf_b->nb_f--;
			}
		SDL_RenderPresent(sdl->renderer);
		SDL_Delay(sdl->delay);
	}
}

void	lem_move(t_info *inf_b, t_my_sdl *sdl)
{
	SDL_Rect	dst;
	char		*gnl;
	int			i;

	inf_b->s_e_ok[1] = inf_b->nb_f;
	inf_b->status = 0;
	load_image(inf_b, "./visu/images/ant10.bmp");
	while (get_next_line(0, &gnl) == 1)
	{
		inf_b->status++;
		i = 0;
		print_visu(inf_b, sdl);
		while (gnl[i] != '\0')
			i = sum_vec(inf_b, sdl, gnl, i);
		SDL_RenderPresent(sdl->renderer);
		SDL_Delay(sdl->delay);
		lem_fps(inf_b, sdl, inf_b->s_e_ok[1]);
		reset_pos(inf_b, inf_b->s_e_ok[1]);
		ft_strdel(&gnl);
	}
	while (sdl_wait_end())
		suc_or_fail(inf_b, sdl);
}

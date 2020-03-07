/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafonso <flafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:57:43 by flafonso          #+#    #+#             */
/*   Updated: 2019/11/14 15:01:29 by flafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visu.h"

void		print_end(t_my_sdl *sdl, SDL_Color color_bg,
				SDL_Rect text_rect, char *str)
{
	SDL_Color			color_fg;
	SDL_Surface			*tsur;
	SDL_Texture			*texture;
	TTF_Font			*font;

	color_fg = give_rgba(255, 255, 255, 255);
	font = TTF_OpenFont("./visu/images/SuperMario256.ttf", 150);
	TTF_SizeText(sdl->font, str, &(text_rect.w), &(text_rect.h));
	text_rect.w *= 5;
	text_rect.h *= 3;
	text_rect.x -= text_rect.w / 2;
	tsur = TTF_RenderText_Blended(font, str, color_bg);
	texture = SDL_CreateTextureFromSurface(sdl->renderer, tsur);
	SDL_FreeSurface(tsur);
	SDL_RenderCopy(sdl->renderer, texture, NULL, &text_rect);
	text_rect.x += text_rect.w;
	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);
}

SDL_Rect	give_rect(int h, int w, int x, int y)
{
	SDL_Rect	rect;

	rect.h = h;
	rect.w = w;
	rect.x = x;
	rect.y = y;
	return (rect);
}

SDL_Color	give_rgba(int r, int g, int b, int a)
{
	SDL_Color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color);
}

void		init_visu(t_info *inf_b, t_my_sdl *sdl)
{
	sdl->window = NULL;
	sdl->renderer = NULL;
	sdl->texture = NULL;
	sdl->font = NULL;
	sdl->delay = 25;
	sdl->w_l = 2000;
	sdl->w_h = 1300;
	sdl->rect = give_rect(0, 0, 0, 0);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
		v_error(inf_b, "Error: sdl_init\n");
	if ((TTF_Init()))
		v_error(inf_b, "Error: TTF_init\n");
	if (!(sdl->font = TTF_OpenFont("./visu/images/Signatra.ttf", 40)))
		v_error(inf_b, "Error: FONT_init !\n");
	sdl->window = SDL_CreateWindow("Visualisateur du turfu",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		sdl->w_l, sdl->w_h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	sdl->renderer = SDL_CreateRenderer(sdl->window, 1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void		init(t_info *inf_b)
{
	int		i;

	i = -1;
	inf_b->nb_f = 0;
	while (++i < MAX_R)
		inf_b->room[i] = NULL;
	inf_b->ant = NULL;
	inf_b->r_index = 0;
	inf_b->status = 0;
	inf_b->s_e_ok[0] = 0;
	inf_b->s_e_ok[1] = 0;
	inf_b->len[0] = 0;
	inf_b->len[1] = 0;
	inf_b->tab_xy[0] = 0;
	inf_b->tab_xy[1] = 0;
	inf_b->tab_xy[2] = 0;
	inf_b->tab_xy[3] = 0;
	inf_b->tab_xy[4] = 0;
	inf_b->tab_xy[5] = 0;
	init_visu(inf_b, &inf_b->sdl);
}

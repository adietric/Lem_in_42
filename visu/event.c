/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafonso <flafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:48:53 by flafonso          #+#    #+#             */
/*   Updated: 2019/11/15 13:31:46 by flafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visu.h"

void	print_pause(t_my_sdl *sdl, SDL_Color color_fg,
					SDL_Color color_bg, SDL_Rect text_rect)
{
	SDL_Surface			*tsur_pause;
	SDL_Texture			*texture_p;
	TTF_Font			*font;

	font = TTF_OpenFont("./visu/images/Signatra.ttf", 50);
	TTF_SizeText(font, " Pause ", &(text_rect.w), &(text_rect.h));
	text_rect.h += 10;
	text_rect.x -= text_rect.w / 2;
	tsur_pause = TTF_RenderText_Shaded(font, " Pause ", color_fg, color_bg);
	texture_p = SDL_CreateTextureFromSurface(sdl->renderer, tsur_pause);
	SDL_FreeSurface(tsur_pause);
	SDL_RenderCopy(sdl->renderer, texture_p, NULL, &text_rect);
	text_rect.x += text_rect.w;
	TTF_CloseFont(font);
	SDL_DestroyTexture(texture_p);
}

int		sdl_wait_end(void)
{
	SDL_Event	event;

	SDL_PollEvent(&event);
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		return (0);
	if (event.type == SDL_QUIT)
		return (0);
	return (1);
}

void	sdl_sleep(t_my_sdl *sdl)
{
	SDL_Rect	text_rect;
	SDL_Color	color_fg;
	SDL_Color	color_bg;
	SDL_Event	event;
	int			quit;

	text_rect = give_rect(0, 0, 1775, 1050);
	color_fg = give_rgba(0, 0, 0, 255);
	color_bg = give_rgba(255, 255, 255, 255);
	quit = 1;
	print_pause(sdl, color_fg, color_bg, text_rect);
	SDL_RenderPresent(sdl->renderer);
	while (quit == 1)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
			quit = 0;
	}
}

int		sdl_event(t_my_sdl *sdl, t_info *inf_b)
{
	SDL_Event	event;

	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
		return (1);
	if (event.type == SDL_KEYDOWN)
	{
		if (sdl->delay - 2 >= 0 && event.key.keysym.sym == SDLK_UP)
			sdl->delay -= 2;
		if (sdl->delay + 2 <= 450 && event.key.keysym.sym == SDLK_DOWN)
			sdl->delay += 2;
		if (event.key.keysym.sym == SDLK_SPACE)
			sdl_sleep(sdl);
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			endsdl(sdl, inf_b);
			exit(EXIT_SUCCESS);
		}
	}
	return (0);
}

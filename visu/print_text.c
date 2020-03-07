/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafonso <flafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:50:33 by flafonso          #+#    #+#             */
/*   Updated: 2019/11/14 16:23:41 by flafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visu.h"

void	draw_text(t_info *inf_b, t_my_sdl *sdl, SDL_Rect *text_rect, char *str)
{
	SDL_Color			color_fg;
	SDL_Surface			*tsur;
	SDL_Texture			*texture_one;
	TTF_Font			*tmp_font;

	color_fg = give_rgba(255, 255, 255, 255);
	if ((str && str[0] == 'b')
		&& (!(tmp_font = TTF_OpenFont("./visu/images/Signatra.ttf", 25))))
		v_error(inf_b, "Error: FONT_init\n");
	if ((str && str[0] != 'b')
		&& (!(tmp_font = TTF_OpenFont("./visu/images/Signatra.ttf", 40))))
		v_error(inf_b, "Error: FONT_init\n");
	TTF_SizeText(tmp_font, str, &(text_rect->w), &(text_rect->h));
	text_rect->y += 75;
	tsur = TTF_RenderText_Blended(tmp_font, str, color_fg);
	texture_one = SDL_CreateTextureFromSurface(sdl->renderer, tsur);
	SDL_FreeSurface(tsur);
	SDL_RenderCopy(sdl->renderer, texture_one, NULL, text_rect);
	SDL_DestroyTexture(texture_one);
	TTF_CloseFont(tmp_font);
}

void	draw_title(t_info *inf_b, t_my_sdl *sdl,
					SDL_Rect text_rect, SDL_Color color_fg)
{
	SDL_Surface			*tsur_fr;
	SDL_Texture			*texture_one;
	TTF_Font			*font;

	font = TTF_OpenFont("./visu/images/SuperMario256.ttf", 100);
	TTF_SizeText(font, "LEM-IN", &(text_rect.w), &(text_rect.h));
	tsur_fr = TTF_RenderText_Blended(font, "LEM-IN", color_fg);
	texture_one = SDL_CreateTextureFromSurface(sdl->renderer, tsur_fr);
	SDL_FreeSurface(tsur_fr);
	SDL_RenderCopy(sdl->renderer, texture_one, NULL, &text_rect);
	SDL_DestroyTexture(texture_one);
	TTF_CloseFont(font);
}

void	nb_line(t_info *inf_b, t_my_sdl *sdl,
				SDL_Rect text_rect, SDL_Color color_fg)
{
	SDL_Surface			*tsur_fr;
	SDL_Surface			*tsur_nbl;
	SDL_Texture			*texture_one;
	SDL_Texture			*texture_two;
	char				*nbl;

	tsur_fr = TTF_RenderText_Blended(sdl->font, "Nombre d'etapes : ",
									color_fg);
	nbl = ft_itoa(inf_b->status);
	if (nbl == NULL)
		v_error(inf_b, "itoa\n");
	tsur_nbl = TTF_RenderText_Blended(sdl->font, nbl, color_fg);
	texture_one = SDL_CreateTextureFromSurface(sdl->renderer, tsur_fr);
	texture_two = SDL_CreateTextureFromSurface(sdl->renderer, tsur_nbl);
	SDL_FreeSurface(tsur_fr);
	SDL_FreeSurface(tsur_nbl);
	SDL_RenderCopy(sdl->renderer, texture_one, NULL, &text_rect);
	text_rect.x = 1900;
	TTF_SizeText(sdl->font, nbl, &(text_rect.w), &(text_rect.h));
	SDL_RenderCopy(sdl->renderer, texture_two, NULL, &text_rect);
	SDL_DestroyTexture(texture_one);
	ft_strdel(&nbl);
}

void	ant_count(t_info *inf_b, t_my_sdl *sdl,
					SDL_Rect text_rect, SDL_Color color_fg)
{
	SDL_Surface			*tsur_fr;
	SDL_Surface			*tsur_nbf;
	SDL_Texture			*texture_one;
	SDL_Texture			*texture_two;
	char				*nbf;

	tsur_fr = TTF_RenderText_Blended(sdl->font, "Fourmi(s) restante(s) : ",
									color_fg);
	nbf = ft_itoa(inf_b->nb_f);
	if (nbf == NULL)
		v_error(inf_b, "itoa\n");
	tsur_nbf = TTF_RenderText_Blended(sdl->font, nbf, color_fg);
	texture_one = SDL_CreateTextureFromSurface(sdl->renderer, tsur_fr);
	texture_two = SDL_CreateTextureFromSurface(sdl->renderer, tsur_nbf);
	SDL_FreeSurface(tsur_fr);
	SDL_FreeSurface(tsur_nbf);
	SDL_RenderCopy(sdl->renderer, texture_one, NULL, &text_rect);
	text_rect.x = 1900;
	TTF_SizeText(sdl->font, nbf, &(text_rect.w), &(text_rect.h));
	SDL_RenderCopy(sdl->renderer, texture_two, NULL, &text_rect);
	SDL_DestroyTexture(texture_one);
	ft_strdel(&nbf);
}

void	print_text(t_info *inf_b, t_my_sdl *sdl)
{
	SDL_Color	color_fg;
	SDL_Rect	t_rect;

	color_fg = give_rgba(255, 255, 255, 255);
	t_rect.y = 200;
	t_rect.x = 1600;
	TTF_SizeText(sdl->font, "Fourmie(s) restante(s) : ",
				&(t_rect.w), &(t_rect.h));
	ant_count(inf_b, sdl, t_rect, color_fg);
	t_rect.y = 275;
	TTF_SizeText(sdl->font, "Nombre d'etapes : ", &(t_rect.w), &(t_rect.h));
	nb_line(inf_b, sdl, t_rect, color_fg);
	t_rect.y = 25;
	t_rect.x = 1580;
	draw_title(inf_b, sdl, t_rect, color_fg);
	t_rect.y = 450;
	t_rect.x = 1625;
	draw_text(inf_b, sdl, &t_rect, "ESC : Quitte");
	draw_text(inf_b, sdl, &t_rect, "ESP : Pause/Play");
	draw_text(inf_b, sdl, &t_rect, "Fleche haut : Acceleration");
	draw_text(inf_b, sdl, &t_rect, "Fleche bas : Deceleration");
	t_rect.x = 1575;
	t_rect.y = 1180;
	draw_text(inf_b, sdl, &t_rect, "by adietric & flafonso");
}

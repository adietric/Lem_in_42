/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafonso <flafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 16:13:02 by flafonso          #+#    #+#             */
/*   Updated: 2019/11/11 13:10:13 by flafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visu.h"

void	sdl_failure(t_info *inf_b, t_my_sdl *sdl)
{
	while (sdl_wait_end())
		suc_or_fail(inf_b, sdl);
	endsdl(sdl, inf_b);
	exit(EXIT_SUCCESS);
}

void	free_link(t_link *link)
{
	if (link != NULL)
	{
		if (link->next != NULL)
			free_link(link->next);
		link->room_l = NULL;
		free(link);
	}
	return ;
}

void	free_all(t_info *inf_b)
{
	inf_b->r_index = 0;
	if (inf_b->ant)
		free(inf_b->ant);
	while (inf_b->room[inf_b->r_index])
	{
		free_link(inf_b->room[inf_b->r_index]->link);
		ft_strdel(&(inf_b->room[inf_b->r_index]->name));
		free(inf_b->room[inf_b->r_index]);
		inf_b->r_index++;
	}
}

void	endsdl(t_my_sdl *sdl, t_info *inf_b)
{
	TTF_CloseFont(sdl->font);
	if (sdl->texture)
		SDL_DestroyTexture(sdl->texture);
	if (sdl->renderer)
		SDL_DestroyRenderer(sdl->renderer);
	if (sdl->window)
		SDL_DestroyWindow(sdl->window);
	TTF_Quit();
	SDL_Quit();
	free_all(inf_b);
}

void	v_error(t_info *inf_b, char *str)
{
	ft_putstr(str);
	endsdl(&inf_b->sdl, inf_b);
	exit(EXIT_FAILURE);
}

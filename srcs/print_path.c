/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafonso <flafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:54:30 by adietric          #+#    #+#             */
/*   Updated: 2019/11/14 19:29:15 by flafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	print_path_2(t_path *path)
{
	while (path->next)
	{
		ft_putstr("[");
		ft_putstr(path->room->name);
		ft_putstr("] -> ");
		path = path->next;
	}
	ft_putstr("\033[1;31m[");
	ft_putstr(path->room->name);
	ft_putstr("]\033[0m\n");
}

void	print_path(t_info *inf_b)
{
	int			nb;
	int			det;
	int			i;

	nb = 0;
	det = 0;
	i = 0;
	if (inf_b->stock[0].path == NULL)
		det = 1;
	ft_putstr("\nNombre total de PATH : ");
	ft_putnbr(inf_b->stock[det].nb_ch);
	while (i < inf_b->stock[det].nb_ch)
	{
		ft_putstr("\n\n\033[1;39mPATH n˚");
		ft_putnbr(++nb);
		ft_putstr(" : \033[1;34m\n[");
		ft_putstr(inf_b->stock[det].path[i]->room->name);
		ft_putstr("]\033[38;5;246m -> ");
		print_path_2(inf_b->stock[det].path[i]->next);
		i++;
	}
}

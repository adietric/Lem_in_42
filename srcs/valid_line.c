/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adietric <adietric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:06:37 by adietric          #+#    #+#             */
/*   Updated: 2019/11/14 12:30:53 by adietric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		commande(t_info *inf_b, char *gnl)
{
	if (ft_strcmp(gnl, "##start") == 0)
	{
		if (inf_b->room_start == 1 || inf_b->room_status != 0)
			error(inf_b, "ERROR\n", gnl);
		inf_b->room_status = 1;
		inf_b->room_start = 1;
		return (1);
	}
	if (ft_strcmp(gnl, "##end") == 0)
	{
		if (inf_b->room_end == 1 || inf_b->room_status != 0)
			error(inf_b, "ERROR\n", gnl);
		inf_b->room_status = -1;
		inf_b->room_end = 1;
		return (-1);
	}
	return (0);
}

int		check_x_y(char *gnl)
{
	int		i;

	i = 0;
	if (gnl[i] == '\0')
		return (TRUE);
	while (gnl[i] == ' ')
		i++;
	if (gnl[i] == '+' || gnl[i] == '-')
	{
		if ((!(gnl[i + 1]) || gnl[i + 1] < 48 || gnl[i + 1] > 57))
			return (FALSE);
		i++;
	}
	while (gnl[i] && gnl[i] != ' ')
	{
		if (ft_isdigit(gnl[i]) != 1)
			return (FALSE);
		i++;
	}
	return (check_x_y(&gnl[i]));
}

int		is_it_a_room(char *gnl)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	if (!gnl || (gnl[0] >= 1 && gnl[0] <= 32))
		return (FALSE);
	while (gnl[i])
	{
		while (gnl[i] && gnl[i] != ' ')
			i++;
		while (gnl[i] && gnl[i] == ' ')
			i++;
		if (gnl[i])
			c++;
	}
	i = 0;
	while (gnl[i] && gnl[i] != ' ')
		i++;
	if (c == 2 && check_x_y(&gnl[i]) == TRUE)
		return (TRUE);
	return (FALSE);
}

int		is_it_a_tube(char *gnl)
{
	int		i;
	int		good;

	good = 0;
	i = 0;
	if (!gnl || (gnl[0] >= 1 && gnl[0] <= 32))
		return (0);
	while (gnl[i] && gnl[i] != ' ')
	{
		if (gnl[i] == '-' && i > 0 && gnl[i + 1] != '\0' && gnl[i + 1] != ' ')
			good = 713705;
		i++;
	}
	i--;
	while (gnl[++i])
		if (gnl[i] != ' ')
			return (0);
	return (good == 0 ? 0 : 1);
}

int		valid_line(char *gnl)
{
	if (is_it_a_room(gnl) == TRUE)
		return (1);
	if (is_it_a_tube(gnl) == TRUE)
		return (-1);
	return (0);
}

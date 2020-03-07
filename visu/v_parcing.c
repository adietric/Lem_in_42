/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_parcing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafonso <flafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 12:14:34 by flafonso          #+#    #+#             */
/*   Updated: 2019/11/14 14:58:23 by flafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visu.h"

int		parcing_room(char *gnl, t_info *inf_b)
{
	unsigned int	len;
	int				line_type;

	len = 0;
	if (gnl[0] == '#')
	{
		v_commande(inf_b, gnl);
		return (TRUE);
	}
	line_type = v_valid_line(gnl);
	if (line_type == 0)
		v_error(inf_b, "Error: invalid line\n");
	if (line_type == -1)
		return (FALSE);
	while (gnl[len] && gnl[len] != ' ')
		len++;
	v_new_room(inf_b, gnl, len);
	return (TRUE);
}

void	read_room_link(t_info *inf_b, char *gnl)
{
	int		room_or_tube;

	room_or_tube = 1;
	while (get_next_line(0, &gnl) == 1)
	{
		if (gnl[0] == '\0')
			break ;
		if (room_or_tube == 1 && parcing_room(gnl, inf_b) == FALSE)
			room_or_tube = 0;
		if (room_or_tube == 0)
			v_parcing_tube(gnl, inf_b);
		ft_strdel(&gnl);
	}
	ft_strdel(&gnl);
	if (inf_b->s_e_ok[0] != 1 || inf_b->s_e_ok[1] != 1)
		v_error(inf_b, "Error: start and/or end is unvailable\n");
}

int		v_read_file(t_info *inf_b)
{
	char	*gnl;

	while (get_next_line(0, &gnl) == 1)
	{
		if (gnl[0] == '#' && v_commande(inf_b, gnl) != 0)
			v_error(inf_b, "Error: invalid line\n");
		else if (gnl[0] != '#')
		{
			if (v_check_x_y(gnl) != 1)
				v_error(inf_b, "Error: invalid line\n");
			inf_b->nb_f = ft_atoi(gnl);
			ft_strdel(&gnl);
			break ;
		}
		ft_strdel(&gnl);
	}
	read_room_link(inf_b, gnl);
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafonso <flafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 12:14:34 by flafonso          #+#    #+#             */
/*   Updated: 2019/11/14 19:29:40 by flafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		parcing_room(char *gnl, t_info *inf_b)
{
	unsigned long long	i;
	unsigned long long	index_hach;
	int					line_type;

	i = 0;
	index_hach = 0;
	if (gnl[0] == '#')
	{
		commande(inf_b, gnl);
		return (TRUE);
	}
	line_type = valid_line(gnl);
	if (line_type == 0)
		error(inf_b, "ERROR\n", gnl);
	if (line_type == -1)
		return (FALSE);
	while (gnl[i] && gnl[i] != ' ')
		i++;
	index_hach = hachage(gnl, i);
	create_room(inf_b, gnl, index_hach, i);
	inf_b->nb_r++;
	return (TRUE);
}

void	read_room_link(t_info *inf_b, char *gnl)
{
	int		room_or_tube;

	room_or_tube = 1;
	while (get_next_line(0, &gnl) == 1)
	{
		if (room_or_tube == 1 && parcing_room(gnl, inf_b) == FALSE)
			room_or_tube = 0;
		if (room_or_tube == 0)
			if (parcing_tube(gnl, inf_b) != 1)
				break ;
		cpy_gnl(inf_b, gnl);
		ft_strdel(&gnl);
	}
	if (inf_b->room_start != 1 || inf_b->room_end != 1)
		error(inf_b, "ERROR\n", gnl);
	ft_strdel(&gnl);
}

void	new_buf(t_info *inf_b)
{
	char	*tmp;

	if (!(tmp = ft_strnew(inf_b->buf_map += 1024)))
		error(inf_b, "error malloc", NULL);
	tmp = ft_strcpy(tmp, inf_b->map);
	ft_strdel(&(inf_b->map));
	inf_b->map = tmp;
}

void	cpy_gnl(t_info *inf_b, char *gnl)
{
	size_t	len;

	len = ft_strlen(gnl);
	if (inf_b->index_buf != 0)
		len++;
	while (inf_b->index_buf + len >= inf_b->buf_map)
		new_buf(inf_b);
	if (inf_b->index_buf != 0)
		ft_strcpy(&(inf_b->map[inf_b->index_buf + 1]), gnl);
	else
		ft_strcpy(&(inf_b->map[inf_b->index_buf]), gnl);
	inf_b->index_buf += len;
	inf_b->map[inf_b->index_buf] = '\n';
}

int		read_file(t_info *inf_b)
{
	char	*gnl;

	gnl = NULL;
	while (get_next_line(0, &gnl) == 1)
	{
		if (gnl[0] == '#' && commande(inf_b, gnl) != 0)
			error(inf_b, "ERROR\n", gnl);
		else if (gnl[0] != '#')
		{
			if (check_x_y(gnl) != 1)
				error(inf_b, "ERROR\n", gnl);
			inf_b->nb_f = ft_atoi(gnl);
			if (inf_b->nb_f <= 0)
				error(inf_b, "ERROR\n", gnl);
			cpy_gnl(inf_b, gnl);
			ft_strdel(&gnl);
			break ;
		}
		cpy_gnl(inf_b, gnl);
		ft_strdel(&gnl);
	}
	read_room_link(inf_b, gnl);
	ft_strdel(&gnl);
	return (TRUE);
}

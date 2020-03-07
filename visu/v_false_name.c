/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_false_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafonso <flafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 15:35:24 by adietric          #+#    #+#             */
/*   Updated: 2019/11/14 16:52:06 by flafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visu.h"

int					boucle_name(char *gnl, t_info *inf_b,
					unsigned long long len)
{
	int		i;

	i = 0;
	while (inf_b->room[i] != NULL && i < MAX_R)
	{
		if (ft_strncmp(gnl, inf_b->room[i]->name, (int)len) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

unsigned long long	len_for_tube(char *gnl, int i,
					unsigned long long len, int lennn)
{
	if (i == 1)
	{
		if (len == 0 && gnl[0] == '-')
		{
			len++;
			if (lennn == len)
				len++;
		}
		while ((gnl[len] && gnl[len] != '-') || len < lennn)
		{
			len++;
			if (lennn == len)
				len++;
		}
	}
	else if (i == 2)
	{
		len = 0;
		while (gnl[len])
			len++;
	}
	return (len);
}

int					v_false_name_tube(char *gnl, t_info *inf_b,
					int i, int lennn)
{
	unsigned long long	len;
	int					len_tot;

	len_tot = ft_strlen(gnl);
	len = 0;
	while (len + lennn + 1 < len_tot)
	{
		len = len_for_tube(gnl, i, len, lennn);
		if (boucle_name(gnl, inf_b, len) == TRUE && boucle_name(&gnl[len + 1]
		, inf_b, len_tot - len - 1) == TRUE)
		{
			inf_b->len[0] = len;
			inf_b->len[1] = len_tot - len - 1;
			return (TRUE);
		}
		lennn = len;
		len = 0;
	}
	return (FALSE);
}

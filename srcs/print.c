/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adietric <adietric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:35:44 by adietric          #+#    #+#             */
/*   Updated: 2019/10/05 15:01:07 by adietric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	print_lem(t_room *room, t_info *inf_b)
{
	if (inf_b->grrr != 0)
		ft_putchar(' ');
	inf_b->grrr++;
	ft_putchar('L');
	ft_putnbr(room->l_here);
	ft_putchar('-');
	ft_putstr(room->name);
}

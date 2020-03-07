/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hachage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafonso <flafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 14:10:49 by adietric          #+#    #+#             */
/*   Updated: 2019/11/14 19:24:52 by flafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

unsigned long long		hachage(char *name, unsigned long long l)
{
	unsigned long long	i;
	unsigned long long	tot;

	i = -1;
	tot = 0;
	if (!name)
		return (0);
	while (++i < l)
		tot += name[i] * ft_puissance(256, l - i - 1);
	tot = tot % BUF_HACH;
	return (tot);
}

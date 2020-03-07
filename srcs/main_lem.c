/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafonso <flafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 10:56:12 by adietric          #+#    #+#             */
/*   Updated: 2019/11/14 17:47:42 by flafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	print_usage(void)
{
	ft_putstr("lem-in usage: lem-in [-p] < [file]\n");
	exit(EXIT_SUCCESS);
}

void	maj_rep_f(t_info *inf_b, t_stock *stock, int tot_rep_f)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (++i < stock->p_index)
		if (stock->path[i]->ban != 1)
			tot_rep_f += (int)stock->path[i]->next->rep_f;
	while (tot_rep_f < inf_b->nb_f)
	{
		i = -1;
		while (++i < stock->p_index)
		{
			if (stock->path[i]->ban != 1 &&
			((stock->path[i]->t_ch + stock->path[i]->next->maj) <
			(stock->path[j]->t_ch + stock->path[j]->next->maj)))
				j = i;
		}
		stock->path[j]->next->maj++;
		tot_rep_f++;
	}
	i = -1;
	while (++i < stock->p_index)
		stock->path[i]->next->rep_f += (double)stock->path[i]->next->maj;
}

int		main(int ac, char **av)
{
	t_info	inf_b;
	int		det;

	if (ac > 2 || (ac == 2 && ft_strcmp(av[1], "-p") != 0))
		print_usage();
	det = 0;
	init(&inf_b);
	if (read_file(&inf_b) != 1)
		error(&inf_b, "ERROR\n", NULL);
	bfs_start(&inf_b);
	if (inf_b.stock[0].path == NULL && inf_b.stock[1].path == NULL)
		error(&inf_b, "ERROR\n", NULL);
	ft_putstr(inf_b.map);
	new_lem_run(&inf_b);
	if (ac == 2 && ft_strcmp(av[1], "-p") == 0)
	{
		print_path(&inf_b);
		ft_putchar('\n');
	}
	free_all(&inf_b);
	return (0);
}

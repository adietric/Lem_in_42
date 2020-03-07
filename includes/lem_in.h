/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafonso <flafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 11:05:07 by adietric          #+#    #+#             */
/*   Updated: 2019/11/14 16:11:52 by flafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "get_next_line.h"

# define BUF_HACH 4999
# define TRUE 1
# define FALSE -1

typedef struct			s_stock
{
	struct s_path		**path;
	int					step;
	int					tot_t_ch;
	int					p_index;
	int					nb_ch;
}						t_stock;

typedef struct			s_path
{
	double				rep_f;
	int					maj;
	int					t_ch;
	int					ban;
	struct s_path		*next;
	struct s_room		*room;
}						t_path;

typedef struct			s_room
{
	char				*name;
	int					l_here;
	int					in_queue;
	int					nb_link;
	int					status;
	int					x_y[2];
	float				rep_f;
	int					taille_chemin;
	int					t_ch_real;
	int					mass;
	int					modif;
	int					skip;
	struct s_room		*next;
	struct s_link		*link;
	struct s_room		*preview;
}						t_room;

typedef struct			s_link
{
	int					flux;
	struct s_room		*room_link;
	struct s_link		*next;
}						t_link;

typedef struct			s_info
{
	t_room				*the_start;
	t_room				*the_end;
	struct s_stock		stock[2];
	int					l_name;
	int					nb_on_end;
	int					tot_t_ch;
	int					nb_f;
	int					nb_r;
	int					nb_chemin;
	int					det_qvalue;
	int					wrong;
	int					first;
	int					grrr;
	int					room_status;
	int					room_start;
	int					room_end;
	int					len[2];
	char				*map;
	int					buf_map;
	int					index_buf;
	struct s_room		*hach_table[BUF_HACH];
}						t_info;

void					cpy_gnl(t_info *inf_b, char *gnl);
int						read_file(t_info *inf_b);
void					read_room_link(t_info *inf_b, char *gnl);
int						parcing_room(char *gnl, t_info *inf_b);
void					create_room(t_info *inf_b, char *gnl
						, int index_hach, int i);
void					init(t_info *inf);
int						valid_line(char *gnl);
t_room					*new_room(t_info *inf_b, char *gnl, int length);
unsigned long long		hachage(char	*name, unsigned long long l);
int						commande(t_info *inf_b, char *gnl);
int						check_x_y(char *gnl);
int						parcing_tube(char *gnl, t_info *inf_b);
int						false_name_tube(char *gnl, t_info *inf_b, int i
						, int lennn);
void					print_all(t_info *inf_b);
void					bfs_start(t_info *inf_b);
void					lem_run(t_info *inf_b);
void					print_lem(t_room *room, t_info *inf_b);
void					free_all(t_info *inf_b);
void					print_path(t_info *inf_b);
void					error(t_info *inf_b, char *str, char *gnl);
float					do_it(t_info *inf_b, float tot_rep_f, t_link *link);
void					test_link(t_room *room, t_link *link);
int						is_free(t_room *room);
void					maj_mass(t_info *inf_b, t_room *room, t_link *link);
int						need_it(t_info *inf_b, t_room *room, t_link *link);
void					rev_flux(t_room *room, t_room *room_prev, int flux);
void					stock_path(t_info *inf_b);
void					sum_rep_f(t_info *inf_b, t_stock *stock);
int						sum_step(t_stock *stock);
int						sum_flux(t_info *inf_b);
void					choose(t_info *inf_b);
void					maj_rep_f(t_info *inf_b, t_stock *stock, int tot_rep_f);
void					new_lem_run(t_info *inf_b);
void					free_path(t_path *path);
void					reset_queue(t_info *inf_b, t_room **queue);

#endif

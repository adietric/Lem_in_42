/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafonso <flafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 16:25:16 by adietric          #+#    #+#             */
/*   Updated: 2019/11/11 16:54:31 by flafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H
# define MAX_R 30

# include "get_next_line.h"
# include "../SDL2/SDL.h"
# include "../SDL2/SDL_ttf.h"

# define TRUE 1
# define FALSE -1

typedef struct	s_my_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	SDL_Rect		rect;
	TTF_Font		*font;
	int				delay;
	int				w_l;
	int				w_h;
}				t_my_sdl;

typedef struct	s_link
{
	struct s_room	*room_l;
	struct s_link	*next;
}				t_link;

typedef struct	s_room
{
	char			*name;
	int				x;
	int				y;
	int				just_one;
	int				status;
	struct s_link	*link;
}				t_room;

typedef struct	s_ant
{
	int				name;
	float			vec[2];
	float			x;
	float			y;
	int				need_move;
	double			angle;
	struct s_room	*room;
}				t_ant;

typedef struct	s_info
{
	int				nb_f;
	int				r_index;
	int				status;
	int				s_e_ok[2];
	int				len[2];
	int				tab_xy[6];
	struct s_room	*room[MAX_R];
	struct s_ant	*ant;
	struct s_my_sdl	sdl;
}				t_info;

void			sum_angle(t_info *inf_b, int lem);
int				sum_vec(t_info *inf_b, t_my_sdl *sdl, char *gnl, int i);
void			set_rect_first(t_info *inf_b, t_room *room);
void			init(t_info *inf_b);
void			init_visu(t_info *inf_b, t_my_sdl *sdl);
void			print_visu(t_info *inf_b, t_my_sdl *sdl);
void			endsdl(t_my_sdl *sdl, t_info *inf_b);
int				sdl_wait_end(void);
int				sdl_event(t_my_sdl *sdl, t_info *inf_b);
int				v_read_file(t_info *inf_b);
void			create_ant(t_info *inf_b);
void			v_new_room(t_info *inf_b, char *str, unsigned int len);
void			v_error(t_info *inf_b, char *str);
void			v_print_all(t_info *inf_b);
int				v_commande(t_info *inf_b, char *gnl);
int				v_check_x_y(char *gnl);
int				v_valid_line(char *gnl);
void			v_parcing_tube(char *gnl, t_info *inf_b);
int				v_false_name_tube(char *gnl, t_info *inf_b,
				int i, int lennn);
void			load_image(t_info *inf_b, char *str);
void			lem_move(t_info *inf_b, t_my_sdl *sdl);
int				ft_nbrlen(int n_cpy);
char			*ft_itoa(int n);
void			suc_or_fail(t_info *inf_b, t_my_sdl *sdl);
void			sdl_failure(t_info *inf_b, t_my_sdl *sdl);
void			print_text(t_info *inf_b, t_my_sdl *sdl);
SDL_Color		give_rgba(int r, int g, int b, int a);
SDL_Rect		give_rect(int h, int w, int x, int y);
void			print_end(t_my_sdl *sdl, SDL_Color color_bg,
				SDL_Rect text_rect, char *str);

#endif

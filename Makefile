# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flafonso <flafonso@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/14 09:43:08 by adietric          #+#    #+#              #
#    Updated: 2019/11/15 13:09:45 by flafonso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

NAME_TWO = visual

# Effects
END = \033[0m
BOLD = \033[1m
UNDER = \033[4m
REV = \033[7m

# Text Colors
GREY = \033[38;5;246m
RED = \033[38;5;160m
GREEN = \033[38;5;118m
YELLOW = \033[38;5;226m
BLUE = \033[38;5;12m
PURPLE = \033[38;5;129m
CYAN = \033[38;5;45m
WHITE = \033[38;5;231m
BLACK = \033[38;5;0m

# Backgrounds Colors
IGREY = \033[48;5;246m
IRED = \033[48;5;160m
IGREEN = \033[48;5;118m
IYELLOW = \033[48;5;226m
IBLUE = \033[48;5;12m
IPURPLE = \033[48;5;129m
ICYAN = \033[48;5;45m
IWHITE = \033[48;5;231m
IBLACK = \033[48;5;0m

INCL_PATH = ./includes
LIB_PATH = ./libsrcs
SRCS_PATH = ./srcs
VISU_PATH = ./visu
OBJVISU_PATH = ./obj
OBJLIB_PATH = ./obj
OBJ_PATH = ./obj

INCL_NAME = lem_in.h		\
			get_next_line.h	\
			libsrcs.h		\
			visu.h

VISU_NAME = main_visu.c		\
			visu.c			\
			v_parcing.c		\
			v_false_name.c	\
			v_valid_line.c	\
			v_create_link.c	\
			v_error.c		\
			v_init.c		\
			event.c			\
			lem_move.c		\
			v_sum.c			\
			print_text.c

LIB_NAME = 	ft_atoi.c		\
			ft_isdigit.c	\
			ft_puissance.c	\
			ft_strsub.c		\
			ft_strlen.c		\
			ft_isspace.c	\
			ft_memalloc.c	\
			ft_bzero.c		\
			ft_strncpy.c	\
			get_next_line.c	\
			ft_strchr.c		\
			ft_strdel.c		\
			ft_strdup.c		\
			ft_strjoin.c	\
			ft_strnew.c		\
			ft_strcat.c		\
			ft_strcpy.c		\
			ft_strcmp.c		\
			ft_putchar.c	\
			ft_putstr.c		\
			ft_putnbr.c		\
			ft_reverse.c	\
			ft_itoa.c

SRCS_NAME = hachage.c		\
			init.c			\
			main_lem.c		\
			room.c			\
			false_name.c	\
			valid_line.c	\
			print.c			\
			bfs.c			\
			print_path.c	\
			create_link.c	\
			error.c			\
			do_it.c			\
			parcing.c		\
			stock.c			\
			free_p.c		\
			new_lem_run.c	\
			for_bfs.c		\
			sum.c

OBJLIB_NAME = $(LIB_NAME:.c=.o)
OBJ_NAME = $(SRCS_NAME:.c=.o)
OBJVISU_NAME = $(VISU_NAME:.c=.o)

INCL = $(addprefix $(INCL_PATH)/, $(INCL_NAME))
LIB = $(addprefix $(LIB_PATH)/, $(LIB_NAME))
SRCS = $(addprefix $(SRCS_PATH)/, $(SRCS_NAME))
OBJLIB = $(addprefix $(OBJLIB_PATH)/, $(OBJLIB_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))
OBJVISU = $(addprefix $(OBJVISU_PATH)/, $(OBJVISU_NAME))

CC = gcc

FLAG = -Wall -Werror -Wextra

.PHONY: all clean fclean re test

all: $(NAME)

$(NAME): $(OBJ) $(OBJLIB) $(INCL)
	@$(CC) $(FLAG) $(OBJ) $(OBJLIB) -o $(NAME)
	@echo "$(BOLD)$(GREEN)[$(NAME) done]$(END)"
	@sleep 0.75

$(NAME_TWO): $(OBJVISU) $(OBJLIB) $(INCL) 
	@$(CC) $(FLAG) $(OBJVISU) $(OBJLIB) -L lib/lib -lSDL2 -L lib/ttf_lib/lib -lSDL2_ttf -o $(NAME_TWO)
	@echo "$(BOLD)$(GREEN)[$(NAME_TWO) done]$(END)"
	@sleep 0.75

$(OBJLIB_PATH)/%.o: $(LIB_PATH)/%.c
	@echo "$(BOLD)$(GREY)[...]$(END)"
	@mkdir $(OBJLIB_PATH) 2> /dev/null || true
	@$(CC) -o $@ -c $<

$(OBJ_PATH)/%.o: $(SRCS_PATH)/%.c
	@echo "$(BOLD)$(GREY)[...]$(END)"
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) -o $@ -c $<

$(OBJVISU_PATH)/%.o: $(VISU_PATH)/%.c
	@echo "$(BOLD)$(GREY)[...]$(END)"
	@mkdir $(OBJVISU_PATH) 2> /dev/null || true
	@$(CC) -o $@ -c $<

git:
	@git add -A
	@git status
	@echo "$(UNDER)$(YELLOW)Un commentaire pour ton git:$(END)\n"
	@read -p "=> " COMMIT;\
	git commit -m "$$COMMIT"
	@git push

color:
	@echo "$(END)$(BOLD)$(UNDER)Text Colors :$(END)\n\n$(GREY)Gris\n$(RED)Rouge\n$(GREEN)Vert\n$(YELLOW)Jaune\n$(BLUE)Bleu\n$(PURPLE)Violet\n$(CYAN)Cyan\n$(WHITE)Blanc\n$(BLACK)Noir"
	@echo "\n"
	@echo "$(END)$(BOLD)$(UNDER)Backgrounds Colors :$(END)\n\n$(IGREY)Gris\n$(IRED)Rouge\n$(IGREEN)Vert\n$(IYELLOW)Jaune\n$(IBLUE)Bleu\n$(IPURPLE)Violet\n$(ICYAN)Cyan\n$(IWHITE)Blanc\n$(IBLACK)Noir"
	@echo "\n"
	@echo "$(END)$(BOLD)$(UNDER)Effects :$(END)\n\nNormal\n$(END)$(BOLD)Gras\n$(END)$(UNDER)Souligner\n$(END)$(REV)Inverse$(END)"

clean:
	@rm -rf $(OBJ) $(OBJLIB) $(OBJVISU)
	@rm -rf $(OBJ_PATH)
	@rm -rf $(OBJLIB_PATH)
	@rm -rf $(OBJVISU_PATH)
	@echo "$(BOLD)$(GREEN)[clean]$(END)"

fclean: clean
	@rm -f $(NAME) $(NAME_TWO)
	@echo "$(BOLD)$(GREEN)[fclean]$(END)"

re: fclean all

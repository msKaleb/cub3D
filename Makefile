# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/22 09:00:15 by msoria-j          #+#    #+#              #
#    Updated: 2024/01/16 13:10:12 by msoria-j         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

define HEADER

 ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ 
██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗
██║     ██║   ██║██████╔╝ █████╔╝██║  ██║
██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║
╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝
 ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ 

endef
export HEADER

# $@ = Name of the target (each file .o)
# $< = First prerequisite name - in this case, in $(SRC)

OS		=	$(shell uname -s)

NAME	=	cub3D

# Common sources
SRC_C	=	errors.c \
			mlx_utils.c \
			flood_fill.c \
			free_memory.c \
			raycast.c \
			player.c \
			parser_utils.c \
			parser_check_map.c \
			parser_get_rgb.c \
			utils.c \
			textures.c \
			render.c \

# Mandatory sources
SRC_M	=	main.c \
			parser.c \

SRC_B	=	main_bonus.c \
			parser_bonus.c \
			render_bonus.c \
			minimap_bonus.c \
			minimap_utils_bonus.c \
			ft_bonus.c \
			player_bonus.c \
			mlx_utils_bonus.c \

OBJ_C	=	$(SRC_C:.c=.o)

OBJ_M	=	$(SRC_M:.c=.o)

OBJ_B	=	$(SRC_B:.c=.o)

CC		=	gcc

LIBFT	=	libft/libft.a

WWW		=	-Wall -Wextra -Werror

# Define flags according to OS
ifeq ($(OS), Linux)
# Linux
	ECHO = echo -e
	CCOBJ = $(WWW) -I/usr/include -I./minilibx_linux -O3 -c $< -o $@
	FLAGS = -L/usr/lib -lXext -lX11 -lm -lz
	MLXDIR = minilibx_linux/
	MLX = $(MLXDIR)libmlx_Linux.a
else ifeq ($(OS), Darwin)
# Mac (-lm compiler option)
# Add -g -O0 in CCOBJ for debugging
	ECHO = echo
	CCOBJ = $(WWW) -Imlx -c $< -o $@
	FLAGS = -Lminilibx_opengl -lmlx -framework OpenGL -framework AppKit
	MLXDIR = minilibx_opengl/
	MLX = $(MLXDIR)libmlx.a
endif

#Define colors for output
COLOR='\033['
NONE=$(COLOR)0m
GREEN=$(COLOR)32m
GRAY=$(COLOR)37m
RED=$(COLOR)31m
CYAN=$(COLOR)36m
MAGENTA=$(COLOR)35m
BLUE=$(COLOR)34m
ITALIC=$(COLOR)3m
BOLD=$(COLOR)1m
BRIGHT_WHITE=$(COLOR)97m

ifndef VERBOSE
	MAKEFLAGS += --silent
endif

all:		$(NAME)

%.o: %.c
	 		$(CC) $(CCOBJ) -g -O0

$(NAME):	$(OBJ_C) $(OBJ_M)

			make bonus -sC libft/
			$(ECHO) $(CYAN) "$$HEADER" $(NONE)
			$(ECHO) $(GREEN)$(ITALIC) "	Compiling $(NAME)..."$(NONE)
			make -sC $(MLXDIR)
			
			$(CC) $(WWW) $(OBJ_M) $(OBJ_C) $(LIBFT) $(MLX) $(FLAGS) -o $(NAME)
			$(ECHO) $(BRIGHT_WHITE)$(BOLD)"\t$(NAME) ready!"$(NONE)
			@rm -rf .bonus

bonus:		.bonus

.bonus:		$(OBJ_C) $(OBJ_B)

			make bonus -sC libft/
			$(ECHO) $(BLUE) "$$HEADER" $(NONE)
			$(ECHO) $(MAGENTA)$(ITALIC) "	Compiling $(NAME) (Bonus)..."$(NONE)
			make -sC $(MLXDIR)

			$(CC) $(WWW) $(OBJ_C) $(OBJ_B) $(LIBFT) $(MLX) $(FLAGS) -o $(NAME)
			$(ECHO) $(BRIGHT_WHITE)$(BOLD)"\t$(NAME) (bonus) ready!"$(NONE)
			@touch .bonus
			@rm -rf $(OBJ_M)

clean:
			$(RM) $(OBJ_C) $(OBJ_B) $(OBJ_M)
			make clean -sC libft/
			make clean -sC $(MLXDIR)
			
fclean:		clean
			$(RM) $(NAME)
			make fclean -sC libft/

re:			fclean $(NAME)

rebonus:	fclean bonus

.PHONY:		all clean fclean re bonus

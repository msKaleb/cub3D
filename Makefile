# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nimai <nimai@student.42urduliz.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/22 09:00:15 by msoria-j          #+#    #+#              #
#    Updated: 2023/12/28 18:54:56 by nimai            ###   ########.fr        #
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

MAIN	=	main.c \

SRC		=	errors.c \
			mlx_utils.c \
			parser.c \
			flood_fill.c 
			
MAIN_B	=	main_bonus.c

SRC_B	=

OBJ		=	$(SRC:.c=.o)

OBJ_M	=	$(MAIN:.c=.o)

OBJ_B	=	$(SRC_B:.c=.o)

OBJ_MB	=	$(MAIN_B:.c=.o)

CC		=	gcc

LIBFT	=	libft/libft.a

# Define flags according to OS
ifeq ($(OS), Linux)
# Linux
	ECHO = echo -e
	CCOBJ = -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@
	FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
	MLXDIR = minilibx_linux/
	MLX = $(MLXDIR)libmlx_Linux.a
else ifeq ($(OS), Darwin)
# Mac (-lm compiler option)
# Add -g -O0 in CCOBJ for debugging
	ECHO = echo
	CCOBJ = -Wall -Wextra -Werror -Imlx -c $< -o $@
	FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
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

pre-build:
			make bonus -sC LibFT/
			$(ECHO) $(CYAN) "$$HEADER" $(NONE)
			$(ECHO) $(GREEN)$(ITALIC) "	Compiling $(NAME)..."$(NONE)
			make -sC $(MLXDIR)

pre-build-bonus:
			make bonus -sC LibFT/
			$(ECHO) $(BLUE) "$$HEADER" $(NONE)
			$(ECHO) $(MAGENTA)$(ITALIC) "	Compiling $(NAME) (Bonus)..."$(NONE)
			make -sC $(MLXDIR)
				
%.o: %.c
	 		$(CC) $(CCOBJ)

$(NAME):	pre-build $(OBJ) $(OBJ_M)
			$(CC) $(FLAGS) $(OBJ_M) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)
			$(ECHO) $(BRIGHT_WHITE)$(BOLD)"\tDone!"$(NONE)

bonus:		pre-build-bonus $(OBJ) $(OBJ_B) $(OBJ_MB)
			$(CC) $(FLAGS) $(OBJ_MB) $(OBJ) $(OBJ_B) $(LIBFT) $(MLX) -o $(NAME)
			$(ECHO) $(BRIGHT_WHITE)$(BOLD)"\tDone!"$(NONE)
			
clean:
			$(RM) $(OBJ) $(OBJ_B) $(OBJ_M) $(OBJ_MB)
			make clean -sC libft/
			make clean -sC $(MLXDIR)
			
fclean:		clean
			$(RM) $(NAME)
			make fclean -sC libft/

re:			fclean $(NAME)

.PHONY:		all clean fclean re bonus pre-build pre-build-bonus
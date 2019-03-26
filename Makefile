# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/11/13 00:29:26 by pduhard-     #+#   ##    ##    #+#        #
#    Updated: 2019/03/26 15:00:31 by pduhard-    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

#__________CONFIG__________#

NAME		=	fdf

CC			=	gcc
FLAGS		=	-g -Wall -Werror -Wextra -O3
FRAMEWORK	=	-framework OpenGL -framework AppKit
LIB_FLAGS	=	-L$(LIB_PATH) $(LIB_FLAG)
MLX_FLAGS	=	-L$(MLX_PATH) $(MLX_FLAG)
INCLUDES	=	-I includes/fdf.h

SRC_PATH	=	./srcs/
BIN_PATH	=	./bins/
LIB_PATH	=	./libft/
MLX_PATH	=	./minilibx_macos/

SRC			=	main.c			\
				parse.c			\
				init.c			\
				map.c			\
				projection.c	\
				line.c			\
				loop.c			\
				commands.c		\
				point_op.c		\
				matrix_op.c		\
				free.c			\
				display.c		\
				display_utils.c	\
				ray_trace.c		\
				matrix.c		\
				key_hook.c		\

BIN			=	$(SRC:.c=.o)

LIB_FLAG			=	-lft
LIB					=	libft.a
MLX_FLAG			=	-lmlx
MLX					=	libmlx.a

SRCS		=	$(addprefix $(SRC_PATH), $(SRC))
BINS		=	$(addprefix $(BIN_PATH), $(BIN))
LIBS		=	$(addprefix $(LIB_PATH), $(LIB))
MLXS		=	$(addprefix $(MLX_PATH), $(MLX))

.PHONY: all clean fclean re lib

#__________COLORS__________#

R			=	\033[0;31m
G			=	\033[32;7m
B			=	\033[0;34m
N			=	\33[0m

#__________RULES__________#

all: $(NAME)

	@make -C $(LIB_PATH)

$(NAME): $(LIBS) $(MLXS) $(BINS)

	@$(CC) -g $(INCLUDES) $(FLAGS) $(LIB_FLAGS) $(MLX_FLAGS) $(FRAMEWORK) $^ -o $@
	@echo "\n\n$(B)[EXECUTABLE \"$(NAME)\" READY]\n"

$(LIBS):

	@make -C $(LIB_PATH)

$(MLXS):

	@make -C $(MLX_PATH)

$(BIN_PATH)%.o: $(SRC_PATH)%.c includes/fdf.h

	@mkdir -p $(BIN_PATH) || true
	@$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $< && echo "${G} \c"

clean:

	@make clean -C $(LIB_PATH)
	@make clean -C $(MLX_PATH)
	@echo "${R}[CLEANING $(NAME) BINARIES]"
	@rm -f $(BINS)

fclean: clean

	@echo "\n${R}[REMOVING "libft.a"]"
	@rm -rf $(LIB_PATH)/libft.a
	@echo "\n${R}[REMOVING "libmlx.a"]"
	@rm -rf $(MLX_PATH)/libmlx.a
	@echo "\n${R}[REMOVING \"$(NAME)\"]\n"
	@rm -f $(NAME)

re: fclean all


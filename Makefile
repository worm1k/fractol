#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ochayche <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/05 19:07:36 by ochayche          #+#    #+#              #
#    Updated: 2017/06/30 19:42:48 by vdoroshy         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC       = gcc
#CFLAGS   = -Wall -Wextra -Werror
LIB_DIR  = ext/libft
LIB      = libft.a
MLX_DIR  = ./ext/minilibx_macos
MLX      = libmlx.a
NAME     = fractol
INC      = fractol.h

#********* -OBJ
OBJ_DIR  = .obj
OBJ      = $(subst .c,.o,$(subst $(SRC_DIR)/,$(OBJ_DIR)/,$(SRC)))

#********* -SRC
SRC_DIR  = src
SRC      = $(addprefix $(SRC_DIR)/, $(SRC_NAME))

SRC_NAME =			main.c \
					window.c \

# add .c file ---->


################################################################################
#	RULES
################################################################################

.PHONY: all clean fclean re

all: $(LIB) $(MLX) $(NAME)

$(NAME): $(OBJ) $(INC)
		$(CC) $(CFLAGS) $(OBJ) $(LIB_DIR)/$(LIB) $(MLX_DIR)/$(MLX) -lm -framework OpenGL -framework AppKit -o $(NAME)
		@echo "\033[33m'$(NAME)' compiling done.\033[0m"

$(LIB):
		@make -C $(LIB_DIR)

$(MLX):
		@make -C $(MLX_DIR)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
		$(CC) -I./ext/minilibx_macos -I./ -I./ext/libft/inc -I./ext/minilibx_macos -c $(CFLAGS) $? -o $@

$(OBJ_DIR):
		mkdir $(OBJ_DIR)

clean:
		rm -rf $(OBJ_DIR)
		make -C $(LIB_DIR)/ clean
		make -C $(MLX_DIR)/ clean

fclean: clean
		rm -f $(NAME)
		rm -f $(LIB_DIR)/$(LIB)
		rm -f $(MLX_DIR)/$(MLX)

re: fclean all

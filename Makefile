# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rfork <rfork@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/05 17:09:20 by rfork             #+#    #+#              #
#    Updated: 2020/01/13 20:23:37 by dovran           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GCC = gcc -Wall -Wextra -Werror
NAME = wolf3d
SRC = init.c hooks.c main.c vect2d.c render.c render2.c map.c validation.c

OBJ_DIR = ./objects
SRC_DIR = ./src
HDR_DIR = ./includes
LIBFT_HDR_DIR = ./libft
MLX_HDR_DIR = ./mlx
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
HDR = ./includes/wolf3d.h ./includes/keys.h
LIB = libft/libft.a
MLX = mlx/lmlx.a

.PHONY: clean fclean re

all: libs $(NAME)
	./$(NAME) text.txt

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR)
	@GCC -g3  -I $(HDR_DIR) -I $(LIBFT_HDR_DIR) -I $(MLX_HDR_DIR) -o $@ -c $<

libs:
	@make -C $(LIBFT_HDR_DIR)
	@make -C $(MLX_HDR_DIR)

clean:
	@make clean -C $(LIBFT_HDR_DIR)
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C $(LIBFT_HDR_DIR)
	@make clean -C $(MLX_HDR_DIR)
	@rm -rf $(NAME)

re: fclean all

$(NAME): $(OBJ_DIR) $(OBJ)
	@GCC -g3 -o $(NAME) -I $(HDR_DIR) -I $(LIBFT_HDR_DIR) -I $(MLX_HDR_DIR) $(LIB) $(VAL) $(OBJ) -L mlx -lmlx -framework OpenGL -framework AppKit

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

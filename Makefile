SRC = init_mlx.c main.c

OBJ_DIR = ./objects
SRC_DIR = ./src
HDR_DIR = ./includes
LIBFT_HDR_DIR = ./libft
MLX_HDR_DIR = ./mlx
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
HDR = ./includes/wolf3d.h
LIB = libft/libft.a
MLX = mlx/lmlx.a
NAME = wolf3d

all: libs $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR)
	@gcc -g3  -I $(HDR_DIR) -I $(LIBFT_HDR_DIR) -I $(MLX_HDR_DIR) -o $@ -c $<

libs:
	@make -C ./libft

clean:
	@make clean -C ./libft
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_DIR)
fclean: clean
	@make fclean -C ./libft
	@rm -rf $(NAME)
re: fclean all

$(NAME): $(OBJ_DIR) $(OBJ)
	@gcc -Wall -Wextra -Werror -g3 -o $(NAME) -I $(HDR_DIR) -I $(LIBFT_HDR_DIR) -I $(MLX_HDR_DIR) $(LIB) $(VAL) $(OBJ) -L mlx -lmlx -framework OpenGL -framework AppKit

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
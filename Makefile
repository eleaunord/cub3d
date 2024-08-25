# VARIABLES
## binary
NAME = cub3D

## compilation
CC = gcc
CFLAGS = -g -Wall -Werror -Wextra
INCLUDES_DIR = ./minilibx-linux ./libft ./get_next_line .
INCLUDES = $(addprefix -I,$(INCLUDES_DIR))

## bash commands
RM = rm -f

## valgrind
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q --tool=memcheck

## directories
OBJ_DIR = ./obj

## libs
MLIBX_PATH = ./minilibx-linux
MLIBX = $(MLIBX_PATH)/libmlx.a
MLX_FLAGS = -L$(MLIBX_PATH) -lmlx -lXext -lX11

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

GNL_PATH = ./get_next_line
GNL_SRCS = $(GNL_PATH)/get_next_line.c

LIBMATH_FLAGS = -lm

## source files
SRCS = main.c \
	parsing/checkers.c \
	parsing/colors.c \
	error.c \
	parsing/parser.c \
	parsing/textures.c \
	parsing/utils.c \
	parsing/process_map.c \
	parsing/fill_map.c \
	parsing/check_walls.c \
	raycasting.c \
	move_player.c \
	init.c \
	textures.c \
	draw_game.c \
	$(GNL_SRCS) \

## object files
OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(MLIBX) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INCLUDES) $(MLX_FLAGS) $(LIBMATH_FLAGS) $(LIBFT)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)  # Create the directory for the object file
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MLIBX):
	make -C $(MLIBX_PATH)

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	make clean -C $(MLIBX_PATH)
	make clean -C $(LIBFT_PATH)
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_PATH)

re: fclean all

run: all
	clear
	./$(NAME) $$MAP

valgrind: $(NAME)
	$(VALGRIND) ./$(NAME) $$MAP

.PHONY: all clean fclean re run valgrind

CC = gcc

NAME = cub3d

HEADER_NAME = cub3d.h

LIBMLX_NAME = libmlx.a

LIB_DIR = my_libft

MY_LIB = libft.a

CFLAGS = -MMD -Wall -Wextra -Werror -g -fsanitize=address -fsanitize=leak

HEADER_DIR = inc/

LIB_FLAGS = -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

LIBMLX_DIR = minilibx-linux/

INCLUDES = -I $(HEADER_DIR) -I $(LIBMLX_DIR)

SRC_FILES = src/main.c \
	src/check_args.c \
	src/open_file.c \
	src/error.c \
	src/utils.c \
	src/free_utils.c \
	src/str_utils.c \
	src/test_utils.c
	
OBJ_FILES = $(SRC_FILES:.c=.o)

DEP_FILES = $(SRC_FILES:.c=.d)

all:
	$(MAKE) -C $(LIBMLX_DIR)
	$(MAKE) -C $(LIB_DIR)
	$(MAKE) $(NAME)

$(NAME): $(OBJ_FILES) my_libft/$(MY_LIB)
	$(CC) $(CFLAGS) $(OBJ_FILES) my_libft/$(MY_LIB) -o $@ $(LIB_FLAGS)


%.o: %.c Makefile mlx_linux/$(LIBMLX_NAME) my_libft/$(MY_LIB)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

-include $(DEP_FILES)

clean:
	rm -f $(OBJ_FILES) $(DEP_FILES)
	$(MAKE) -C $(LIBMLX_DIR) clean
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBMLX_DIR) clean
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

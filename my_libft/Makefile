LIB = ar -rcs

RM = rm -f

CC = gcc

CCFLAGS = -Wall -Wextra -Werror -MMD

NAME = libft.a

SRC =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isspace.c\
ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c\
ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c\
ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c\
ft_strrchr.c ft_tolower.c ft_toupper.c ft_substr.c ft_strjoin.c\
ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c\
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
ft_lstnew.c ft_lstadd_front.c ft_lstsize.c\
ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c\
ft_lstclear.c ft_lstiter.c ft_lstmap.c\

P_GNL = get_next_line/

P_PT = ft_printf/

SRC_GNL = $(P_GNL)get_next_line.c $(P_GNL)get_next_line_utils.c\

SRC_PT = $(P_PT)ft_printf.c $(P_PT)ft_putchar.c $(P_PT)ft_puthex.c $(P_PT)ft_putnbr.c $(P_PT)ft_putptr.c $(P_PT)ft_putstr.c $(P_PT)ft_putunsig.c\

OBJ = $(SRC:.c=.o) $(SRC_GNL:.c=.o) $(SRC_PT:.c=.o)

DEPS = $(SRC:.c=.d) $(SRC_GNL:.c=.d) $(SRC_PT:.c=.d)

INCLUDE = libft.h $(P_GNL)get_next_line.h $(P_PT)ft_printf.h

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	$(LIB) $(NAME) $(OBJ)

%.o: %.c Makefile
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(DEPS)

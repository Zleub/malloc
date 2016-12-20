ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
EXT = a
NAME = libft_malloc_$(HOSTTYPE).$(EXT)

SRC = malloc.c
OBJ = $(subst .c,.o,$(SRC))

CC = clang
CFLAGS = -Wall -Werror -Wextra -I libft/inc

all: dep $(NAME)
	$(CC) -lft -Llibft -lft_malloc -L. -o test main.o

$(NAME): $(OBJ)
	ar rc $@ $^
	ranlib $@
	rm -rf libft_malloc.$(EXT)
	ln -s $@ libft_malloc.$(EXT)

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean:
	rm -f $(OBJ)
	rm -f $(NAME)
	make -C libft fclean

re:
	make fclean
	make all

dep:
	make -C libft

.PHONY: dep all $(NAME) clean fclean re

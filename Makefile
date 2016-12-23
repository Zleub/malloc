ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
EXT = a
NAME = libft_malloc_$(HOSTTYPE).$(EXT)

SRC = malloc.c utils.c
OBJ = $(subst .c,.o,$(SRC))

export CC = clang
export CFLAGS = -Wall -Werror -Wextra -Iinc

all: dep $(NAME) main.c
	$(CC) -g3 main.c -Iinc -L. -lft_malloc -Llibft -lft -o test
	$(CC) -g3 main.c -Iinc -Llibft -lft -o temoin

debug: dep $(NAME) main.c
	$(CC) -g3 -D DEBUG=$(DEBUG) main.c -Iinc -L. -lft_malloc -Llibft -lft -o test
	$(CC) -g3 main.c -Iinc -Llibft -lft -o temoin

tests:
	make all
	fish test.fish

%.o:%.c inc/malloc.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	ar rc $@ $^ libft/libft.a
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

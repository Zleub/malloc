ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
EXT = a
NAME = libft_malloc_$(HOSTTYPE).$(EXT)

SRC = malloc.c utils.c
OBJ = $(subst .c,.o,$(SRC))

export CC = clang

ifeq ($(EXT), a)
export CFLAGS = -Wall -Werror -Wextra -Iinc
else
export CFLAGS = -Wall -Werror -Wextra -Iinc -fPIC
endif

all: dep $(NAME) main.c
ifeq ($(EXT), so)
	$(CC) -fPIC -Iinc -Llibft -lft -o test main.c
	$(CC) -fPIC -Iinc -Llibft -lft -o temoin main.c
else
	$(CC) -Iinc -Llibft -lft -L. -lft_malloc -o test main.c
	$(CC) -Iinc -Llibft -lft -o temoin main.c
endif

tests:
	make all
	fish test.fish

%.o:%.c inc/malloc.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
ifeq ($(EXT), so)
	$(CC) $(CFLAGS) -shared -o $@ $^ libft/libft.a
else
ifeq ($(EXT), dylib)
	$(CC) $(CFLAGS) -dynamiclib -o $@ $^ libft/libft.a
else
	ar rc $@ $^ libft/libft.a
	ranlib $@
endif
endif
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

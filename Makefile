ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
NAME = libft_malloc_$(HOSTTYPE).so

SRC = main.c
OBJ = $(subst .c,.o,$(SRC))

CC = clang
CFLAGS = -Wall -Werror -Wextra -I libft/inc

all: dep $(NAME)
	$(CC) -lft -Llibft -o test $(NAME)

$(NAME): $(OBJ)
	ar rc $@ $^
	ranlib $@

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

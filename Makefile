ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

ifeq ($(HOSTTYPE), x86_64_Darwin)
	STATIC_EXT = a
	DYNAMIC_EXT = dylib
endif
ifeq ($(HOSTTYPE), Linux)
	STATIC_EXT = a
	DYNAMIC_EXT = so
endif

NAME = ft_malloc
STATIC_NAME = libft_malloc_$(HOSTTYPE).$(STATIC_EXT)
DYNAMIC_NAME = libft_malloc_$(HOSTTYPE).$(DYNAMIC_EXT)

SRC =	src/malloc.c
OBJ = $(subst .c,.o,$(SRC))

export CC = clang
export CFLAGS = -O0 -Wall -Werror -Wextra -Iinc

all: dep $(NAME)

tests: main.c
ifeq ($(HOSTTYPE), x86_64_Darwin)
	$(CC) $(CFLAGS) -fPIC -Llibft -lft -o dyn_test main.c

	$(CC) $(CFLAGS) -Llibft -lft -o stt_test main.c libft_malloc.a
	$(CC) $(CFLAGS) -Llibft -lft -o stt_temoin main.c
endif

%.o:%.c inc/malloc.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
ifeq ($(HOSTTYPE), x86_64_Darwin)
	$(CC) -dynamiclib -o $(DYNAMIC_NAME) $^ libft/libft.a
	ar rc $(STATIC_NAME) $^ libft/libft.a
	ranlib $(STATIC_NAME)
endif
# ifeq ($(EXT), so)
# 	$(CC) $(CFLAGS) -shared -o $@ $^ libft/libft.a
# else
# ifeq ($(EXT), dylib)
# 	$(CC) $(CFLAGS) -dynamiclib -o $@ $^ libft/libft.a
# else
# 	ar rc $@ $^ libft/libft.a
# 	ranlib $@
# endif
# endif
	rm -rf libft_malloc.$(STATIC_EXT)
	ln -s $(STATIC_NAME) libft_malloc.$(STATIC_EXT)
	rm -rf libft_malloc.$(DYNAMIC_EXT)
	ln -s $(DYNAMIC_NAME) libft_malloc.$(DYNAMIC_EXT)

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean:
	rm -f $(OBJ)
	rm -rf libft_malloc.$(DYNAMIC_EXT)
	rm -f $(DYNAMIC_NAME)
	rm -rf libft_malloc.$(STATIC_EXT)
	rm -f $(STATIC_NAME)
	make -C libft fclean

re:
	make fclean
	make all

dep:
	make -C libft

.PHONY: dep all $(NAME) clean fclean re

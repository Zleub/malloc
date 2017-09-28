# @Author: Debray Arnaud <adebray>
# @Date:   2017-08-12T09:29:05+02:00
# @Email:  adebray@student.42.fr
# @Last modified by:   adebray
# @Last modified time: 2017-08-12T10:13:29+02:00

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

ifeq ($(HOSTTYPE), x86_64_Darwin)
	STATIC_EXT = a
	DYNAMIC_EXT = dylib
endif
ifeq ($(HOSTTYPE), x86_64_Linux)
	STATIC_EXT = a
	DYNAMIC_EXT = so
endif

NAME = ft_malloc
STATIC_NAME = libft_malloc_$(HOSTTYPE).$(STATIC_EXT)
DYNAMIC_NAME = libft_malloc_$(HOSTTYPE).$(DYNAMIC_EXT)

SRC = src/malloc.c src/utils.c
OBJ = $(subst .c,.o,$(SRC))

export CC = clang
export CFLAGS = -O3 -Wall -Werror -Wextra -Iinc

all: dep $(NAME) tests

tests: main.c
ifeq ($(HOSTTYPE), x86_64_Darwin)
	$(CC) $(CFLAGS) -fPIC -Llibft -lft -o dyn_test main.c
	$(CC) $(CFLAGS) -fPIC -Llibft -lft -o dyn_void void.c

	$(CC) $(CFLAGS) -Llibft -lft -o stt_test main.c libft_malloc.a
	$(CC) $(CFLAGS) -Llibft -lft -o stt_temoin main.c
	$(CC) $(CFLAGS) -Llibft -lft -o stt_void void.c
endif
ifeq ($(HOSTTYPE), x86_64_Linux)
	$(CC) $(CFLAGS) -fPIC -o dyn_test main.c -Llibft -lft

	$(CC) $(CFLAGS) -o stt_test main.c -Wl, -v -Wl, -Llibft -Wl, -lft -Wl, -L. -Wl, -lft_malloc
	$(CC) $(CFLAGS) -o stt_temoin main.c -Llibft -lft
endif

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
	# make -C libft clean

fclean:
	rm -f $(OBJ)
	rm -rf libft_malloc.$(DYNAMIC_EXT)
	rm -f $(DYNAMIC_NAME)
	rm -rf libft_malloc.$(STATIC_EXT)
	rm -f $(STATIC_NAME)
	# make -C libft fclean

re:
	make fclean
	make all

dep:
	make -C libft

.PHONY: dep all $(NAME) clean fclean re tests

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

TESTS = test/test.c test/run.c
TESTS_OBJ = $(subst .c,.o,$(TESTS))

export CC = clang
export CFLAGS = -O3 -Wall -Werror -Wextra -Iinc -Ilibft/inc -Ift_printf/inc
export LDFLAGS = -Llibft -lft -Lft_printf -lftprintf

all: dep $(NAME) tests

test/%.o: test/%.c
	$(CC) $(CFLAGS) $(LDFLAGS) -undefined dynamic_lookup -o $(*F).out $<

%.o: %.c
	m4 inc/malloc.m4 $< | $(CC) -fPIC $(CFLAGS) -c -o $@ -xc -

tests: $(TESTS_OBJ)

$(NAME): $(OBJ)
	$(CC) -dynamiclib -fPIC -o $(DYNAMIC_NAME) $^ libft/libft.a ft_printf/libftprintf.a
	ar rc $(STATIC_NAME) $^ libft/libft.a
	ranlib $(STATIC_NAME)
	rm -rf libft_malloc.$(STATIC_EXT)
	ln -s $(STATIC_NAME) libft_malloc.$(STATIC_EXT)
	rm -rf libft_malloc.$(DYNAMIC_EXT)
	ln -s $(DYNAMIC_NAME) libft_malloc.$(DYNAMIC_EXT)

clean:
	rm -f $(OBJ) $(TESTS_OBJ)
	make -C libft clean

fclean:
	rm -f $(OBJ) $(TESTS_OBJ) test.out run.out
	rm -rf libft_malloc.$(DYNAMIC_EXT)
	rm -f $(DYNAMIC_NAME)
	rm -rf libft_malloc.$(STATIC_EXT)
	rm -f $(STATIC_NAME)
	make -C libft fclean
	make -C ft_printf fclean

re:
	make fclean
	make all

dep:
	make -C libft
	make -C ft_printf

.PHONY: dep all $(NAME) clean fclean re tests

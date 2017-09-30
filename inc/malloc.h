//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-08-12T09:29:04+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-09-28T20:37:50+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <limits.h>

# include <libft.h>

# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/mman.h>

# include <pthread.h>

# include <stdio.h>

# define SPRINTF(args...) { char str[1024] = {0}; sprintf(str, args); ft_putstr_fd(str, ft_malloc.debug_fd); }
// # define SPRINTF(args...) { (void)0; }

# define CHUNK_SIZE (getpagesize() * 8) // short limits
# define INIT_SIZE CHUNK_SIZE

# define TINY (size_t)((getpagesize() / 4) - 1)
# define SMALL (size_t)(getpagesize() / 4)
# define LARGE (size_t)(getpagesize())

# define PROT_FLAGS (PROT_WRITE | PROT_READ)
# define MAP_FLAGS (MAP_ANONYMOUS | MAP_PRIVATE)
# define MMAP(size) mmap(NULL, size, PROT_FLAGS, (MAP_FLAGS), -1, 0)

struct s_malloc {
	void *tiny_head;
	void *small_head;
	void *free_head;
	void *tiny_tail;
	void *small_tail;
	void *free_tail;

	int debug_fd;
};

struct s_chunk_head {
	unsigned int binary_heap;
	void *prev;
	void *next;
};

struct s_malloc ft_malloc;

#define MAP(x) (((struct s_ref*)ft_malloc.global_head)[x])
#define FREE(x) (((struct s_ref*)ft_malloc.free_head)[x])

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void show_alloc_mem(void);
void *last_hand_cache(void *ptr, size_t size);

#endif

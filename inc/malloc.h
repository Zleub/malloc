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

# define SPRINTF(args...) {char str[1024] = {0}; sprintf(str, args); ft_putstr_fd(str, ft_malloc.debug_fd); }
// # define SPRINTF(args...) {(void)0; }

# define CHUNK_SIZE (getpagesize() * 1024) // short limits
# define INIT_SIZE (CHUNK_SIZE / 16)

# define LARGE CHUNK_SIZE
# define TINY 32

# define PROT_FLAGS (PROT_WRITE | PROT_READ)
# define MAP_FLAGS (MAP_ANONYMOUS | MAP_PRIVATE)
# define MMAP(size) mmap(NULL, size, PROT_FLAGS, (MAP_FLAGS), -1, 0)

struct s_malloc {
	void *global_map;
	void *free_map;
	void *global_cache;

	int debug_fd;
	size_t nb_fields;
};

struct s_malloc ft_malloc;

#define MAP(x) (((void**)ft_malloc.global_map)[x])

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void show_alloc_mem(void);
void *last_hand_cache(void *ptr, size_t size);

static int sizes[] = {
	4096,
	8192,
	12288,
	16384,
	20480,
	24576,
	28672,
	32768,
	36864,
	40960,
	45056,
	49152,
	53248,
	57344,
	61440,
	65536,
	69632,
	73728,
	77824,
	81920,
	86016,
	90112,
	94208,
	98304,
	102400,
	106496,
	110592,
	114688,
	118784,
	122880,
	126976,
	131072,
	135168,
	139264,
	143360,
	147456,
	151552,
	155648,
	159744,
	163840,
	167936,
	172032,
	176128,
	180224,
	184320,
	188416,
	192512,
	196608,
	200704,
	0
};

#endif

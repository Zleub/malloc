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

# define LARGE 0000
# define TINY 32

struct binaryheap
{
	unsigned int	size;
	unsigned int	mult;
	unsigned int	is_free;
	void			*parent;
};

struct reference
{
	size_t			remaining;
	void			*map;
};

#define REF_ALLOC(x) (struct reference){ x, MMAP(x) }

# define INIT_SIZE (getpagesize() * 32)
# define CHUNK_SIZE (getpagesize() * 1024) // short limits

# define CASTBH(alloc...) (struct binaryheap)alloc;
# define SIZEBH(size) (unsigned int)(size + sizeof(struct binaryheap))
# define TOBH(x) (*(struct binaryheap *)x)
# define NEXTBH(x) (x + TOBH(x).mult)
# define PREVBH(x) (x - TOBH(x).mult)
# define HALFBH(x) (x + TOBH(x).mult / 2)

# define SHRKBH(x) CASTBH({TOBH(x).size, TOBH(x).mult / 2, TOBH(x).is_free, TOBH(x).parent})

# define IS_FREE(x) (TOBH(x).is_free == 1)

# define PROT_FLAGS (PROT_WRITE | PROT_READ)
# define MAP_FLAGS (MAP_ANONYMOUS | MAP_PRIVATE)
# define MMAP(size) mmap(NULL, size, PROT_FLAGS, (MAP_FLAGS), -1, 0)

struct s_malloc {
	void *global_map;
	void *global_cache;

	int debug_fd;
};

struct s_malloc ft_malloc;

#define MAP(x) (((struct reference*)ft_malloc.global_map)[x])

// extern void	*g_oldp;

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

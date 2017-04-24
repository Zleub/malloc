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

# define CHUNK_SIZE (getpagesize() * 1024) // short limits
# define INIT_SIZE CHUNK_SIZE

# define TINY (size_t)(SMALL / 4)
# define SMALL (size_t)(getpagesize() / 4)
# define LARGE (size_t)CHUNK_SIZE

# define PROT_FLAGS (PROT_WRITE | PROT_READ)
# define MAP_FLAGS (MAP_ANONYMOUS | MAP_PRIVATE)
# define MMAP(size) mmap(NULL, size, PROT_FLAGS, (MAP_FLAGS), -1, 0)

struct s_malloc {
	void *global_map;
	void *global_cache;
	void *free_map;
	void *free_cache;

	int debug_fd;
	size_t map_fields;
	size_t free_fields;
};

struct s_ref {
	void *self;
	void *mmap;
};

struct s_malloc ft_malloc;

#define MAP(x) (((struct s_ref*)ft_malloc.global_map)[x])
#define FREE(x) (((struct s_ref*)ft_malloc.free_map)[x])

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void show_alloc_mem(void);
void *last_hand_cache(void *ptr, size_t size);

#endif

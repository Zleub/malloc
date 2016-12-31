#ifndef MALLOC_H
# define MALLOC_H

#include <unistd.h>
#include <errno.h>
#include <limits.h>

#include <libft.h>

#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/mman.h>

#include <pthread.h>

#include <stdio.h>

int logfd;

// #define SPRINTF(args...) {char str[1024] = {0}; sprintf(str, args); ft_putstr_fd(str, logfd); }
#define SPRINTF(args...) {(void)0; }

#define LARGE 0000

struct binaryheap
{
	unsigned short	size;
	unsigned short	mult;
	unsigned int	is_free;
	void			*parent;
};

# define CHUNK_SIZE (getpagesize() * 8) // short limits

# define CASTBH(alloc...) (struct binaryheap)alloc;
# define SIZEBH(size) (int)(size + sizeof(struct binaryheap))
# define TOBH(x) (*(struct binaryheap *)x)
# define NEXTBH(x) (x + TOBH(x).mult)
# define PREVBH(x) (x - TOBH(x).mult)
# define HALFBH(x) (x + TOBH(x).mult / 2)

# define SHRKBH(x) CASTBH({TOBH(x).size, TOBH(x).mult / 2, TOBH(x).is_free, TOBH(x).parent})

# define IS_FREE(x) (TOBH(x).is_free == 1)

# define PROT_FLAGS (PROT_WRITE | PROT_READ)
# define MAP_FLAGS (MAP_ANONYMOUS | MAP_PRIVATE)
# define MMAP(size) mmap(NULL, size, PROT_FLAGS, (MAP_FLAGS), -1, 0)

extern void	*g_oldp;

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);

#endif

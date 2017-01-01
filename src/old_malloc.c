/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 21:01:33 by adebray           #+#    #+#             */
/*   Updated: 2016/12/31 18:31:45 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// static void __attribute__((constructor)) init(void) {
 // callocp = (void *(*) (size_t, size_t)) dlsym (RTLD_NEXT, "calloc");
 // mallocp = (void *(*) (size_t)) dlsym (RTLD_NEXT, "malloc");
 // reallocp = (void *(*) (void *, size_t)) dlsym (RTLD_NEXT, "realloc");
 // memalignp = (void *(*)(size_t, size_t)) dlsym (RTLD_NEXT, "memalign");
 // freep = (void (*) (void *)) dlsym (RTLD_NEXT, "free");
// };

#include <malloc.h>


extern int global_call_cmp;

void	*g_oldp;
#define INDEX(x) (((void**)g_oldp)[x])
void show_alloc_mem();

void debug_p(void *oldp, size_t size) {
	size_t i = 0;

	(void) oldp;
	while ( i < size ) {
		SPRINTF("%x ", ((unsigned char*)oldp)[i]);
		i += 1;
	}
	SPRINTF("\n");
}


void	*get_next_bloc(void *chunk, size_t size)
{
	void	*newp;
	int		mark;

	mark = 0;
	newp = chunk;
	while (!((IS_FREE(newp) && SIZEBH(size) < TOBH(newp).mult && (mark = 1)) ||
		(SIZEBH(TOBH(newp).size) < TOBH(newp).mult / 2 &&
			SIZEBH(size) < TOBH(newp).mult / 2 && TOBH(newp).mult / 2 > 64 && (mark = 2))))
	{
		// if (IS_FREE(newp) && SIZEBH(size) > TOBH(newp).mult)
		// 	free(newp + sizeof(struct binaryheap));

		// SPRINTF("???\n");
		if (TOBH(newp).mult == 0) {
			SPRINTF("B @ %p\n", newp);
			show_alloc_mem();
			exit(-1);
		}
		newp = newp + TOBH(newp).mult;
		if (newp >= chunk + CHUNK_SIZE) {
			return (NULL);
		}
	}
	if (mark == 1)
	{
		TOBH(newp) = (struct binaryheap){ size, TOBH(newp).mult, 0, chunk };
		return (newp + sizeof(struct binaryheap));
	}
	else if (mark == 2) {
		TOBH(HALFBH(newp)) = (struct binaryheap){ size, TOBH(newp).mult / 2, 0, chunk };
		TOBH(newp) = SHRKBH(newp);
		if (TOBH(newp).mult == 0) {
			SPRINTF("'!'");
			exit(-1);
		}
		return (newp + TOBH(newp).mult) + sizeof(struct binaryheap);
	}
	return (NULL);
}

#define INIT_SIZE (getpagesize() * 64)
#include <fcntl.h>

int sizes[] = {
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

#include <signal.h>
extern char **environ;

void	sighandler(int sig) {
	(void)sig;
	SPRINTF("SIGSEGV\n")
	show_alloc_mem();
	exit(-1);
}

void	*malloc(size_t size) __attribute__((weak_import))
{
	if (!logfd) {
		// ft_putstr("my malloc\n");
		signal(SIGSEGV, sighandler);
		logfd = open("/Users/adebray/malloc/log", O_CREAT | O_TRUNC | O_APPEND | O_WRONLY);
	}
	// SPRINTF("malloc %zu\n", size);
	// show_alloc_mem();

	if (!size)
		return (NULL);

	if (size >= (size_t)(CHUNK_SIZE)) {
		int *ptr_size = sizes;
		while (*ptr_size) {
			if ( (size_t)*(ptr_size + 1) > size) {
				SPRINTF("padding: %zu -> %d\n", size, *ptr_size + 1);
				size = *ptr_size + 1;
				break ;
			}
			ptr_size += 1;
		}

		void *p = MMAP(size + sizeof(struct binaryheap) + 16);
		SPRINTF("%zu @ %p\n", size, p);
		TOBH(p) = (struct binaryheap){ size, size, 0, 0 };
		SPRINTF("%p\n", p);
		return (p + sizeof(struct binaryheap));
	}
	else
	{
		// show_alloc_mem();
		if (g_oldp == 0)
		{
			g_oldp = MMAP(INIT_SIZE);
			SPRINTF("\e[32mmy malloc init %p %d (%lu)\n\033[0m", g_oldp, INIT_SIZE, INIT_SIZE / sizeof(void *));
			SPRINTF("~~~ %s ~~~\n", environ[-2]);
			SPRINTF("chunk %d\n", (unsigned short)CHUNK_SIZE);
			SPRINTF("thread %p\n", pthread_self());
			SPRINTF("main map %p -> %p\n", g_oldp, g_oldp + INIT_SIZE);

			INDEX(0) = MMAP(CHUNK_SIZE);
			if (INDEX(0) == MAP_FAILED) {
				SPRINTF("test\n");
				exit(-1);
			}
			SPRINTF("new map %p -> %p\n", INDEX(0), INDEX(0) + CHUNK_SIZE);
			TOBH(INDEX(0)) = (struct binaryheap){ size, (CHUNK_SIZE), 0, INDEX(0) };
			return (INDEX(0) + sizeof(struct binaryheap));
		}
		else {
			int i = 0;
			while (INDEX(i))
			{
				void *p = get_next_bloc(INDEX(i), size);
				if (p != 0) {
					if ((long)p % 16 != 0) {
						show_alloc_mem();
						SPRINTF(" -> %p %d\n", p, (int)p % 16);
						exit(-1);
					}
					return (p + sizeof(struct binaryheap));
				}
				i += 1;
			}
			// SPRINTF("%zu vs %zu\n", i * sizeof(void*), (unsigned long)INIT_SIZE - 16);
			// show_alloc_mem();
			if (i * sizeof(void*) > (unsigned long)INIT_SIZE - 16) {
				SPRINTF("no more place in oldp\n")
				exit(-1);
			}
			// SPRINTF("%lu vs %d\n", i * sizeof(void*), INIT_SIZE - 16);
			INDEX(i) = MMAP(CHUNK_SIZE);
			if (INDEX(i) == MAP_FAILED) {
				SPRINTF("Map Failed\n");
				return (NULL);
			}
			SPRINTF("new map %p -> %p\n", INDEX(i), INDEX(i) + CHUNK_SIZE);
			TOBH(INDEX(i)) = (struct binaryheap){ size, (CHUNK_SIZE), 0, INDEX(i) };
			return (INDEX(i) + sizeof(struct binaryheap));
		}
	}
	SPRINTF("???\n");
	return (NULL);
}

void *calloc(size_t count, size_t size)
{
	(void)count;
	// SPRINTF("calloc %zu\n", size);
	void *p = malloc(count * size);
	if (!p)
		return (p);
	bzero(p, size);
	return (p);

}
void *realloc(void *ptr, size_t size)
{
	(void)ptr;
	(void)size;
	if (ptr == 0x0)
		return malloc(size);

	SPRINTF("test realloc %p %zu\n", ptr, size);
	void *p = malloc(size);
	SPRINTF("realloc: %p\n", p);
	if (!p) {
		SPRINTF("REALLOC FAIL\n");
		return (p);
	}
	// bzero(p, size);
	strncpy(p, ptr, TOBH((ptr - sizeof(struct binaryheap))).size );
	free(ptr);
	return (p);
}
// void *reallocf(void *ptr, size_t size)
// {
// 	(void)ptr;
// 	(void)size;
// 	SPRINTF("test reallocf\n");
// 	return (NULL);
// }

// void *valloc(size_t size)
// {
// 	(void)size;
// 	SPRINTF("test valloc\n");
// 	return (NULL);
// }

// malloc_zone_t *malloc_create_zone(vm_size_t start_size, unsigned flags)
// {
// 	SPRINTF("malloc_create_zone\n");
// }

// voidmalloc_destroy_zone(malloc_zone_t *zone)
// {
// 	SPRINTF("malloc_destroy_zone\n");
// }

// malloc_zone_t *malloc_default_zone(void)
// {
// 	SPRINTF("malloc_default_zone\n");
// }

// malloc_zone_t *malloc_zone_from_ptr(const void *ptr)
// {
// 	SPRINTF("malloc_zone_from_ptr\n");
// }

// void *malloc_zone_malloc(void *zone, size_t size)
// {
// 	(void)zone;
// 	SPRINTF("malloc_zone_malloc %zu\n", size);
// 	return malloc(size);
// }
// void *malloc_zone_calloc(void *zone, size_t size)
// {
// 	(void)zone;
// 	SPRINTF("malloc_zone_calloc %zu\n", size);
// 	void *p = malloc(size);
// 	bzero(p, size);
// 	return (p);
// }


// void *malloc_zone_valloc(malloc_zone_t *zone, size_t size)
// {
// 	SPRINTF("malloc_zone_valloc\n");
// }

// void *malloc_zone_realloc(malloc_zone_t *zone, void *ptr, size_t size)
// {
// 	SPRINTF("malloc_zone_realloc\n");
// }

// void *malloc_zone_memalign(malloc_zone_t *zone, size_t alignment, size_t size)
// {
// 	SPRINTF("malloc_zone_memalign\n");
// }

// void malloc_zone_free(malloc_zone_t *zone, void *ptr)
// {
// 	SPRINTF("malloc_zone_free\n");
// }


void	free(void *p)
{
	void		*newp;
		return ;

	if (p == 0 || (long)p & 0x700000000000) {
		SPRINTF("not free @ %p\n", p);
	}

	int i = 0;
	while (INDEX(i))
	{
		if (!( INDEX(i) < p && p < INDEX(i) + CHUNK_SIZE )) {
			i += 1;
		}
		else
			break;
	}
	if (INDEX(i) == 0) {
		SPRINTF("not free %p %p %p\n", INDEX(i), p, INDEX(i) + CHUNK_SIZE);
		return ;
	}

	newp = p - sizeof(struct binaryheap);
	SPRINTF("free %p [%p], %d\n", p, newp, TOBH((newp)).size);

	TOBH(newp).is_free = 1;

	if (TOBH(newp).size >= CHUNK_SIZE) {
		munmap(newp, TOBH(newp).size);
		return ;
	}
	if (NEXTBH(newp) < TOBH(newp).parent + CHUNK_SIZE && IS_FREE(NEXTBH(newp)) &&
		(TOBH(NEXTBH(newp)).mult == TOBH(newp).mult))
	{
		TOBH(newp) = (struct binaryheap){
			TOBH(newp).size, TOBH(newp).mult * 2, 1, TOBH(newp).parent
		};
		// free(newp + sizeof(struct binaryheap));
	}
	if (PREVBH(newp) > TOBH(newp).parent && IS_FREE(PREVBH(newp)) &&
		(TOBH(PREVBH(newp)).mult == TOBH(newp).mult))
	{
		TOBH(PREVBH(newp)) = (struct binaryheap){
			TOBH(PREVBH(newp)).size, TOBH(PREVBH(newp)).mult * 2, 1,
			TOBH(PREVBH(newp)).parent
		};
		// free(PREVBH(newp) + sizeof(struct binaryheap));
	}

	// show_alloc_mem();
}

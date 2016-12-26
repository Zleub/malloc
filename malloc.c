/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 21:01:33 by adebray           #+#    #+#             */
/*   Updated: 2016/12/26 23:32:30 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	*g_oldp;

extern int global_call_cmp;

#define INDEX(x) (((void**)g_oldp)[x])
void show_alloc_mem();

void debug_p(void *oldp, size_t size) {
	size_t i = 0;

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
			SIZEBH(size) < TOBH(newp).mult / 2 && (mark = 2))))
	{
		// if (IS_FREE(newp) && SIZEBH(size) > TOBH(newp).mult)
		// 	free(newp + sizeof(struct binaryheap));

		if (TOBH(newp).mult == 0) {
			SPRINTF("B @ %p\n", newp);
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
		return (newp + TOBH(newp).mult) + sizeof(struct binaryheap);
	}
	return (NULL);
}

#define INIT_SIZE (getpagesize() * 4)
  #include <fcntl.h>
void	*malloc(size_t size)
{
	logfd = open("./log", O_CREAT | O_APPEND | O_WRONLY);
	// SPRINTF("malloc %zu\n", size);
	// show_alloc_mem();

	if (size >= (size_t)(CHUNK_SIZE)) {
		void *p = MMAP(size + sizeof(struct binaryheap));
		// SPRINTF("%zu @ %p\n", size, p);
		TOBH(p) = (struct binaryheap){ size, size, 0, 0 };
		return (p + sizeof(struct binaryheap));
	}
	else
	{
		if (g_oldp == 0)
		{
			g_oldp = MMAP(getpagesize() * 4);
			// SPRINTF("my malloc init %p %d (%lu)\n", g_oldp, INIT_SIZE, INIT_SIZE / sizeof(void *));
			// SPRINTF("%p -> %p\n", g_oldp, g_oldp + INIT_SIZE);

			INDEX(0) = MMAP(CHUNK_SIZE);
			TOBH(INDEX(0)) = (struct binaryheap){ size, (CHUNK_SIZE), 0, INDEX(0) };
			return (INDEX(0) + sizeof(struct binaryheap));
		}
		else {
			int i = 0;
			while (INDEX(i))
			{
				void *p = get_next_bloc(INDEX(i), size);
				if (p != 0)
					return (p);
				i += 1;
			}
			if (i * sizeof(void*) > (unsigned long)INIT_SIZE - 16) {
				SPRINTF("no more place in oldp\n")
				exit(-1);
			}
			// SPRINTF("%lu vs %d\n", i * sizeof(void*), INIT_SIZE - 16);
			INDEX(i) = MMAP(CHUNK_SIZE);
			if (INDEX(i) == MAP_FAILED) {
				return (NULL);
			}
			TOBH(INDEX(i)) = (struct binaryheap){ size, (CHUNK_SIZE), 0, INDEX(i) };
			return (INDEX(i) + sizeof(struct binaryheap));
		}
	}
	return (NULL);
}

void *calloc(size_t count, size_t size)
{
	(void)count;
	// SPRINTF("calloc %zu\n", size);
	void *p = malloc(count * size);
	bzero(p, size);
	return (p);

}
void *realloc(void *ptr, size_t size)
{
	(void)ptr;
	(void)size;
	if (ptr == 0x0)
		return malloc(size);

	SPRINTF("test realloc %p\n", ptr);
	void *p = malloc(size);
	strncpy(p, ptr, TOBH((ptr - sizeof(struct binaryheap))).size );
	// bzero(p, size);
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

	if (p == 0 || (unsigned long)p & -1)
		return ;
	newp = p - sizeof(struct binaryheap);


	SPRINTF("free @ %x %p [%p], %d\n", (unsigned int)p, p, newp, TOBH(newp).size);
	TOBH(newp).is_free = 1;

	if (TOBH(newp).size > CHUNK_SIZE) {
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
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 21:01:33 by adebray           #+#    #+#             */
/*   Updated: 2016/12/23 22:53:52 by adebray          ###   ########.fr       */
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
	// if (global_call_cmp > 60000)
	// SPRINTF("%p %p %s\n", newp, chunk, TOBH(newp).parent == chunk ? "true" : "false");
	while (!((IS_FREE(newp) && SIZEBH(size) < TOBH(newp).mult && (mark = 1)) ||
		(SIZEBH(TOBH(newp).size) < TOBH(newp).mult / 2 &&
			SIZEBH(size) < TOBH(newp).mult / 2 && (mark = 2))))
	{
		// if (IS_FREE(newp) && SIZEBH(size) > TOBH(newp).mult)
		// 	free(newp + sizeof(struct binaryheap));
		// SPRINTF("A\n");
		if (TOBH(newp).mult == 0) {
			SPRINTF("B @ %p\n", newp);
			// show_alloc_mem(newp);
			exit(-1);
		}
		newp = newp + TOBH(newp).mult;
		if (newp >= chunk + CHUNK_SIZE) {
			return (NULL);
		}
	}
	if (mark == 1)
	{
		// SPRINTF("D\n");
		TOBH(newp) = (struct binaryheap){ size, TOBH(newp).mult, 0, chunk };
		return (newp + sizeof(struct binaryheap));
	}
	else if (mark == 2) {
		// SPRINTF("E @ %p, parent: %p, parentsize %p, distanceformend: %lx\n", HALFBH(newp), TOBH(newp).parent, TOBH(newp).parent + CHUNK_SIZE, TOBH(newp).parent + CHUNK_SIZE - newp);
		TOBH(HALFBH(newp)) = (struct binaryheap){ size, TOBH(newp).mult / 2, 0, chunk };
		TOBH(newp) = SHRKBH(newp);
		// debug_p(chunk, 32);
		SPRINTF("%p, %d, %lu = %p\n", newp, TOBH(newp).mult, sizeof(struct binaryheap), (newp + TOBH(newp).mult) + sizeof(struct binaryheap));
		return (newp + TOBH(newp).mult) + sizeof(struct binaryheap);
	}
	return (NULL);
}

void	*malloc(size_t size)
{
	SPRINTF("%zu\n", size);
	show_alloc_mem();

	if (size >= (size_t)(CHUNK_SIZE)) {
		void *p = MMAP(size + sizeof(struct binaryheap));
		SPRINTF("%zu @ %p\n", size, p);
		TOBH(p) = (struct binaryheap){ size, size, 0, 0 };
		return (p + sizeof(struct binaryheap));
	}
	else
	{
		if (g_oldp == 0)
		{
			g_oldp = MMAP(getpagesize() * 4);
			// ft_bzero(g_oldp, getpagesize() * 8);
			INDEX(0) = MMAP(CHUNK_SIZE);
			// SPRINTF("%p\n", INDEX(0));
			// debug_oldp(g_oldp, getpagesize());

			TOBH(INDEX(0)) = (struct binaryheap){ size, (CHUNK_SIZE), 0, INDEX(0) };
			SPRINTF("A %zu @ %p in %p + %d\n", size, INDEX(0), g_oldp, 0);
			show_alloc_mem();
			// debug_p(INDEX(0), 32);
			SPRINTF("%p\n", INDEX(0) + sizeof(struct binaryheap));
			return (INDEX(0) + sizeof(struct binaryheap));
		}
		else {
			int i = 0;
			// debug_p(INDEX(i), 32);
			while (INDEX(i))
			{
				void *p = get_next_bloc(INDEX(i), size);
				if (p != 0) {
					// SPRINTF("%p in %p @ %d\n", p, INDEX(i), i);
					SPRINTF("B %zu @ %p in %p + %d\n", size, p, INDEX(i), i);
					return (p);
				}
				i += 1;
			}
			INDEX(i) = MMAP(CHUNK_SIZE);
			SPRINTF("C %zu @ %p in %p + %d\n", size, INDEX(i), INDEX(i), i);
			if (INDEX(i) == MAP_FAILED) {
				return (NULL);
			}
			TOBH(INDEX(i)) = (struct binaryheap){ size, (CHUNK_SIZE), 0, INDEX(i) };
			return (INDEX(i) + sizeof(struct binaryheap));
			// return (get_next_bloc(INDEX(0), size));
		}
	}
	return (NULL);
}

void	free(void *p)
{
	void		*newp;

	if (p == 0)
		return ;
	newp = p - sizeof(struct binaryheap);

	if ((unsigned long)p & 0x7f0000000000)
		return ;
	SPRINTF("free @ %lx\n", (unsigned long)p & 0x7f0000000000);
	TOBH(newp).is_free = 1;

	if (TOBH(newp).size > CHUNK_SIZE) {
		// SPRINTF("%p\n", newp);
		munmap(newp, TOBH(newp).size);
		return ;
	}
	if (NEXTBH(newp) < TOBH(newp).parent + CHUNK_SIZE && IS_FREE(NEXTBH(newp)) &&
		(TOBH(NEXTBH(newp)).mult == TOBH(newp).mult))
	{
		// SPRINTF("A %d %d\n", TOBH(newp).mult, TOBH(newp).mult * 2);
		TOBH(newp) = (struct binaryheap){
			TOBH(newp).size, TOBH(newp).mult * 2, 1, TOBH(newp).parent
		};
		// free(newp + sizeof(struct binaryheap));
	}
	// SPRINTF("test %s\n", PREVBH(newp) > TOBH(newp).parent ? "true" : "false");
	if (PREVBH(newp) > TOBH(newp).parent && IS_FREE(PREVBH(newp)) &&
		(TOBH(PREVBH(newp)).mult == TOBH(newp).mult))
	{
		// SPRINTF("A %d %d\n", TOBH(PREVBH(newp)).mult, TOBH(PREVBH(newp)).mult * 2);
		TOBH(PREVBH(newp)) = (struct binaryheap){
			TOBH(PREVBH(newp)).size, TOBH(PREVBH(newp)).mult * 2, 1,
			TOBH(PREVBH(newp)).parent
		};
		// free(PREVBH(newp) + sizeof(struct binaryheap));
	}
	// show_alloc_mem();
}

void *realloc(void *ptr, size_t size)
{
	(void)ptr;
	(void)size;
	SPRINTF("test realloc\n");
	return (NULL);
}

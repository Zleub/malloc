/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 21:01:33 by adebray           #+#    #+#             */
/*   Updated: 2016/12/22 23:26:54 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	*g_oldp;

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
		newp = newp + TOBH(newp).mult;
		if (newp >= chunk + CHUNK_SIZE) {
			// SPRINTF("TEST\n");
			return (NULL);
		}
	}
	if (mark == 1)
	{
		TOBH(newp) = (struct binaryheap){ size, TOBH(newp).mult, 0 };
		return (newp + sizeof(struct binaryheap));
	}
	TOBH(HALFBH(newp)) = (struct binaryheap){ size, TOBH(newp).mult / 2, 0 };
	TOBH(newp) = SHRKBH(newp);
	return (newp + TOBH(newp).mult) + sizeof(struct binaryheap);
}

#define INDEX(x) (((void **)g_oldp)[x])
void show_alloc_mem();

void	*malloc(size_t size)
{
	// SPRINTF("%zu\n", size);
	// show_alloc_mem();

	if (size >= (size_t)(getpagesize() - 16))
		return (MMAP(size));
	else
	{
		if (g_oldp == 0)
		{
			g_oldp = MMAP(getpagesize() * 4);
			INDEX(0) = MMAP(CHUNK_SIZE);
			TOBH(INDEX(0)) = (struct binaryheap){ size, (CHUNK_SIZE), 0 };
			return (INDEX(0) + sizeof(struct binaryheap));
		}
		else {
			int i = 0;
			while (INDEX(i))
			{
				void *p = get_next_bloc(INDEX(i), size);
				if (p != 0) {
					// SPRINTF("%p in %p @ %d\n", p, INDEX(i), i);
					return (p);
				}
				i += 1;
			}
			INDEX(i) = MMAP(CHUNK_SIZE);
			TOBH(INDEX(i)) = (struct binaryheap){ size, (CHUNK_SIZE), 0 };
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
	TOBH(newp).is_free = 1;
	if (NEXTBH(newp) < g_oldp + CHUNK_SIZE && IS_FREE(NEXTBH(newp)) &&
		(TOBH(NEXTBH(newp)).mult == TOBH(newp).mult))
		TOBH(newp) = (struct binaryheap){
			TOBH(newp).size, TOBH(newp).mult * 2, 1
		};
	if (PREVBH(newp) < g_oldp + CHUNK_SIZE && IS_FREE(PREVBH(newp)) &&
		(TOBH(PREVBH(newp)).mult == TOBH(newp).mult))
		TOBH(PREVBH(newp)) = (struct binaryheap){
			TOBH(PREVBH(newp)).size, TOBH(PREVBH(newp)).mult * 2, 1
		};
}

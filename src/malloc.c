/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 00:35:03 by adebray           #+#    #+#             */
/*   Updated: 2017/10/04 00:38:10 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <ft_printf.h>

struct s_malloc ft_malloc;

include()

void	*map_tiny(void)
{
	m4_map(TINY);
}

void	*map_small(void)
{
	m4_map(SMALL);
}

void	*malloc(size_t size)
{
	void *p;

	if (!ft_malloc.tiny_head)
		init();
	if (size <= TINY)
		m4_alloc(TINY);
	if (size <= SMALL)
		m4_alloc(SMALL);
	p = MMAP(size + (sizeof(struct s_chunk_head)));
	if (!ft_malloc.large_head)
		ft_malloc.large_head = (ft_malloc.large_tail = p);
	else
		((struct s_chunk_head*)ft_malloc.large_tail)->next = p;
	*((struct s_chunk_head *)p) = (struct s_chunk_head){
		.binary_heap = size,
		.prev = ft_malloc.large_tail,
		.next = NULL
	};
	ft_malloc.large_tail = p;
	if (p == MAP_FAILED)
		return (0);
	return (p + (sizeof(struct s_chunk_head)));
}

void	free(void *p)
{
	m4_free_loop(TINY);
	m4_free_loop(SMALL);
}

void	*realloc(void *p, size_t size)
{
	struct s_chunk_head *h;
	int		size_;
	void	*np;

	size_ = 0;
	free(p);
	m4_realloc_loop(TINY);
	m4_realloc_loop(SMALL);
	np = malloc(size);
	if (size_)
		ft_strncpy(np, p, size_);
	else if (p != NULL)
	{
		h = (p - sizeof(struct s_chunk_head));
		ft_strncpy(np, p, h->binary_heap);
		munmap(p - 4, h->binary_heap);
	}
	return (np);
}

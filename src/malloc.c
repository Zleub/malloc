/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 00:35:03 by adebray           #+#    #+#             */
/*   Updated: 2017/12/24 17:32:34 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <ft_printf.h>

struct s_malloc ft_malloc;

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

	SPRINTF("malloc %zu\n", size);
	show_alloc_mem();
	SPRINTF("\n");

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

	SPRINTF("malloc large %p %zu\n", p, size);

	return (p + (sizeof(struct s_chunk_head)));
}

void	free(void *p)
{

	if (!p)
		return;
	SPRINTF("free %p\n", p);
	m4_free_loop(TINY);
	m4_free_loop(SMALL);
	SPRINTF("free large ?\n");
}

void	*realloc(void *p, size_t size)
{
	// struct s_chunk_head *h;
	int		size_;
	void	*np;

	size_ = 0;
	free(p);
	m4_realloc_loop(TINY);
	m4_realloc_loop(SMALL);
	np = malloc(size);
	// SPRINTF(
	// 	"\tp: %p\n"
	// 	"\tsize: %zu\n"
	// 	"\tsize_: %d\n"
	// 	"\n", p, size, size_);
	// if (p != NULL)
	// {
	// 	h = (p - sizeof(struct s_chunk_head));
	// 	// if (size) {
	// 		// SPRINTF("A %p %zu\n", p, size);
	// 		ft_strncpy(np, p, size);
	// 	// }
	// 	// else {
	// 	// 	SPRINTF("B %p %u\n", p, h->binary_heap);
	// 	// 	ft_strncpy(np, p, h->binary_heap);
	// 	// }
	// 	// ft_printf("%d\n", h == ft_malloc.large_head);
	// 	// munmap(h, h->binary_heap);
	// }
	// else if (size_) {
	// SPRINTF("realloc\n");
	// SPRINTF("np: %p, p: %p\n", np, p);
	// SPRINTF("size: %zu, size_: %d\n", size, size_);
	if (p)
		strncpy(np, p, size_ ? size_ : size);
		// SPRINTF("strncpy: %p\n", strncpy(np, p, size_ ? size_ : size) );
		// ft_strncpy(np, p, size_);
	// }
	return (np);
}

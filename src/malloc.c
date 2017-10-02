/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 00:35:03 by adebray           #+#    #+#             */
/*   Updated: 2017/10/03 01:40:07 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

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

	if (!ft_malloc.tiny_head)
		init();
	if (size <= TINY)
		m4_alloc(TINY);
	if (size <= SMALL)
		m4_alloc(SMALL);
	p = MMAP(size + 4);
	*((int *)p) = size;
	if (p == MAP_FAILED)
		return (0);
	return (p + 4);
}

void	free(void *p)
{
	m4_free_loop(TINY);
	m4_free_loop(SMALL);
}

void	*realloc(void *p, size_t size)
{
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
		ft_strncpy(np, p, *((int *)(p - 4)));
		munmap(p - 4, *((int *)(p - 4)));
	}
	return (np);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 00:21:16 by adebray           #+#    #+#             */
/*   Updated: 2017/10/04 00:27:53 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/*
** # define SPRINTF(args...) { char str[1024] = {0}; \
**     sprintf(str, args); \
**     ft_putstr_fd(str, ft_malloc.debug_fd); \
** }
*/
# define SPRINTF(args...) { (void)0; }

# define CHUNK_SIZE (getpagesize() * 8)

# define TINY (size_t)((getpagesize() / 4) - 1)
# define SMALL (size_t)(getpagesize() / 4)
# define LARGE (size_t)(getpagesize())

# define PROT_FLAGS (PROT_WRITE | PROT_READ)
# define MAP_FLAGS (MAP_ANONYMOUS | MAP_PRIVATE)
# define MMAP(size) mmap(NULL, size, PROT_FLAGS, (MAP_FLAGS), -1, 0)

struct	s_malloc {
	void	*tiny_start;

	void	*tiny_head;
	void	*tiny_tail;

	void	*small_start;

	void	*small_head;
	void	*small_tail;

	void	*large_head;
	void	*large_tail;

	int		debug_fd;
};

struct	s_chunk_head {
	unsigned int	binary_heap;
	void			*prev;
	void			*next;
};

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);
void	init(void);
void	*map_tiny(void);
void	*map_small(void);

#endif

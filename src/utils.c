/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 00:26:32 by adebray           #+#    #+#             */
/*   Updated: 2017/10/04 00:33:00 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>
#include <malloc.h>

#define COLORIZE(r,g,b) (16 + 36 * (r) + 6 * (g) + (b))

extern struct s_malloc ft_malloc;

void		init(void)
{
	map_tiny();
	map_small();
}

static void	gradient(int c)
{
	int a;
	int x;

	x = 1;
	while (x < c + 1)
	{
		a = (x / 6) > 5 ? 6 - (x / 6) : 5;
		ft_printf("\x1B[38;5;%dm•\x1B[0m", COLORIZE(
			x > 5 ? a : x,
			(x / 6) > 5 ? 5 : (x / 6),
			0));
		x += 1;
	}
	ft_printf("\n");
}

static void	pretty_print(struct s_chunk_head *h)
{
	int i;
	int c;
	int b;

	while (h->prev)
		h = h->prev;
	while (h)
	{
		i = 0;
		c = 0;
		b = h->binary_heap;
		while (i < 32)
		{
			if ((b & 0x1) != 0)
			{
				b = b >> 1;
				c += 1;
			}
			i += 1;
		}
		c = (c * 42) / 32;
		ft_printf("[%p -> %p] ", h, h + CHUNK_SIZE);
		gradient(c);
		h = h->next;
	}
}

void		show_alloc_mem(void)
{
	struct s_chunk_head *h;

	ft_printf("~ TINY\n");
	pretty_print(ft_malloc.tiny_head);
	ft_printf("~ SMALL\n");
	pretty_print(ft_malloc.small_head);
	ft_printf("~ LARGE\n");
	h = ft_malloc.large_head;
	while (h)
	{
		ft_printf("[%p] %u\n", h, h->binary_heap);
		h = h->next;
	}
}

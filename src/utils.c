#include <libft.h>
#include <ft_printf.h>
#include <malloc.h>
#define COLORIZE(r,g,b) (16 + 36 * (r) + 6 * (g) + (b))

extern struct s_malloc ft_malloc;

void	pretty_print(struct s_chunk_head *h) {
	while (h->prev) {
		h = h->prev;
	}

	while (h) {
		int i = 0;
		int c = 0;
		int $ = h->binary_heap;
		while (i < 32) {
			if (($ & 0x1) != 0)
			c += 1;
			$ = $ >> 1;
			i += 1;
		}

		c = (c * 42) / 32;
		int __ = 0;
		ft_printf("~ [%p] -> [%p]", h, h + INIT_SIZE);
		while (__ < c) {
			int _ = __ / 6;
			int color = COLORIZE(
				__ > 5 ? (_ > 5 ? 6 - _ : 5) : __,
				_ > 5 ? 5 : _,
				0
			);
			(void)color;
			ft_printf("\x1B[38;5;%dm•\x1B[0m", color);
			__ += 1;
		}
		ft_printf("\n");
		h = h->next;
	}
}


void	show_alloc_mem(void)
{
	ft_printf("~ TINY\n");
	pretty_print(ft_malloc.tiny_head);
	ft_printf("~ SMALL\n");
	pretty_print(ft_malloc.small_head);
}

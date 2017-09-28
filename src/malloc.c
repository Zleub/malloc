//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-08-12T09:34:58+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-09-28T20:54:36+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#include <malloc.h>

void init(void)
{
	ft_malloc.debug_fd = open("/Users/adebray/malloc/log", O_CREAT | O_TRUNC | O_WRONLY, 0744);
	ft_malloc.tiny_head = MMAP(INIT_SIZE);
	ft_malloc.tiny_tail = ft_malloc.tiny_head;
	ft_malloc.small_head = MMAP(INIT_SIZE);
	ft_malloc.small_tail = ft_malloc.small_head;
	// ft_malloc.free_head = MMAP(INIT_SIZE);
	// ft_malloc.free_tail = ft_malloc.free_head;

	SPRINTF("~~~ %s ~~~\n", getprogname());
	SPRINTF("~ my init %p %d\n", ft_malloc.tiny_head, INIT_SIZE);
	SPRINTF("~ main map %p -> %p\n", ft_malloc.small_head, ft_malloc.small_head + INIT_SIZE);
}

void *malloc(size_t size)
{
	if (!ft_malloc.tiny_head)
		init();
	if (size == 666) {
		SPRINTF("~ tiny map %p -> %p [%lu / %lu]\n", ft_malloc.tiny_head, ft_malloc.tiny_tail, (ft_malloc.tiny_tail - ft_malloc.tiny_head) / TINY, (ft_malloc.tiny_head + INIT_SIZE - ft_malloc.tiny_head) / TINY);
		SPRINTF("~ small map %p -> %p [%lu / %lu]\n", ft_malloc.small_head, ft_malloc.small_tail, (ft_malloc.small_tail - ft_malloc.small_head) / SMALL, (ft_malloc.small_head + INIT_SIZE - ft_malloc.small_head) / SMALL);
		// SPRINTF("~ free map %p -> %p [%lu / %lu]\n", ft_malloc.free_head, ft_malloc.free_tail, (ft_malloc.free_tail - ft_malloc.free_head) / 32);
	}

	SPRINTF("MALLOC %zu\n", size);
	if (size <= TINY) {
		void *_r = ft_malloc.tiny_tail;
		if (ft_malloc.tiny_tail + TINY > ft_malloc.tiny_head + INIT_SIZE) {
			SPRINTF("MAP\n");
			ft_malloc.tiny_tail = MMAP(INIT_SIZE);
			ft_malloc.tiny_head = ft_malloc.tiny_tail;
			return (ft_malloc.tiny_head);
		}
		ft_malloc.tiny_tail += TINY;
		return (_r);
	}
	if (size <= SMALL) {
		void *_r = ft_malloc.small_tail;
		if (ft_malloc.small_tail + SMALL > ft_malloc.small_head + INIT_SIZE) {
			SPRINTF("MAP\n");
			ft_malloc.small_tail = MMAP(INIT_SIZE);
			ft_malloc.small_head = ft_malloc.small_tail;
			return (ft_malloc.small_head);
		}
		ft_malloc.small_tail += SMALL;
		return (_r);
	}
	// SPRINTF("~ MAP\n");
	SPRINTF("MAP\n");
	return (MMAP(4096));
	// return (0);
}

void free(void *p) {
	(void)p;
}

// main map 0x1035a5000 -> 0x1035a9000
// main map 0x1035a53fb -> 0x1035a93fb

#include <malloc.h>

struct s_malloc ft_malloc;

m4_map(tiny);
m4_map(small);

void init(void)
{
	map_tiny();
	map_small();
}

void *malloc(size_t size)
{
	if (!ft_malloc.tiny_head)
		init();

	if (size <= TINY) {
		m4_alloc(tiny);
	}
	if (size <= SMALL) {
		m4_alloc(small);
	}
	void *p = MMAP(size + 4);
	*((int *)p) = size;
	if (p == MAP_FAILED)
		return (0);
	return (p + 4);
}


void free(void *p) {
	m4_free_loop(tiny);
	m4_free_loop(small);
}

void *realloc(void *p, size_t size) {
	int _size = 0;

	m4_realloc_loop(tiny);
	m4_realloc_loop(small);
	void *np = malloc(size);
	if (_size)
		strncpy(np, p, _size);
	else if (p != NULL) {
		strncpy(np, p, *((int *)(p - 4)));
		munmap(p - 4, *((int *)(p - 4)));
	}
	return (np);
}

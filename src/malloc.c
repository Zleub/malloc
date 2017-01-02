#include <malloc.h>

struct s_malloc ft_malloc;

void	*last_hand_cache(void *ptr, size_t size)
{
	static void *p;

	if (ptr) {
		p = ptr;
		return (ptr);
	}
	else if (p && size) {
		if ( (IS_FREE(p) && SIZEBH(size) < TOBH(p).mult) )
		{
			TOBH(p) = (struct binaryheap){ size, TOBH(p).mult, 0, TOBH(p).parent };
			return (p);
		}

		if (SIZEBH(TOBH(p).size) < TOBH(p).mult / 2 && SIZEBH(size) < TOBH(p).mult / 2 && TOBH(p).mult / 2 > TINY)
		{
			TOBH(HALFBH(p)) = (struct binaryheap){ size, TOBH(p).mult / 2, 0, TOBH(p).parent };
			TOBH(p) = SHRKBH(p);
			return (p + TOBH(p).mult);
		}
	}
	else if (ptr == NULL && size == 0)
		return p;
	return (NULL);
}

void	show_alloc_mem(void)
{
	int i;
	int j;
	int chunk_size;

	i = 0;
	while (MAP(i))
	{
		j = 0;
		chunk_size = 0;
		SPRINTF("%d: %p\n", i, MAP(i));
		while (j < CHUNK_SIZE) {
			if (MAP(i) + j == last_hand_cache(NULL, 0))
				SPRINTF("C");
			SPRINTF("\t%p %d [%d] %s\n", MAP(i) + j, TOBH((MAP(i) + j)).size, TOBH((MAP(i) + j)).mult, TOBH((MAP(i) + j)).is_free ? "FREE" : "OCCUPIED");
			chunk_size += TOBH((MAP(i) + j)).mult;
			j += TOBH((MAP(i) + j)).mult;
		}
		SPRINTF("[ %d ] %s\n", chunk_size, chunk_size == CHUNK_SIZE ? "true" : "false");
		i += 1;
	}
}

void	*large_alloc(size_t size)
{
	int *ptr_size = sizes;

	while (*ptr_size)
	{
		if ( (size_t)*(ptr_size + 1) > size)
		{
			SPRINTF("padding: %zu -> %d\n", size, *ptr_size + 1);
			size = *ptr_size + 1;
			break ;
		}
		ptr_size += 1;
	}

	void *p = MMAP(size + sizeof(struct binaryheap) + 16);
	if (p == MAP_FAILED)
		return (NULL);

	SPRINTF("%zu @ %p\n", size, p);
	TOBH(p) = (struct binaryheap){ size, size, 0, 0 };
	SPRINTF("%p\n", p);
	return (p + sizeof(struct binaryheap));
}

void	*get_next_map(size_t index, size_t size)
{
	MAP(index) = MMAP(CHUNK_SIZE);
	if (MAP(index) == MAP_FAILED) {
		SPRINTF("Map Failed\n");
		return (NULL);
	}
	SPRINTF("new map %p -> %p\n", MAP(index), MAP(index) + CHUNK_SIZE);
	TOBH(MAP(index)) = (struct binaryheap){ size, (CHUNK_SIZE), 0, MAP(index) };
	last_hand_cache(MAP(index), 0);
	return (MAP(index) + sizeof(struct binaryheap));
}

void	*get_next_bloc(void *chunk, size_t size)
{
	void	*newp;
	int		mark;

	mark = 0;
	newp = chunk;
	while (!((IS_FREE(newp) && SIZEBH(size) < TOBH(newp).mult && (mark = 1)) ||
		(SIZEBH(TOBH(newp).size) < TOBH(newp).mult / 2 &&
			SIZEBH(size) < TOBH(newp).mult / 2 && TOBH(newp).mult / 2 > TINY && (mark = 2))))
	{
		// if (IS_FREE(newp) && SIZEBH(size) > TOBH(newp).mult)
		// 	free(newp + sizeof(struct binaryheap));

		newp = newp + TOBH(newp).mult;
		if (newp >= chunk + CHUNK_SIZE)
			return (NULL);
	}
	if (mark == 1)
	{
		TOBH(newp) = (struct binaryheap){ size, TOBH(newp).mult, 0, chunk };
		return (newp);
	}
	else if (mark == 2) {
		TOBH(HALFBH(newp)) = (struct binaryheap){ size, TOBH(newp).mult / 2, 0, chunk };
		TOBH(newp) = SHRKBH(newp);
		return (newp + TOBH(newp).mult);
	}
	else
		return (NULL);
}


const char *getprogname(void);

void	sighandler(int sig)
{
	(void)sig;
	SPRINTF("SIGSEGV\n")
	show_alloc_mem();
	exit(-1);
}

void	init(void)
{
	signal(SIGSEGV, sighandler);
	ft_malloc.debug_fd = open("/Users/adebray/malloc/log",
		O_CREAT | O_TRUNC | O_APPEND | O_WRONLY, 0744);

	ft_malloc.global_map = MMAP(INIT_SIZE);
	SPRINTF("\e[32mmy malloc init %p %d (%lu)\n\033[0m", ft_malloc.global_map, INIT_SIZE, INIT_SIZE / sizeof(void *));
	SPRINTF("~~~ %s ~~~\n", getprogname());
	SPRINTF("main %d | chunk %d\n", INIT_SIZE, (unsigned short)CHUNK_SIZE);
	SPRINTF("thread %p\n", (void*)pthread_self());
	SPRINTF("main map %p -> %p\n", ft_malloc.global_map, ft_malloc.global_map + INIT_SIZE);

	MAP(0) = MMAP(CHUNK_SIZE);
	if (MAP(0) == MAP_FAILED) {
		SPRINTF("test\n");
		exit(-1);
	}
	SPRINTF("new map %p -> %p\n", MAP(0), MAP(0) + CHUNK_SIZE);
	TOBH(MAP(0)) = (struct binaryheap){ CHUNK_SIZE, CHUNK_SIZE, 1, MAP(0) };

	last_hand_cache(MAP(0), 0);
}

void	*malloc(size_t size)
{
	if (!ft_malloc.debug_fd)
		init();

	if (!size)
		return (NULL);

	// SPRINTF("malloc: %zu\n", size);
	// show_alloc_mem();

	if (size >= (size_t)(CHUNK_SIZE))
		return (large_alloc(size));
	else
	{
			void *p = last_hand_cache(NULL, size);
			if (p)
				return (p + sizeof(struct binaryheap));

			int i = 0;
			while (MAP(i))
			{
				void *p = get_next_bloc(MAP(i), size);
				if (p != 0) {
					if ((long)p % 16 != 0) {
						show_alloc_mem();
						SPRINTF(" -> %p %d\n", p, (int)p % 16);
						exit(-1);
					}
					return last_hand_cache(p, 0) + sizeof(struct binaryheap);
				}
				i += 1;
			}
			if (i * sizeof(void*) > (unsigned long)INIT_SIZE - 16) {
				SPRINTF("no more place in oldp\n")
				exit(-1);
			}
			return get_next_map(i, size);
	}
}

void	free(void *p)
{
	void		*newp;
		return ;

	if (p == 0 || (long)p & 0x700000000000) {
		SPRINTF("not free @ %p\n", p);
	}

	int i = 0;
	while (MAP(i))
	{
		if (!( MAP(i) < p && p < MAP(i) + CHUNK_SIZE )) {
			i += 1;
		}
		else
			break;
	}
	if (MAP(i) == 0) {
		SPRINTF("not free %p %p %p\n", MAP(i), p, MAP(i) + CHUNK_SIZE);
		return ;
	}

	newp = p - sizeof(struct binaryheap);
	SPRINTF("free %p [%p], %d\n", p, newp, TOBH((newp)).size);

	TOBH(newp).is_free = 1;

	if (TOBH(newp).size >= CHUNK_SIZE) {
		munmap(newp, TOBH(newp).size);
		return ;
	}
	if (NEXTBH(newp) < TOBH(newp).parent + CHUNK_SIZE && IS_FREE(NEXTBH(newp)) &&
		(TOBH(NEXTBH(newp)).mult == TOBH(newp).mult))
	{
		TOBH(newp) = (struct binaryheap){
			TOBH(newp).size, TOBH(newp).mult * 2, 1, TOBH(newp).parent
		};
		// free(newp + sizeof(struct binaryheap));
	}
	if (PREVBH(newp) > TOBH(newp).parent && IS_FREE(PREVBH(newp)) &&
		(TOBH(PREVBH(newp)).mult == TOBH(newp).mult))
	{
		TOBH(PREVBH(newp)) = (struct binaryheap){
			TOBH(PREVBH(newp)).size, TOBH(PREVBH(newp)).mult * 2, 1,
			TOBH(PREVBH(newp)).parent
		};
		// free(PREVBH(newp) + sizeof(struct binaryheap));
	}

	// show_alloc_mem();
}

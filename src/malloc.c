#include <malloc.h>

void	init(void)
{
	// signal(SIGSEGV, sighandler);
	ft_malloc.debug_fd = open("/Users/adebray/malloc/log", O_CREAT | O_TRUNC | O_WRONLY, 0744);

	ft_malloc.global_map = MMAP(INIT_SIZE);
	SPRINTF("my malloc init %p %d (%lu)\n", ft_malloc.global_map, INIT_SIZE, INIT_SIZE / sizeof(void *));
	SPRINTF("~~~ %s ~~~\n", getprogname());
	SPRINTF("main %d | chunk %d\n", INIT_SIZE, CHUNK_SIZE);
	// SPRINTF("sizeof binaryheap %zu\n", sizeof(struct binaryheap));
	SPRINTF("thread %p\n", (void*)pthread_self());
	SPRINTF("main map %p -> %p\n", ft_malloc.global_map, ft_malloc.global_map + INIT_SIZE);

	MAP(0) = MMAP(CHUNK_SIZE);
	if (MAP(0) == MAP_FAILED) {
		SPRINTF("MAP FAILED\n");
		exit(-1);
	}
	SPRINTF("new_map %p -> %p\n", MAP(0), MAP(0) + CHUNK_SIZE);
	// TOBH(MAP(0)) = (struct binaryheap){ CHUNK_SIZE, CHUNK_SIZE, 1, MAP(0) };

	// last_hand_cache(MAP(0).map, 0);
	ft_malloc.global_cache = MAP(0);
	ft_malloc.nb_fields = 0;
}

void *malloc(size_t size)
{
	if (!ft_malloc.debug_fd)
		init();

	// if (size == 666)
	// 	show_alloc_mem();

	SPRINTF("malloc: %zu\n", size);
	if (ft_malloc.global_cache + size - CHUNK_SIZE > MAP(ft_malloc.nb_fields))
	{
		ft_malloc.nb_fields += 1;
		MAP(ft_malloc.nb_fields) = MMAP(CHUNK_SIZE);
		if (MAP(ft_malloc.nb_fields) == MAP_FAILED) {
			SPRINTF("MAP FAILED\n");
			exit(-1);
		}
		SPRINTF("new_map %p -> %p\n", MAP(ft_malloc.nb_fields), MAP(ft_malloc.nb_fields) + CHUNK_SIZE);
		ft_malloc.global_cache = MAP(ft_malloc.nb_fields);
	}

	void *ptr = ft_malloc.global_cache;
	ft_malloc.global_cache += size;
	return (ptr);
}

void free(void *p)
{
	if (p == 0 || (long)p & 0x700000000000) {
		SPRINTF("not free @ %p\n", p);
		return ;
	}

	SPRINTF("FREE %p\n", p);
}

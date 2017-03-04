#include <malloc.h>

void sighandler(int sig)
{
	(void)sig;
	dprintf(2, "Signal\n");
}

void debug()
{
	int i = 0;
	while (i < INIT_SIZE) {
		if (MAP(i).self != 0)
			SPRINTF("%d: %p\n", i, MAP(i).self)
		i += 1;
	}
}

void	init(void)
{
	signal(SIGSEGV, sighandler);
	ft_malloc.debug_fd = open("/Users/adebray/malloc/log", O_CREAT | O_TRUNC | O_WRONLY, 0744);

	ft_malloc.global_map = MMAP(INIT_SIZE);

	// int i = 0;
	// while (i < INIT_SIZE)
	// {
	// 	((char *)ft_malloc.global_map)[i] = 0;
	// 	i += 1;
	// }
	SPRINTF("my malloc init %p %d (%lu)\n", ft_malloc.global_map, INIT_SIZE, INIT_SIZE / sizeof(void *));
	SPRINTF("~~~ %s ~~~\n", getprogname());
	SPRINTF("main %d | chunk %d\n", INIT_SIZE, CHUNK_SIZE);
	// SPRINTF("sizeof binaryheap %zu\n", sizeof(struct binaryheap));
	SPRINTF("thread %p\n", (void*)pthread_self());
	SPRINTF("main map %p -> %p\n", ft_malloc.global_map, ft_malloc.global_map + INIT_SIZE);

	void *p = MMAP(CHUNK_SIZE);
	MAP(0) = (struct s_ref){ .self = p, .mmap = p };
	if (p == MAP_FAILED) {
		SPRINTF("MAP FAILED\n");
		exit(-1);
	}
	SPRINTF("new_map %p -> %p\n", MAP(0).self, MAP(0).self + CHUNK_SIZE);
	// TOBH(MAP(0)) = (struct binaryheap){ CHUNK_SIZE, CHUNK_SIZE, 1, MAP(0) };

	// last_hand_cache(MAP(0).map, 0);
	ft_malloc.global_cache = p;
	ft_malloc.nb_fields = 0;
}

void *malloc(size_t size)
{
	if (!ft_malloc.debug_fd)
		init();

	SPRINTF("malloc: %zu\n", size);
	void *ptr = ft_malloc.global_cache;

	if (size == 666) {
		debug();
		SPRINTF("%d\n", ft_malloc.nbz)
		// show_alloc_mem();
	}

	if (ptr + size > MAP(ft_malloc.nb_fields).mmap + CHUNK_SIZE) {
		ft_malloc.nb_fields += 1;
		void *p = MMAP(CHUNK_SIZE);
		MAP(ft_malloc.nb_fields) = (struct s_ref){ .self = p, .mmap = p };
		if (MAP(ft_malloc.nb_fields).self == MAP_FAILED) {
			SPRINTF("MAP FAILED\n");
			exit(-1);
		}
		SPRINTF("new_map %p -> %p\n", MAP(ft_malloc.nb_fields).self, MAP(ft_malloc.nb_fields).self + CHUNK_SIZE);
		ft_malloc.global_cache = MAP(ft_malloc.nb_fields).self;
		return ft_malloc.global_cache;
	}


	if (size < TINY)
		ft_malloc.global_cache += TINY;
	else if (size < SMALL) {
		// ft_malloc.nb_fields += 1;
		// MAP(ft_malloc.nb_fields) = (struct s_ref){ .self = ptr, .mmap = MAP(ft_malloc.nb_fields - 1).mmap };

		ft_malloc.global_cache += size;
	}
	else {
		void *p = MMAP(size);
		return p;
	}

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

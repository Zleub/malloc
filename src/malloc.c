#include <malloc.h>

// void debug()
// {
// 	int i = 0;
// 	void *last = 0;
// 	while (MAP(i).self != 0) {
// 		if (last)
// 			SPRINTF("%-8ld", MAP(i).self - last)
// 		else
// 			SPRINTF("XXXXXXXX")
// 		SPRINTF("%4d: %p [%p]\n", i, MAP(i).self, MAP(i).mmap)
// 		last = MAP(i).self;
// 		i += 1;
// 	}
// 	SPRINTF("\n")
// 	SPRINTF("--  --  --  --  --  --\n")
// 	SPRINTF("\n")
// 	i = 0;
// 	while (FREE(i).self != 0) {
// 		SPRINTF("%12d: %p [%p]\n", i, FREE(i).self, FREE(i).mmap)
// 		last = FREE(i).self;
// 		i += 1;
// 	}
// }

void	init(void)
{
	ft_malloc.debug_fd = open("/Users/adebray/malloc/log", O_CREAT | O_TRUNC | O_WRONLY, 0744);

	ft_malloc.global_map = MMAP(INIT_SIZE);
	ft_malloc.free_map = MMAP(INIT_SIZE);

	SPRINTF("my malloc init %p %d (%lu)\n", ft_malloc.global_map, INIT_SIZE, INIT_SIZE / sizeof(struct s_ref));
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

	ft_malloc.global_cache = p;
	ft_malloc.map_fields = 0;
	ft_malloc.free_fields = 0;
}

void *malloc(size_t size)
{
	void	*ptr;

	if (!ft_malloc.global_map)
		init();

	SPRINTF("malloc\n")
	ptr = ft_malloc.global_cache;
	if (ptr + size > MAP(ft_malloc.map_fields).mmap + CHUNK_SIZE) {
		ft_malloc.map_fields += 1;
		void *p = MMAP(CHUNK_SIZE);
		MAP(ft_malloc.map_fields) = (struct s_ref){ .self = p, .mmap = 0x0 };
		if (MAP(ft_malloc.map_fields).self == MAP_FAILED) {
			return (NULL);
		}
		ft_malloc.global_cache = MAP(ft_malloc.map_fields).self;
		return ft_malloc.global_cache;
	}

	if (ft_malloc.free_fields) {
		int i = 0;
		while (FREE(i).self != 0) {
			int j = 0;
			while (MAP(j).self != 0) {
				if (MAP(j).self == FREE(i).self && MAP(j + 1).self - MAP(j).self != 0 )
				{
					if (size <= (size_t)(MAP(j + 1).self - MAP(j).self))
					{
						FREE(i) = (struct s_ref){ .self = 0x0, .mmap = 0x0 };
						ft_malloc.free_fields -= 1;
						return (MAP(j).self);
					}
				}
				j += 1;
			}
			i += 1;
		}
	}

	if (size <= TINY)
		ft_malloc.global_cache += TINY;
	else if (size <= SMALL)
		ft_malloc.global_cache += SMALL;
	else {
		void *p = MMAP(size);
		return p;
	}

	ft_malloc.map_fields += 1;
	MAP(ft_malloc.map_fields) = (struct s_ref){ .self = ptr, .mmap = MAP(ft_malloc.map_fields - 1).mmap };
	return (ptr);
}

void free(void *p)
{
	if (p == 0 || (long)p & 0x700000000000) {
		return ;
	}
	size_t i = 0;
	while (i < ft_malloc.free_fields)
	{
		if (FREE(i).self == 0) {
			FREE(i) = (struct s_ref){ .self = p, .mmap = 0x0 };
			ft_malloc.free_fields += 1;
			return ;
		}
		i += 1;
	}
	FREE(ft_malloc.free_fields) = (struct s_ref){ .self = p, .mmap = 0x0 };
	ft_malloc.free_fields += 1;
}

void *realloc(void *ptr, size_t size)
{
	void *dest = malloc(size);
	ft_memcpy(dest, ptr, size);
	free(ptr);
	return dest;
}

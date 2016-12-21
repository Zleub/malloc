#include <malloc.h>

void debug(size_t size) {
	SPRINTF("size: %zu\n", size);
	SPRINTF("getpagesize: %d\n", getpagesize());

	int ressources[9] = {
		RLIMIT_CORE,
		RLIMIT_CPU,
		RLIMIT_DATA,
		RLIMIT_FSIZE,
		RLIMIT_MEMLOCK,
		RLIMIT_NOFILE,
		RLIMIT_NPROC,
		RLIMIT_RSS,
		RLIMIT_STACK
	};

	char *ressources_strings[9] = {
		"RLIMIT_CORE",
		"RLIMIT_CPU",
		"RLIMIT_DATA",
		"RLIMIT_FSIZE",
		"RLIMIT_MEMLOCK",
		"RLIMIT_NOFILE",
		"RLIMIT_NPROC",
		"RLIMIT_RSS",
		"RLIMIT_STACK"
	};

	int i = 0;
	while (i < 9)
	{
		struct rlimit l;
		int resource = ressources[i];
		ft_bzero(&l, sizeof(struct rlimit));
		int rlimit = getrlimit(resource, &l);

		SPRINTF("%d: %s\n", resource, ressources_strings[i]);
		SPRINTF("\trlimit return: %d\n", rlimit);
		SPRINTF("\trlim_cur %llu | rlim_max %llu\n", l.rlim_cur, l.rlim_max);
		i += 1;
	}
}

# define TOBH(x) (*(struct binaryheap *)x)

struct binaryheap
{
	short	size;
	short	mult;
	int		is_free;
};

void print_from_pointer(void *p) {
	struct binaryheap *dt;

	dt = p;
	SPRINTF("%8d [%6d] @ %p [%s]\n", dt[0].size, dt[0].mult, p, dt[0].is_free ? "FREE" : "OCCUPIED");
}

void show_alloc_mem(void *p) {
	int i = 0;
	while (i < getpagesize() * 10) {
		print_from_pointer(p + i);
		i += TOBH((p + i)).mult;
	}
}

void *malloc(size_t size) {
	size_t page_size = getpagesize();

	static void *oldp;
	void *p;

	p = NULL;
	if (size > page_size)
		p = mmap(0, size, PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	else {
		if (oldp == 0) {
			oldp = mmap(0, page_size * 10, PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
			TOBH(oldp) = (struct binaryheap){ size, (page_size * 10) / 2, 0 };
			TOBH((oldp + page_size * 10 / 2)) = (struct binaryheap){ 0, (page_size * 10) / 2, 1 };

			SPRINTF("first allocation\n");
			p = oldp + sizeof(struct binaryheap);
		}
		else {
			void *newp = oldp + TOBH(oldp).mult;

			if ( TOBH(newp).is_free == 1 && (short)size < TOBH(newp).mult ) {
				TOBH(newp) = (struct binaryheap){ size, TOBH(newp).mult, 0 };
				p = newp + sizeof(struct binaryheap);
			}
			else if (TOBH(oldp).size < TOBH(oldp).mult / 2 && (short)size < TOBH(oldp).mult / 2) {

				TOBH((oldp + TOBH(oldp).mult / 2)) = (struct binaryheap){ size, TOBH(oldp).mult / 2, 0 };
				TOBH(oldp) = (struct binaryheap){ TOBH(oldp).size, TOBH(oldp).mult / 2, 0 };

				p = (oldp + TOBH(oldp).mult / 2) + sizeof(struct binaryheap);
			}
			else {
				void *newp = oldp;
				while (!(TOBH(newp).size < TOBH(newp).mult / 2 && (short)size < TOBH(newp).mult / 2))
					newp = newp + TOBH(newp).mult;

				TOBH((newp + TOBH(newp).mult / 2)) = (struct binaryheap){ size, TOBH(newp).mult / 2, 0 };
				TOBH(newp) = (struct binaryheap){ TOBH(newp).size, TOBH(newp).mult / 2, 0 };

				p = (newp + TOBH(newp).mult / 2) + sizeof(struct binaryheap);
			}
			// show_alloc_mem(oldp);
			// if ( TOBH(oldp).is_free == FALSE && TOBH(oldp).size < TOBH(oldp).mult && (short)size < TOBH(oldp).mult) {
			// 	void *newp = oldp + TOBH(oldp).mult;

			// 	TOBH(oldp).mult = TOBH(oldp).mult / 2;
			// 	TOBH(newp) = (struct binaryheap){ size, TOBH(oldp).mult, 0 };
			// 	TOBH((newp + TOBH(oldp).mult)) = (struct binaryheap){ 0, TOBH(oldp).mult, 1 };

			// 	p = newp + sizeof(struct binaryheap);
			// }
			// else {
			// 	void *newp = oldp + TOBH(oldp).mult * 2;

			// 	while (!(TOBH(newp).is_free == FALSE && TOBH(newp).size < TOBH(newp).mult)) {
			// 		newp = newp + TOBH(newp).mult* 2;
			// 	}

			// 	TOBH(newp).mult = TOBH(newp).mult / 2;

			// 	newp = newp + TOBH(newp).mult;
			// 	TOBH(newp) = (struct binaryheap){ size, TOBH(newp).mult, 0 };

			// 	p = newp + sizeof(struct binaryheap);
			// }

		}

		show_alloc_mem(oldp);
	}
	if (p == MAP_FAILED)
		SPRINTF("errno: %d: %s\n", errno, strerror(errno));

	SPRINTF("-> %p\n", p);
	return (p);
}


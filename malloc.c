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
		SPRINTF("\trlim_cur %lu | rlim_max %lu\n", l.rlim_cur, l.rlim_max);
		i += 1;
	}
}

# define TOBH(x) (*(struct binaryheap *)x)

void print_from_pointer(void *p) {
	struct binaryheap *dt;

	dt = p;
	SPRINTF("%8d [%6d] @ %p [%s]\n", dt[0].size, dt[0].mult, p, dt[0].is_free ? "FREE" : "OCCUPIED");
}

static void *oldp;
void show_alloc_mem() {
	int i = 0;

	if (!oldp)
		return ;

	while (i < getpagesize() * 10) {
		print_from_pointer(oldp + i);
		i += TOBH((oldp + i)).mult;
	}
}

void *malloc(size_t size) {
	size_t page_size = getpagesize();

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
			void *newp = oldp;
			int mark = 0;
			while (!(
				( TOBH(newp).is_free == 1 && (int)(size + sizeof(struct binaryheap)) < TOBH(newp).mult && (mark = 1)) ||
				( (int)(TOBH(newp).size + sizeof(struct binaryheap)) < TOBH(newp).mult / 2 && (int)(size + sizeof(struct binaryheap)) < TOBH(newp).mult / 2 && (mark = 2) )
			)) {
				if (newp == oldp + page_size * 10)
					return  (NULL);
				newp = newp + TOBH(newp).mult;
			}

			if (mark == 1) {
				TOBH(newp) = (struct binaryheap){ size, TOBH(newp).mult, 0 };
				return newp + sizeof(struct binaryheap);
			}

				// SPRINTF("----BEFORE--------\n");
				// print_from_pointer(newp + TOBH(newp).mult / 2);
				// SPRINTF("-----------------\n");
			TOBH((newp + TOBH(newp).mult / 2)) = (struct binaryheap){ size, TOBH(newp).mult / 2, 0 };
				// print_from_pointer(newp + TOBH(newp).mult / 2);
				// SPRINTF("-----AFTER-------\n");
			TOBH(newp) = (struct binaryheap){ TOBH(newp).size, TOBH(newp).mult / 2, TOBH(newp).is_free };

			p = (newp + TOBH(newp).mult) + sizeof(struct binaryheap);
		}
	}
	if (p == MAP_FAILED)
		SPRINTF("errno: %d: %s\n", errno, strerror(errno));

	SPRINTF("-> %p\n", p);
	return (p);
}

void free(void *p) {
	if (p == 0)
		return ;
	TOBH((p - sizeof(struct binaryheap))).is_free = 1;
}

#include <unistd.h>

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);

#include <libft.h>

#define PUTNBR(x) ft_putnbr(x) ;
#define PUTNBRSEP(x, y) ft_putnbr(x) ; ft_putstr(y) ;
#define PUTNBRPRE(x, y) ft_putstr(x) ; ft_putnbr(y) ;
#define PUTNBRENDL(x) ft_putnbr(x) ; ft_putendl("") ;

     #include <sys/types.h>
     #include <sys/time.h>
     #include <sys/resource.h>

#include <stdio.h>
#include <sys/mman.h>

#define SPRINTF(args...) { char str[1024] = {0}; sprintf(str, args); ft_putendl(str); }

void *test(size_t size) {
	PUTNBRPRE("size ", size);
	ft_putendl("");
	PUTNBRPRE("getpagesize ", getpagesize());
	ft_putendl("");

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

    void *p = mmap(0, 0, 0, 0, 0, 0);

    SPRINTF("%p\n", p);

	return (NULL);
}

int main(void) {
	void *p = test(4);

	PUTNBR((int)p);
	return (0);
}

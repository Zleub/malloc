#include <unistd.h>

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);

#include <libft.h>

#define PUTNBR(x) ft_putnbr(x) ; ft_putendl("") ;

void *malloc(size_t size) {
	PUTNBR(size);
	PUTNBR(getpagesize());

	return (NULL);
}

int main(void) {
	void *p = malloc(4);

	PUTNBR((int)p);
	return (0);
}

#include <stdlib.h>
#include <malloc.h>

int main(void) {

	SPRINTF("%zu\n", sizeof(size_t));

	int i = 0;
	while (i < 10) {
		char test[] = "arno";
		int i = rand() % 500;
		SPRINTF("allocate %d\n", i);
		void *p = malloc( i );

		strcpy(p, test);
	}
	return (0);
}

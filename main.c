#include <malloc.h>

// int main(void) {

// 	SPRINTF("%zu\n", sizeof(struct binaryheap));
// 	int i = 0;
// 	while (i < 10) {
// 		char test[] = "arnoarnoarnoarnoarnoarnoarnoarno";
// 		int i = rand() % 10 + 5;
// 		SPRINTF("allocate %d\n", i);
// 		void *p = malloc( i );

// 		strncpy(p, test, i - 1);
// 		show_alloc_mem();
// 	}
// 	return (0);
// }

#define TESTSIZE 50000

void show_alloc_mem();
int main(void) {

	void *array[TESTSIZE + 1] = {0};

	int i = 1;
	int j = 0;

	// debug();

	while (i < TESTSIZE) {

		// if ((i + 1) % 6 == 0) {
		// 	while (rand() % TESTSIZE / 20) {
		// 		int j = rand() % i;
		// 		free(array[j]);
		// 		array[j] = 0;
		// 		// j += 1;
		// 	}
		// }
		// else {
			int j = rand() % 100 + 5;
			void *p = malloc( j );
			// SPRINTF("allocate %d @ %p\n", j, p ? p - sizeof(struct binaryheap) : p );
			array[i] = p;
			strncpy(p, (char*)&main, j);
		// }

		// #ifdef FT_MALLOC
		// 	SPRINTF("----------------------------------------------\n");
		// 	show_alloc_mem();
		// #endif
		i += 1;
	}
	SPRINTF("ENDTEST\n");
}

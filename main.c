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

#define TESTSIZE 100

void show_alloc_mem();
int main(void) {

	void *array[100] ={0};

	int i = 1;
	int j = 0;

	// debug();

	while (i < TESTSIZE) {
		// if ((i + 1) % 4 == 0) {
		// 	int j = rand() % 50 + 5;
		// 	SPRINTF("allocate %d\n", j);
		// 	void *p = malloc( j );
		// 	array[i] = p;
		// 	strcpy(p, "test");
		// }
		// else
		if ((i + 1) % 3 == 0) {
			int j = rand() % i;
			SPRINTF("free: %d %p\n", j, array[j])
			free(array[j]);
		}
		else {
			int j = rand() % 5000 + 5;
			SPRINTF("allocate %d\n", j);
			void *p = malloc( j );
			array[i] = p;
			strcpy(p, "test");
		}

		show_alloc_mem();
		i += 1;
	}
}

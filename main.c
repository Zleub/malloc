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

#define TESTSIZE 100000

int global_call_cmp;

void show_alloc_mem();
int main(void) {

	void *array[TESTSIZE + 1] = {0};

	int i = 1;
	int j = 0;
	int cmp = 0;
	global_call_cmp = 0;

	// debug();

	while (i < TESTSIZE) {

		// if ((i + 1) % 6 == 0) {
		// 	while (rand() % TESTSIZE / 200) {
		// 		int j = rand() % i;
		// 		free(array[j]);
		// 		array[j] = 0;
		// 		// j += 1;
		// 	}
		// }
		// else {
			int j = rand() % (16 * 16 * 16 * 16) + 5;
			void *p = malloc( j );
			cmp += j;
			if (p == 0)
				SPRINTF("0x0\n");
			#ifdef DEBUG
			SPRINTF("allocate %d @ %p\n", j, p ? p - sizeof(struct binaryheap) : p );
			#endif
			array[i] = p;
			strncpy(p, (char*)&main, j);
		// }

		#ifdef DEBUG
			SPRINTF("----------------------------------------------\n");
			SPRINTF("%d\n", global_call_cmp);
			show_alloc_mem();
		#endif

		i += 1;
		global_call_cmp += 1;
	}
	SPRINTF("ENDTEST %d\n", cmp);
}

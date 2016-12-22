#include <malloc.h>

// int main(void) {

// 	SPRINTF("%zu\n", sizeof(size_t));
// 	int i = 0;
// 	while (i < 10) {
// 		char test[] = "arno";
// 		int i = rand() % 500 + 5;
// 		SPRINTF("allocate %d\n", i);
// 		void *p = malloc( i );

// 		strcpy(p, test);
// 	}
// 	return (0);
// }

#define TESTSIZE 100

int main(void) {

	int i = 0;
	int j = 0;
	while (i < TESTSIZE) {
		if (i % 3 == 0)
			j = 10;
		else
			j = rand() % 5000 + 5 ;

		SPRINTF("allocate %d\n", j);
		void *p = malloc( j );
		strcpy(p, "test");
		i += 1;
	}
}

#define SUPPORT_ZONES 0

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

#define TESTSIZE 10000

int global_call_cmp;

void show_alloc_mem();

char *str = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\
Cras at euismod urna. Vestibulum porta ultrices ex, a lacinia lorem imperdiet ac.\
Morbi et dui neque. Morbi elementum eget eros non scelerisque.\
Vivamus varius, ipsum eget vulputate euismod, nisi ex venenatis lorem,\
ut laoreet dui velit quis leo. Aenean mattis venenatis lorem vel finibus.\
Donec semper varius nisi et aliquet.\
Cras et mauris ut eros aliquam efficitur a vitae ante.\
Proin sed velit non nibh varius pellentesque.\
Vestibulum viverra urna a mi sagittis, ac tristique augue efficitur.\
Morbi sit amet eleifend nulla, in dapibus nisl.\
Praesent elementum consequat ultrices.\
Mauris lobortis tellus nec ipsum ultricies pharetra.\
Class aptent taciti sociosqu ad litora torquent per conubia nostra,\
per inceptos himenaeos. Donec nec mattis justo.\
Fusce auctor vehicula mi. Donec molestie tincidunt dolor,\
ac gravida urna auctor ac. Vestibulum sagittis, ante vel ullamcorper bibendum,\
enim erat rhoncus urna, nec viverra ipsum sem non velit. Ut eros arcu posuere.";

int main(void) {

	void *array[TESTSIZE + 1] = {0};

	int i = 1;
	int j = 0;
	int cmp = 0;
	global_call_cmp = 0;

	// debug();
	// SPRINTF("BEGINTEST\n")
	while (i < TESTSIZE) {

		int j = rand() % (16 * 16) + 5;
		void *p = malloc( j );
		bzero(p, j);
		cmp += j;
		if (p == 0)
			SPRINTF("0x0\n");

		// SPRINTF("allocate %d @ %p\n", j, p ? p - sizeof(struct binaryheap) : p );

		array[i] = p;
		strncpy(p, str, j - 1);
		if (strlen(p) != j - 1)
			SPRINTF("I GOT AN ISSUE : %lu vs %d\n", strlen(p), j);

		// SPRINTF("----------------------------------------------\n");
		// SPRINTF("%d\n", global_call_cmp);
		// show_alloc_mem();

		i += 1;
		global_call_cmp += 1;
	}
	SPRINTF("ENDTEST %d\n", cmp);
}

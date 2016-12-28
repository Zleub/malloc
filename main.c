#undef SUPPORT_ZONES

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

#define TESTSIZE 1000

int global_call_cmp;

void show_alloc_mem();

char *str = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\
Cras at euismod urna. Vdawestibulum porta ultrices ex, a lacinia lorem imperdiet ac.\
Morbi et dui neque. Moawddaasum eget vulputate euismod, nisi ex venenatis lorem,\
ut laoreet dui velit quiswd dleo. Aeneanaddaad mattis venenatis lorem vel finibus.\
Donec semper variuwddas nisisda ddaawetad aawdwwawaadwddadaddliquet.\
Cras et mauris ut eros wdaldiddasadawawdwawdquam effdicitur a vitae ante.\
Proin sed velit non nidwawddbh varius pellentesque.\
Vestibulum viverra urna a awdmi sagittis, ac tristique augue efficitur.\
Morbi sit amet ewdaawdleifend nulla, in dapibus nisl.\
Praesent elementawum consequat ultrices.\
Mauris lobortis datellus nec ipsum ultricies pharetra.\
Class aptent taciti sawoawdciosqu ad litora torquent per conubia nostra,\
per inceptos himenaeos. Donec nec mattis justo.\
Fusce auctor vehicula mi. Donec molestie tincidunt dolor,\
ac gravida urna auctor ac. Vestibulum sagittis, ante vel ullamcorper bibendum,\
enim erat rhoncus urna, nec viverra ipsum sem non velit. Ut eros arcu posuere.";

int main(void) {

	void *array[TESTSIZE + 1] = {0};

	int i = 1;
	int cmp = 0;
	global_call_cmp = 0;

	// debug();
	// SPRINTF("BEGINTEST\n")
	while (i < TESTSIZE) {

		int j = 1024; //rand() % (16 * 16) + 5;
		void *p = malloc( j );
		bzero(p, j);
		cmp += j;
		if (p == 0)
			SPRINTF("0x0\n");

		// SPRINTF("allocate %d @ %p\n", j, p ? p - sizeof(struct binaryheap) : p );

		array[i] = p;
		strncpy(p, str, j - 1);
		if (strlen(p) != (unsigned long)j - 1)
			SPRINTF("I GOT AN ISSUE : %lu vs %d\n", strlen(p), j);

		// SPRINTF("----------------------------------------------\n");
		// SPRINTF("%d\n", global_call_cmp);
		// show_alloc_mem();

		i += 1;
		global_call_cmp += 1;
	}
	SPRINTF("ENDTEST %p %d\n", array[i], cmp);
}

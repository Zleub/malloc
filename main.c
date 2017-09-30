//           `--::-.`
//       ./shddddddddhs+.
//     :yddddddddddddddddy:
//   `sdddddddddddddddddddds`
//  /ddddy:oddddddddds:sddddd/   @By: Debray Arnaud <adebray> - adebray@student.42.fr
//  sdddddddddddddddddddddddds   @Last modified by: adebray
//  sdddddddddddddddddddddddds
//  :ddddddddddhyyddddddddddd:   @Created: 2017-08-12T09:29:05+02:00
//   odddddddd/`:-`sdddddddds    @Modified: 2017-09-28T20:22:32+02:00
//    +ddddddh`+dh +dddddddo
//     -sdddddh///sdddddds-
//       .+ydddddddddhs/.
//           .-::::-`

#undef SUPPORT_ZONES

#include <malloc.h>

// int main(void) {

// 	dprintf(2, "%zu\n", sizeof(struct binaryheap));
// 	int i = 0;
// 	while (i < 10) {
// 		char test[] = "arnoarnoarnoarnoarnoarnoarnoarno";
// 		int i = rand() % 10 + 5;
// 		dprintf(2, "allocate %d\n", i);
// 		void *p = malloc( i );

// 		strncpy(p, test, i - 1);
// 		show_alloc_mem();
// 	}
// 	return (0);
// }

#define TESTSIZE 64 // 4096 * 8

int global_call_cmp;

void show_alloc_mem();
const char *getprogname(void);

char *str = "dawdawdadwfawdsaLorem ipsum dolor sit amet, consectetur adipiscing elit. Nam mattis risus sed hendrerit ornare. Suspendisse accumsan lectus a nisi aliquam molestie. Suspendisse pharetra sagittis tortor vel lacinia. Quisque gravida mi sit amet elit fermentum eleifend sed nec lorem. Donec varius porttitor ex, a pharetra eros tempor vitae. Donec dignissim volutpat gravida. Suspendisse auctor pharetra dolor eget ullamcorper. Aenean ultricies magna ut pretium faucibus.\
Proin blandit euismod accumsan. Curabitur tempus non massa vel tempus. Nam ante arcu, bibendum nec enim non, varius dapibus sapien. Cras nec quam pharetra, tincidunt justo quis, gravida neque. Nullam hendrerit lacus ut dolor semper, at imperdiet lorem malesuada. Vivamus rhoncus dui vel nunc commodo, non condimentum ante consequat. Phasellus non justo ornare, rutrum turpis id, posuere eros. Morbi ac ante magna.\
Integer et diam iaculis, semper nunc vitae, ultrices elit. Nulla eget purus congue quam mollis facilisis ornare eu ligula. Ut eleifend posuere leo vulputate commodo. Sed interdum non nulla sed lacinia. Ut rutrum sapien ut eleifend fermentum. Nulla facilisi. Aenean consequat, nunc eu convallis semper, metus dolor tempus nulla, non placerat ligula libero eget eros. Sed vel rutrum metus. Suspendisse ac erat lacinia purus commodo auctor non tincidunt ipsum.\
Morbi tincidunt metus odio, sed sagittis est porttitor sit amet. Donec in gravida nunc. Integer fermentum, mi id pulvinar vehicula, dolor nisi tincidunt felis, cursus tristique justo sem id ipsum. Maecenas nibh orci, vehicula quis faucibus quis, rhoncus sed metus. Vestibulum congue, dui nec condimentum finibus, tortor mi gravida risus, pulvinar placerat est ante eu odio. In et purus nec nulla aliquam maximus vel vitae urna. Donec a mi pretium, egestas ex at, faucibus magna.\
Sed felis risus, luctus in iaculis ac, mattis quis ante. Ut placerat, tellus a porttitor laoreet, augue tortor cursus tellus, quis gravida risus odio vitae mi. Etiam luctus accumsan neque, eu maximus metus condimentum eu. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Sed aliquam convallis nisl at scelerisque. Proin vitae ex et urna finibus aliquam eu id turpis. Suspendisse pharetra velit eget ornare pharetra. Praesent vestibulum sem at libero tempus, nec viverra leo posuere. Integer vulputate mollis dolor at dictum. Integer ex arcu, vulputate interdum nulla in, varius vulputate orci. Suspendisse sollicitudin venenatis mi, non accumsan nisl dignissim at. Nam lacus augue, imperdiet eget nisl in, rhoncus efficitur enim. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas ut volutpat neque. Donec posuere nisl et leo ullamcorper vestibulum varius vitae orci.\
Etiam cursus tincidunt turpis, quis finibus felis condimentum at. Phasellus at quam est. Curabitur dictum sapien in iaculis euismod. Curabitur mollis nulla nunc, sit amet euismod libero feugiat id. Morbi et felis non velit tempor egestas ac ornare nisi. Mauris sed nisi eget tellus lobortis vehicula. Vivamus vitae neque dapibus leo imperdiet porta. Cras pellentesque nisi eu tellus vulputate, non euismod sem malesuada. Aliquam bibendum efficitur dui et consectetur. Vivamus egestas maximus porttitor. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc sodales vel ex nec vehicula. Integer tortor lorem, volutpat suscipit sodales id, elementum et mi. Praesent aliquet lectus nunc, sed ullamcorper ex egestas et.\
Aliquam vitae erat arcu. Donec quis vehicula massa, nec tincidunt leo. Donec egestas nunc eget quam scelerisque, quis maximus magna rhoncus. Aenean sodales sem a volutpat dignissim. In ac placerat enim, et vestibulum orci. Ut maximus, leo at consectetur tincidunt, nunc nisi pellentesque diam, at blandit enim lorem et quam. Proin consectetur ligula et dui volutpat finibus. Suspendisse et metus ut tellus consequat ornare vel et est. Sed quis nulla sodales, bibendum eros id, rutrum dui. Proin tellus lorem, condimentum sit amet massa eget, volutpat ultricies leo. Nulla semper, mi non ornare malesuada, ex nunc auctor nulla, a volutpat.";

int main(int ac, char**argv) {

	void *array[TESTSIZE + 1] = {0};

	int i = 1;
	int cmp = 0;
	global_call_cmp = 0;

	// debug();
	// dprintf(2, "BEGINTEST\n")
	(void)ac;
	if (ac < 2) {
		dprintf(2, "Dude\n");
		return (-1);
	}
	while (i < TESTSIZE) {

		int j = atoi(argv[1]); // || rand() % (16 * 16 * 3) + 5;
		void *p = malloc( j );
		if (p == 0) {
			dprintf(2, "main: 0x0\n");
			exit(-1);
		}
		bzero(p, j);
		cmp += j;

		// dprintf(2, "allocate %d @ %p\n", j, p ? p - sizeof(struct binaryheap) : p );

		array[i] = p;
		strncpy(p, str, j - 1);
		if (strlen(p) != (unsigned long)j - 1)
			dprintf(2, "I GOT AN ISSUE : %lu vs %d\n", strlen(p), j);

		// dprintf(2, "----------------------------------------------\n");
		// dprintf(2, "%d\n", global_call_cmp);
		// show_alloc_mem();
		// int index = rand() % i;
		// if (array[index]) {
		// 	free(array[index]);
		// 	array[index] = 0;
		// }

		i += 1;
		global_call_cmp += 1;
	}
	void *p = malloc(666);
	bzero(p, 665);
	strncpy(p, str, 665);

	char str[1024] = {0};
	sprintf(str, "~~~ END %s ~~~\n", argv[0]);

	ft_putstr(str);
}

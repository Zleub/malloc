/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 00:59:41 by adebray           #+#    #+#             */
/*   Updated: 2017/10/04 00:34:05 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <malloc.h>
#include <sys/time.h>

#define TESTSIZE 120

char *g_str = "dawdarem ipsum dolor sit amet,\
consectetur adipNam mattis risus sed hendrerit ornare. \
Suspendisse accumnisi aliquam molestie. Suspendisse\
pharetra sagittilacinia. Quisque gravida mi sit amet elit\
fermentum eleiferem. Donec varius porttitor ex, a pharetra\
eros tempor vitaissim volutpat gravida. Suspendisse auctor \
pharetra dolor egr. Aenean ultricies magna ut pretium faucibus.\
roin blandit euis Curabitur tempus non massa vel tempus. Nam ante\
arcu, bibendum nvarius dapibus sapien. Cras nec quam pharetra,\
tincidunt justo  neque. Nullam hendrerit lacus ut dolor semper, at\
imperdiet lorem vamus rhoncus dui vel nunc commodo, non \
condimentum ante asellus non justo ornare, rutrum turpis id, \
posuere eros. Morgna. Integer et diam iaculis, semper nunc\
vitae, ultrices get purus congue quam mollis facilisis ornare eu\
ligula. Ut eleifeo vulputate commodo. Sed interdum non nulla sed\
lacinia. Ut rutreleifend fermentum. Nulla facilisi. \
Aenean consequat,allis semper, metus dolor tempus nulla, non placerat\
ligula libero egeel rutrum metus. Suspendisse ac erat lacinia purus\
commodo auctor nopsum. Morbi tincidunt metus odio, sed sagittis est\
porttitor sit ameravida nunc. Integer fermentum, mi id pulvinar\
vehicula, dolor n felis, cursus tristique justo sem id ipsum.\
Maecenas nibh orcuis faucibus quis, rhoncus sed metus. Vestibulum\
congue, dui nec cnibus, tortor mi gravida risus, pulvinar placerat\
est ante eu odio.nec nulla aliquam maximus vel vitae urna.\
Donec a mi pretiu at, faucibus magna. Sed felis risus, luctus\
in iaculis ac, mae. Ut placerat, tellus a porttitor laoreet,\
augue tortor cursis gravida risus odio vitae mi.\
Etiam luctus accuu maximus metus condimentum eu.\
Cum sociis natoqut magnis dis parturient montes, nascetur\
ridiculus mus. Sevallis nisl at scelerisque. Proin vitae\
ex et urna finibuid turpis. Suspendisse pharetra velit\
eget ornare phare vestibulum sem at libero tempus,\
nec viverra leo per vulputate mollis dolor at dictum. Integer\
ex arcu, vulputatlla in, varius vulputate orci. Suspendisse\
sollicitudin vene accumsan nisl dignissim at. Nam\
lacus augue, impesl in, rhoncus efficitur enim. Lorem ipsum\
dolor sit amet, cipiscing elit. Maecenas ut volutpat\
neque. Donec posueo ullamcorper vestibulum varius vitae orci.\
Etiam cursus tinc quis finibus felis condimentum at.\
Phasellus at quamur dictum sapien in iaculis euismod. Curabitur\
mollis nulla nuncismod libero feugiat id. Morbi et felis non\
velit tempor eges nisi. Mauris sed nisi eget tellus lobortis\
vehicula. Vivamusdapibus leo imperdiet porta. Cras pellentesque\
nisi eu tellus vueuismod sem malesuada. Aliquam bibendum\
efficitur dui et Vivamus egestas maximus porttitor. Lorem ipsum dolor\
sit amet, consectng elit. Nunc sodales vel ex nec vehicula.\
Integer tortor lo suscipit sodales id, elementum et mi.\
Praesent aliquet sed ullamcorper ex egestas et. Aliquam vitae erat arcu.\
Donec quis vehicu tincidunt leo. Donec egestas nunc eget quam scelerisque,\
quis maximus magnnean sodales sem a volutpat dignissim. In ac placerat\
enim, et vestibulaximus, leo at consectetur tincidunt, nunc nisi\
pellentesque diamenim lorem et quam. Proin consectetur ligula et dui\
volutpat finibus.et metus ut tellus consequat ornare vel et est.\
Sed quis nulla soum eros id, rutrum dui. Proin tellus lorem,\
condimentum sit at, volutpat ultricies leo. Nulla semper, mi non\
ornare malesuada,or nulla, a volutpat.";

void	do_stuff(char *av, int i)
{
	int		j;
	void	*p;
	int		index;
	void	*array[TESTSIZE + 1];

	j = atoi(av);
	p = malloc(j);
	ft_bzero(array, TESTSIZE + 1);
	if (p == 0)
	{
		dprintf(2, "main: 0x0\n");
		exit(-1);
	}
	bzero(p, j);
	array[i] = p;
	strncpy(p, g_str, j - 1);
	if (strlen(p) != (unsigned long)j - 1)
		dprintf(2, "I GOT AN ISSUE : %lu vs %d\n", strlen(p), j);
	index = rand() % i;
	if (array[index])
	{
		free(array[index]);
		array[index] = 0;
	}
}

int		main(int ac, char **argv)
{
	int		i;

	i = 1;
	if (ac < 2)
	{
		dprintf(2, "Dude\n");
		return (-1);
	}
	while (i < TESTSIZE)
	{
		do_stuff(argv[1], i);
		i += 1;
	}
	show_alloc_mem();
}

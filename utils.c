/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 22:49:34 by adebray           #+#    #+#             */
/*   Updated: 2016/12/23 22:35:07 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	print_from_pointer(void *p)
{
	struct binaryheap *dt;

	dt = p;
	SPRINTF("%8d [%6d] @ %p [%s]\n", dt[0].size, dt[0].mult, p,
		dt[0].is_free == 1 ? "FREE" : "OCCUPIED");
}

#define INDEX(x) (((void **)g_oldp)[x])

void	show_alloc_mem(void)
{
	int	i;
	int	j;

	j = 0;
	if (!g_oldp)
		return ;
	while (INDEX(j))
	{
		i = 0;
		SPRINTF("INDEX: %d\n", j);
		while (i < CHUNK_SIZE)
		{
			print_from_pointer(INDEX(j) + i);
			i += TOBH((INDEX(j) + i)).mult;
		}
		j += 1;
	}
}

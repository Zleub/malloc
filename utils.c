/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 22:49:34 by adebray           #+#    #+#             */
/*   Updated: 2016/12/22 22:58:00 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	print_from_pointer(void *p)
{
	struct binaryheap *dt;

	dt = p;
	SPRINTF("%8d [%6d] @ %p [%s]\n", dt[0].size, dt[0].mult, p,
		dt[0].is_free ? "FREE" : "OCCUPIED");
}

void	show_alloc_mem(void)
{
	int	i;

	i = 0;
	if (!g_oldp)
		return ;
	while (i < CHUNK_SIZE)
	{
		print_from_pointer(g_oldp + i);
		i += TOBH((g_oldp + i)).mult;
	}
}

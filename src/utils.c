/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 22:49:34 by adebray           #+#    #+#             */
/*   Updated: 2017/01/13 17:46:16 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	show_alloc_mem(void)
{
	int i;
	int j;
	int chunk_size;

	i = 0;
	while (MAP(i).map)
	{
		j = 0;
		chunk_size = 0;
		SPRINTF("%d: %p [%zu]\n", i, MAP(i).map, MAP(i).remaining);
		while (j < CHUNK_SIZE) {
			if (MAP(i).map + j == last_hand_cache(NULL, 0))
				SPRINTF("C");
			SPRINTF("\t%p %u [%d] %s\n",
				MAP(i).map + j,
				TOBH((MAP(i).map + j)).size,
				TOBH((MAP(i).map + j)).mult,
				TOBH((MAP(i).map + j)).is_free ? "FREE" : "OCCUPIED"
			);
			chunk_size += TOBH((MAP(i).map + j)).mult;
			j += TOBH((MAP(i).map + j)).mult;
		}
		SPRINTF("[ %d ] %s\n", chunk_size, chunk_size == CHUNK_SIZE ? "true" : "false");
		i += 1;
	}
}

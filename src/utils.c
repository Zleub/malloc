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
	size_t i = 0;

	while (i < INIT_SIZE / sizeof(void*))
	{
		if (MAP(i))
			SPRINTF("%p\n", MAP(i));
		i += 1;
	}
}

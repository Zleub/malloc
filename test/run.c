/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 00:58:09 by adebray           #+#    #+#             */
/*   Updated: 2017/10/04 01:40:55 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <libft.h>
#include <malloc.h>

int		main(void)
{
	char	*str;
	char	*s;
	char	*s2;

	str = "adebray\n";
	s = malloc(ft_strlen(str) + 1);
	ft_bzero(s, ft_strlen(str) + 1);
	ft_strcpy(s, str);
	ft_printf(s);
	ft_strcpy(s, "yarbeda\n");
	ft_printf(s);
	ft_strncpy(s, "ade", 3);
	ft_printf(s);
	s2 = realloc(s, 4092);
	ft_printf(s2);
	ft_strncpy(s2, "## <<>> <<>> ##\n", 16);
	ft_printf(s2);
	ft_printf("%s\n", (s == s2) ? "true" : "false" );
	free(s2);
	show_alloc_mem();
	return (0);
}

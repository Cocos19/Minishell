/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:34:08 by mprofett          #+#    #+#             */
/*   Updated: 2022/10/04 15:34:09 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str_to_check;
	unsigned char	char_to_search;

	i = -1;
	str_to_check = (unsigned char *)s;
	char_to_search = c;
	while (++i < n)
		if (*(str_to_check + i) == char_to_search)
			return (str_to_check + i);
	return (NULL);
}

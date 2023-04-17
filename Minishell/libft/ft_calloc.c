/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:48:58 by mprofett          #+#    #+#             */
/*   Updated: 2022/10/04 16:49:00 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	i;
	size_t	memsize;

	memsize = count * size;
	str = malloc(memsize);
	if (!str)
		return (NULL);
	i = -1;
	while (++i < memsize)
		*(str + i) = '\0';
	return (str);
}

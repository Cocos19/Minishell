/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:48:51 by mprofett          #+#    #+#             */
/*   Updated: 2022/10/04 12:48:53 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*newdst;
	const unsigned char	*newsrc;

	if (dst == src || n <= 0)
		return (dst);
	newdst = dst;
	newsrc = src;
	while (n-- > 0)
		*(newdst + n) = *(newsrc + n);
	return (dst);
}

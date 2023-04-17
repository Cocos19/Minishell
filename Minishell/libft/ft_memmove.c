/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:20:53 by mprofett          #+#    #+#             */
/*   Updated: 2022/10/04 13:20:55 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*newdst;
	const unsigned char	*newsrc;
	size_t				i;

	if (dst == src || len <= 0)
		return (dst);
	newdst = dst;
	newsrc = src;
	i = 0;
	if (dst > src)
	{
		while (i++ < len)
			*(newdst + len - i) = *(newsrc + len - i);
		return (dst);
	}
	i = -1;
	while (++i < len)
		newdst[i] = newsrc[i];
	return (dst);
}

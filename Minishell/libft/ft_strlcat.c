/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:03:00 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/19 13:23:54 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	dest_start_len;
	size_t	src_len;

	if (!dst && dstsize == 0)
		return (ft_strlen(src));
	dest_start_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dest_start_len >= dstsize || dstsize <= 0)
		return (dstsize + src_len);
	i = 0;
	while (src[i] && i < dstsize - dest_start_len - 1)
	{
		dst[i + dest_start_len] = src[i];
		i++;
	}
	dst[i + dest_start_len] = '\0';
	return (dest_start_len + src_len);
}

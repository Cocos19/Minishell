/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:54:05 by mprofett          #+#    #+#             */
/*   Updated: 2022/10/04 15:54:07 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = (char *)haystack;
	if (ft_strlen(needle) == 0)
		return (result);
	if (len == 0)
		return (NULL);
	while (haystack[i] && (ft_strlen(needle) + i) <= len)
	{
		j = 0;
		while (haystack[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return (&result[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

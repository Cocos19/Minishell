/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:14:02 by mprofett          #+#    #+#             */
/*   Updated: 2022/10/04 15:14:04 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str_to_check;
	size_t	str_len;

	str_len = ft_strlen(s);
	str_to_check = (char *)s;
	if (*(str_to_check + str_len) == 0 && c == 0)
		return (str_to_check + str_len);
	while (str_len > 0)
		if (*(str_to_check + --str_len) == (char)c)
			return (str_to_check + str_len);
	return (NULL);
}

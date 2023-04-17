/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:43:31 by mprofett          #+#    #+#             */
/*   Updated: 2022/10/04 14:43:33 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	char	*str_to_check;

	str_to_check = (char *)s;
	while (*(str_to_check))
	{
		if (*str_to_check == (char)c)
			return (str_to_check);
		str_to_check++;
	}
	if (*str_to_check == 0 && c == 0)
		return (str_to_check);
	return (NULL);
}

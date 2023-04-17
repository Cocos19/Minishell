/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:48:57 by mprofett          #+#    #+#             */
/*   Updated: 2023/03/30 14:09:20 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	int_fast16_t	i;

	if (!*s1 && !*s2)
		return (0);
	if (!*s2)
		return (1);
	i = -1;
	while (*(s1 + ++i) && (unsigned char)*(s1 + i) == (unsigned char)*(s2 + i))
	{
		if (!*(s1 + i) && !*(s2 + i))
			return (0);
		if (!*(s1 + i))
			return (-1);
		if (!*(s2 + i))
			return (1);
	}
	return ((unsigned char)*(s1 + i) - (unsigned char)*(s2 + i));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:22:29 by mprofett          #+#    #+#             */
/*   Updated: 2022/10/04 15:22:31 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0 || (!s1[i] && !s2[i]))
		return (0);
	if (!s2[i])
		return (1);
	while (s1[i] && (unsigned char)s1[i] == (unsigned char)s2[i] && i < n)
	{
		i++;
		if ((!s1[i] && !s2[i]) || i == n)
			return (0);
		if (!s1[i])
			return (-1);
		if (!s2[i])
			return (1);
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

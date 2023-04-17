/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_delimited.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:26:16 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/07 10:27:09 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_substr_delimited(char *start, const char *end)
{
	char	*result;
	int		i;
	int		len;

	if (!start || !end)
		return (NULL);
	len = end - start + 1;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = -1;
	if (len != 0)
	{
		while ((start + ++i) != end)
			*(result + i) = *(start + i);
		*(result + i) = *(start + i);
	}
	*(result + ++i) = '\0';
	return (result);
}

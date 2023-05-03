/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:11:19 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/03 11:13:00 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int end_index)
{
	char	*result;
	int		i;

	result = (char *)malloc(sizeof(char) * end_index + 2);
	if (!result)
		return (NULL);
	i = 0;
	while (s1 && s1[i] && i <= end_index)
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

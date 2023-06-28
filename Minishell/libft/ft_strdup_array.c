/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:20:02 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/28 11:06:05 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strdup_array(char **str_array)
{
	char	**result;
	int		array_len;
	int		i;

	i = 0;
	array_len = ft_strarraylen(str_array);
	result = malloc((array_len + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (i < array_len)
	{
		result[i] = ft_strdup(str_array[i]);
		if (!result)
		{
			result = ft_free_str_array(result);
			return (NULL);
		}
		++i;
	}
	result[i] = NULL;
	return (result);
}

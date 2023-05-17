/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_retrieve_from_str_array.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:40:53 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/05 14:41:11 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_retrieve_from_str_array(char **src, int index_to_remove)
{
	char	**result;
	int		str_array_len;
	int		i;
	int		j;

	str_array_len = ft_strarraylen(src);
	result = malloc(sizeof(char *) * str_array_len);
	if (!result)
		return (NULL);
	i = -1;
	j = -1;
	while (++i < str_array_len - 1)
	{
		if (i != index_to_remove)
			result[++j] = ft_strdup(*(src + i));
	}
	result[++j] = NULL;
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_str_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:58:28 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/04 19:00:09 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_str_array(char **array)
{
	char	*buffer;
	int		array_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	array_len = ft_strarraylen(array);
	while (i < array_len)
	{
		j = i + 1;
		while (j < array_len)
		{
			if (ft_strcmp(array[i], array[j]) > 0)
			{
				buffer = array[i];
				array[i] = array[j];
				array[j] = buffer;
			}
		j++;
		}
	i++;
	}
}

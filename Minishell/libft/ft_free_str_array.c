/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:43:47 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/04 10:21:06 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	**ft_free_str_array(char **str_array)
{
	int	i;

	i = -1;
	while (str_array && str_array[++i])
		if (str_array[i])
			free(str_array[i]);
	if (str_array)
		free(str_array);
	return (NULL);
}

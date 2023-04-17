/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrayjoin_and_free_srcs.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:06:07 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/07 10:43:30 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strarrayjoin_and_free_srcs(char **sarr1, char **sarr2)
{
	char	**result;
	int		result_len;
	int		i;
	int		j;

	result_len = ft_strarraylen(sarr1) + ft_strarraylen(sarr2);
	result = malloc(sizeof(char *) * result_len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (i + j < result_len)
	{
		*(result + i) = *(sarr1 + i);
		++i;
	}
	while (i + j++ < result_len)
		*(result + i + j) = *(sarr2 + j);
	*(result + i + j) = NULL;
	free(sarr1);
	free(sarr2);
	return (result);
}

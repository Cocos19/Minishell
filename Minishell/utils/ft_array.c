/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:17:21 by cmartino          #+#    #+#             */
/*   Updated: 2023/06/29 11:09:55 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	**ft_free_all(int **array, size_t j)
{
	size_t	i;

	i = 0;
	while (i <= j)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

int	len_tab(char **tb)
{
	int	i;

	i = 0;
	if (!tb)
		return (0);
	while (tb[i])
		++i;
	return (i);
}

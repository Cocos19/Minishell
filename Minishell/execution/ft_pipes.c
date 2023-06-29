/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:50:14 by cmartino          #+#    #+#             */
/*   Updated: 2023/06/29 10:57:09 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*create_mini_pipe(void)
{
	int	*array;

	array = malloc(sizeof(int) * 2);
	if (!array)
		return (NULL);
	return (array);
}

int	**init_pipes(int nbr_pipes)
{
	int	i;
	int	**array;

	array = malloc(sizeof(int *) * (nbr_pipes + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (i < nbr_pipes)
	{
		array[i] = create_mini_pipe();
		if (!array[i])
			return (ft_free_all(array, i));
		i++;
	}
	array[i] = NULL;
	return (array);
}

int	ft_pipe(int **array, int pos)
{
	int	ret;

	ret = pipe(array[pos]);
	return (ret);
}

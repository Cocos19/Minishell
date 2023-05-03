/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:13:43 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/03 11:36:07 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**get_envp_paths(char **envp)
{
	char	**paths;
	int		i;

	if (!envp)
		return (NULL);
	i = -1;
	paths = NULL;
	while (envp[++i])
	{
		if (!ft_strncmp("PATH", envp[i], 4))
			paths = ft_split(&envp[i][5], ':');
	}
	return (paths);
}

void	ft_print_str_array(char **str_array)
{
	int	i;

	i = -1;
	while (str_array && str_array[++i])
		ft_printf("%s\n", str_array[i]);
}

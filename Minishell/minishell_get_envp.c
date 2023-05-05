/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_get_envp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:13:43 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/05 11:38:32 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

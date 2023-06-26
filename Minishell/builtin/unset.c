/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:14:54 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/26 16:15:14 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	index_in_envp_var(t_shell *shell, char *str)
{
	int		var_len;
	int		i;

	i = -1;
	var_len = ft_strlen(str);
	while (shell->envp[++i])
	{
		if (ft_strncmp(shell->envp[i], str, var_len) == 0)
			return (i);
	}
	return (-1);
}

void	execute_unset(t_shell *shell, t_pipe_node *node)
{
	int		var_index;
	int		i;
	char	**result;

	i = 0;
	while (node->arguments[++i])
	{
		var_index = index_in_envp_var(shell, node->arguments[i]);
		if (var_index > -1)
		{
			result = ft_retrieve_from_str_array(shell->envp, var_index);
			free(shell->envp);
			shell->envp = result;
		}
	}
}

int	builtin_unset(t_shell *shell, t_pipe_node *node)
{
	if (!node->arguments[1])
		return (0);
	execute_unset(shell, node);
	return (0);
}

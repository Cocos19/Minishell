/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:14:54 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/20 15:31:36 by mprofett         ###   ########.fr       */
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
	int		redirections_check;

	redirections_check = open_close_inputs(shell, node->input_file_lst);
	if (!redirections_check)
		return (redirections_check);
	redirections_check = open_close_outputs(node->output_file_lst);
	if (!redirections_check)
		return (redirections_check);
	if (!node->arguments[1])
		return (0);
	if (node->fdio[0] == -1 && node->fdio[1] != 1)
		execute_unset(shell, node);
	return (0);
}

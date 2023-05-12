/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_unset.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:14:54 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/12 12:20:27 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	builtin_unset(int fd_in, t_shell *shell, t_pipe_node *node, int fd_out)
{
	int		var_index;
	int		i;
	int		redirections_check;
	char	**result;

	redirections_check = open_close_inputs(shell, node->input_file_lst);
	if (!redirections_check)
		return (redirections_check);
	redirections_check = open_close_outputs(node->output_file_lst);
	if (!redirections_check)
		return (redirections_check);
	if (!node->arguments[1])
		return (0);
	if (fd_in == -1 && fd_out == 1)
	{
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
	return (0);
}

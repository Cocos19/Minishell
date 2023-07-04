/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_middle_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:06:23 by cmartino          #+#    #+#             */
/*   Updated: 2023/07/04 13:20:10 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	middle_cmd(t_shell *shell, t_pipe_node *cmd, int i)
{
	if (is_builtin(cmd) == 0)
		find_path(shell, cmd);
	if (cmd->iofiles[0] == 1)
	{
		ft_dup2(cmd->fdio[0], STDIN_FILENO);
		ft_close(cmd->fdio[0], 0);
	}
	else
	{
		ft_dup2(shell->pipefd[i - 1][0], STDIN_FILENO);
		ft_close(shell->pipefd[i - 1][0], 0);
	}
	if (cmd->iofiles[1] == 1)
	{
		ft_dup2(cmd->fdio[1], STDOUT_FILENO);
		ft_close(cmd->fdio[1], 0);
	}
	else
	{
		ft_dup2(shell->pipefd[i][1], STDOUT_FILENO);
		ft_close(shell->pipefd[i][1], 0);
	}
}

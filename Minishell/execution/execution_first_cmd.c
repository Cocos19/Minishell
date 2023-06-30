/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_first_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:06:23 by cmartino          #+#    #+#             */
/*   Updated: 2023/06/30 15:54:35 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_cmd(t_shell *shell, t_pipe_node *cmd)
{
	if (is_builtin(cmd) == 0)
		find_path(shell, cmd);
	if (cmd->iofiles[0] == 1)
	{
		dup2(cmd->fdio[0], STDIN_FILENO);
		ft_close(cmd->fdio[0], "13");
	}
	if (cmd->iofiles[1] == 1)
	{
		dup2(cmd->fdio[1], STDOUT_FILENO);
		ft_close(cmd->fdio[1], "14");
	}
	else if (shell->nbr_cmds > 1)
	{
		dup2(shell->pipefd[0][1], STDOUT_FILENO);
		ft_close(shell->pipefd[0][1], "15");
	}
}

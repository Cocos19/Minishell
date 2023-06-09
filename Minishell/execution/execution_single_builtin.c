/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_single_builtin.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:06:23 by cmartino          #+#    #+#             */
/*   Updated: 2023/07/04 13:33:20 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	restore_stdout(int dup_stdout)
{
	if (close(STDOUT_FILENO) == -1)
		return ;
	ft_dup2(dup_stdout, STDOUT_FILENO);
	close(dup_stdout);
}

static void	setup_redir_builtin(t_pipe_node *cmd)
{
	if (cmd->iofiles[1] == 1)
	{
		ft_dup2(cmd->fdio[1], STDOUT_FILENO);
		ft_close(cmd->fdio[1], 0);
	}
}

void	execution_single_builtin(t_shell *shell, t_pipe_node *cmd)
{
	cmd->iofiles[0] = 0;
	cmd->iofiles[1] = 0;
	cmd->dup_stdout = -2;
	if (cmd->in_out_redir_list)
	{
		cmd->dup_stdout = dup(STDOUT_FILENO);
		openiofile(shell, cmd, cmd->in_out_redir_list);
		if (cmd->iofiles[0] == 1 && cmd->fdio[0] != -1)
			ft_close(cmd->fdio[0], 0);
	}
	if (cmd->dup_stdout == -1 || shell->exit != 1)
		return ;
	setup_redir_builtin(cmd);
	redirection_builtin(shell, cmd);
	if (cmd->dup_stdout > 2)
		restore_stdout(cmd->dup_stdout);
}

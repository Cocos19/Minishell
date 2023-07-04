/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:06:23 by cmartino          #+#    #+#             */
/*   Updated: 2023/07/04 09:40:27 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_close_children(int pos, t_shell *shell, t_pipe_node *cmd)
{
	if (shell->nbr_cmds <= 1)
		return ;
	if (pos == 0)
	{
		ft_close(shell->pipefd[0][0], "1");
		if (cmd->iofiles[1] == 1)
			ft_close(shell->pipefd[0][1], "2");
	}
	if (pos == shell->nbr_cmds - 1 && cmd->iofiles[0] == 1)
		ft_close(shell->pipefd[pos - 1][0], "3");
	if (pos < shell->nbr_cmds - 1 && pos > 0)
	{
		ft_close(shell->pipefd[pos][0], "4");
		if (cmd->iofiles[0] == 1)
			ft_close(shell->pipefd[pos - 1][0], "5");
		if (cmd->iofiles[1] == 1)
			ft_close(shell->pipefd[pos][1], "6");
	}
}

void	ft_children(t_shell *shell, t_pipe_node *cmd, int pos)
{
	activate_signals(CHILD_MODE);
	ft_close_children(pos, shell, cmd);
	if (pos == 0)
		first_cmd(shell, shell->pipe_lst);
	else if (pos == shell->nbr_cmds - 1)
		last_cmd(shell, cmd, pos);
	else
		middle_cmd(shell, cmd, pos);
	if (shell->exit == 2)
		exit(EXIT_FAILURE);
	if (redirection_builtin(shell, cmd) == 0)
	{
		if (g_exit_status == 127)
			exit (COMMAND_NOT_FOUND);
		execve(cmd->path, cmd->arguments, shell->envp);
		if (ft_strncmp(cmd->arguments[0], "./", 2) == 0
			|| ft_strncmp(cmd->arguments[0], "/", 1) == 0)
		{
			printf("minishell: %s: Is a directory\n", cmd->arguments[0]);
			exit (126);
		}
		exit (EXIT_FAILURE);
	}
	exit(shell->last_exit_status);
}

void	loop_execution(t_shell *shell, t_pipe_node	*cmd, int i)
{
	while (cmd)
	{
		shell->exit = 1;
		cmd->iofiles[0] = 0;
		cmd->iofiles[1] = 0;
		if (cmd->in_out_redir_list)
			openiofile(shell, cmd, cmd->in_out_redir_list);
		if (shell->exit == 0 || !cmd->arguments)
		{
			shell->nbr_cmds = i;
			return ;
		}
		if (cmd->next)
			ft_pipe(shell->pipefd, i);
		shell->pids[i] = ft_fork(shell);
		if (shell->pids[i] == -1)
			return ;
		if (shell->pids[i] == 0 && cmd->arguments)
			ft_children(shell, cmd, i);
		ft_close_parent(i, cmd, shell);
		cmd = cmd->next;
		i++;
	}
}

void	execution(t_shell *shell)
{
	t_pipe_node	*cmd;

	cmd = shell->pipe_lst;
	shell->exit = 1;
	shell->nbr_cmds = lstsize_cmd(cmd);
	if (!cmd->next && is_builtin(cmd))
	{
		execution_single_builtin(shell, cmd);
		return ;
	}
	shell->pipefd = init_pipes(shell->nbr_cmds);
	create_pids(shell, cmd);
	loop_execution(shell, cmd, 0);
	ft_waitpids(shell);
	ft_waitpids(shell);
	ft_free_execution(shell);
}

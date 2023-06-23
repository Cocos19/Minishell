/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_first_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:06:23 by cmartino          #+#    #+#             */
/*   Updated: 2023/06/23 14:49:17 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	first_cmd2(t_shell *shell, t_pipe_node *pipe)
{
	(void)shell;
	if (pipe->iofiles[0] == 1)
	{
		dup2(pipe->fdio[0], STDIN_FILENO);
		if (pipe->fdio[0] != -1)
			ft_close(pipe->fdio[0]);
	}
	if (pipe->iofiles[1] == 1)
	{
		dup2(pipe->fdio[1], STDOUT_FILENO);
		ft_close(pipe->fd[1]);
		pipe->fd[1] = pipe->fdio[1];
	}
	else
		dup2(pipe->fd[1], STDOUT_FILENO);
}

void	first_cmd(t_shell *shell, t_pipe_node *pipe)
{
	ft_pipe(shell, pipe);
	find_path(shell, pipe);
	shell->pids[0] = ft_fork(shell);
	if (shell->pids[0] == 0)
	{
		if (!pipe->arguments[0])
			exit(EXIT_FAILURE);
		first_cmd2(shell, pipe);
		ft_close(pipe->fd[0]);
		if (redirection_builtin(shell, pipe) == 0)
			execve(pipe->path, pipe->arguments, shell->envp);
		exit(EXIT_FAILURE);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_middle_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:06:23 by cmartino          #+#    #+#             */
/*   Updated: 2023/06/19 11:28:01 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	middle_cmd2(t_shell *shell, t_pipe_node *pipe)
{
	if (pipe->input_file_lst)
	{
		ft_close(pipe->fdio[0]);
		pipe->fdio[0] = ft_open_infiles(shell, pipe);
		dup2(pipe->fdio[0], STDIN_FILENO);
		if (pipe->fdio[0] != -1)
			ft_close(pipe->fdio[0]);
	}
	else
		dup2(pipe->fdio[0], STDIN_FILENO);
	ft_close_files(pipe->fdio[0], "middle cmd");
	close(pipe->fdio[1]);
	if (pipe->output_file_lst)
	{
		pipe->fdio[1] = ft_open_outfiles(shell, pipe);
		dup2(pipe->fdio[1], STDOUT_FILENO);
		ft_close(pipe->fd[1]);
		pipe->fd[1] = pipe->fdio[1];
	}
	else
		dup2(pipe->fd[1], STDOUT_FILENO);
}

void	middle_cmd(t_shell *shell, t_pipe_node *pipe, int i)
{
	find_path(shell, pipe);
	ft_pipe(shell, pipe);
	shell->pids[i] = ft_fork(shell);
	if (shell->pids[i] == 0)
	{
		if (!pipe->arguments[0])
			exit(EXIT_FAILURE);
		middle_cmd2(shell, pipe);
		ft_close(pipe->fd[0]);
		ft_close(pipe->fd[1]);
		if (redirection_builtin(shell, pipe) == 0)
			execve(pipe->path, pipe->arguments, shell->envp);
		exit(EXIT_FAILURE);
	}
}

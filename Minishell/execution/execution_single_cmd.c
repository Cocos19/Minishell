/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_single_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:06:23 by cmartino          #+#    #+#             */
/*   Updated: 2023/06/26 10:42:32 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execution_cmd(t_shell *shell, t_pipe_node *pipe)
{
	if (redirection_builtin(shell, pipe) == 0)
	{
		shell->pids[0] = ft_fork(shell);
		if (shell->pids[0] == 0)
		{
			if (pipe->iofiles[0] == 1)
			{
				dup2(pipe->fdio[0], STDIN_FILENO);
				if (pipe->fdio[0] != -1)
					ft_close(pipe->fdio[0]);
			}
			if (pipe->iofiles[1] == 1)
			{
				dup2(pipe->fdio[1], STDOUT_FILENO);
				ft_close(pipe->fdio[1]);
			}
			else
				pipe->fdio[1] = 1;
			execve(pipe->path, pipe->arguments, shell->envp);
			exit(EXIT_FAILURE);
		}
		ft_waitpids(shell, pipe);
	}
}

void	execution_single_cmd(t_shell *shell, t_pipe_node *pipe)
{
	pipe->iofiles[0] = 0;
	pipe->iofiles[1] = 0;
	if (is_builtin(pipe) == 0)
		find_path(shell, pipe);
	create_pids(shell, pipe);
	pipe->fdio[0] = -1;
	pipe->fdio[0] = 1;
	if (pipe->in_out_redir_list)
		openiofile(shell, pipe, pipe->in_out_redir_list);
	if (shell->exit == 1)
		execution_cmd(shell, pipe);
	free(shell->pids);
}

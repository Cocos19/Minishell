/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:06:23 by cmartino          #+#    #+#             */
/*   Updated: 2023/06/26 16:33:46 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_path(t_shell *shell, t_pipe_node *pipe)
{
	char	*cmd;
	char	*cmd_final;

	cmd = cmd_exist(shell, shell->envp, pipe->arguments);
	if (shell->exit == 0)
	{
		free(cmd);
		return ;
	}
	cmd_final = ft_strjoin_protected(cmd, "/");
	free(cmd);
	pipe->path = ft_strjoin_protected(cmd_final, pipe->arguments[0]);
	free(cmd_final);
}

int	execution_several_cmds_midlle(t_shell *shell, t_pipe_node *pipe)
{
	int	i;

	i = 1;
	while (pipe->next)
	{
		pipe->fdio[0] = pipe->fd[0];
		pipe->iofiles[0] = 0;
		pipe->iofiles[1] = 0;
		if (pipe->in_out_redir_list)
			openiofile(shell, pipe, pipe->in_out_redir_list);
		middle_cmd(shell, pipe, i);
		ft_close_files(pipe->fdio[0], "test1");
		ft_close_files(pipe->fd[1], "test2");
		ft_copy_fd(pipe);
		pipe = pipe->next;
		++i;
	}
	pipe->fdio[0] = pipe->fd[1];
	pipe->iofiles[0] = 0;
	pipe->iofiles[1] = 0;
	return (i);
}

void	execution_several_cmds(t_shell *shell, t_pipe_node *pipe)
{
	t_pipe_node	*pipe_temp;
	int			i;

	pipe_temp = pipe;
	pipe->iofiles[0] = 0;
	pipe->iofiles[1] = 0;
	create_pids(shell, pipe);
	pipe->fdio[0] = -1;
	pipe->fdio[1] = 1;
	if (pipe->in_out_redir_list)
		openiofile(shell, pipe, pipe->in_out_redir_list);
	first_cmd(shell, pipe);
	ft_close(pipe->fd[1]);
	ft_copy_fd(pipe);
	pipe = pipe->next;
	i = execution_several_cmds_midlle(shell, pipe);
	if (pipe->in_out_redir_list)
		openiofile(shell, pipe, pipe->in_out_redir_list);
	last_cmd(shell, pipe, i);
	// ft_close_files(pipe->fd[0], "fd[0] last");
	ft_waitpids(shell, pipe_temp);
}

void	execution(t_shell *shell)
{
	t_pipe_node	*pipe;

	pipe = shell->pipe_lst;
	shell->exit = 1;
	if (!pipe->next)
		execution_single_cmd(shell, pipe);
	else
		execution_several_cmds(shell, pipe);
}

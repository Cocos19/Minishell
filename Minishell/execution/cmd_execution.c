/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:06:23 by cmartino          #+#    #+#             */
/*   Updated: 2023/05/17 11:21:33 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_path(t_shell *shell, t_pipe_node *pipe)
{
	char	*cmd;
	char	*cmd_final;

	cmd = cmd_exist(shell->envp, pipe->arguments);
	cmd_final = ft_strjoin_protected(cmd, "/");
	free(cmd);
	pipe->path = ft_strjoin_protected(cmd_final, pipe->arguments[0]);
	free(cmd_final);
}

void	execution_several_cmds(t_shell *shell, t_pipe_node *pipe)
{
	t_pipe_node	*pipe_temp;
	int			i;

	pipe_temp = pipe;
	create_pids(shell, pipe);
	ft_pipe(shell, pipe);
	first_cmd(shell, pipe);
	ft_close(pipe->fd[1]);
	ft_copy_fd(pipe);
	pipe = pipe->next;
	i = 1;
	while (pipe->next)
	{
		pipe->fdio[0] = pipe->fd[0];
		middle_cmd(shell, pipe, i);
		ft_close_files(pipe->fdio[0], "test1");
		ft_close_files(pipe->fd[1], "test2");
		ft_copy_fd(pipe);
		pipe = pipe->next;
		++i;
	}
	pipe->fdio[0] = pipe->fd[1];
	last_cmd(shell, pipe, i);
	ft_close_files(pipe->fd[0], "fd[0] last");
	ft_waitpids(shell, pipe_temp);
}

void	execution(t_shell *shell)
{
	t_pipe_node	*pipe;

	pipe = shell->pipe_lst;
	if (!pipe->next)
		execution_one_cmd(shell, pipe);
	else
		execution_several_cmds(shell, pipe);
}

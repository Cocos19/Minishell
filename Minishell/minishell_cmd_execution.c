/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cmd_execution.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:06:23 by cmartino          #+#    #+#             */
/*   Updated: 2023/04/24 14:50:58 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*create_pids(t_pipe_node *pipe)
{
	int	pids;

	pids = ft_calloc(sizeof(int), ft_lstsize(pipe));
	if (!pids)
		exit(EXIT_FAILURE);
	return (pids);
}

void	ft_close(int fd)
{
	if (close(fd) == -1)
		perror(__func__);
	// donner le nom du fichier ??? 
}

void	ft_pipe(t_shell *shell, int *fd)
{
	pipe(fd);
	if (fd[0] == -1 || fd[1] == -1)
		exit(EXIT_FAILURE);
	(void)shell;
}

int	ft_fork(t_shell *shell)
{
	int	result;

	result = fork();
	if (result == -1)
		exit(EXIT_FAILURE);
	(void)shell;
	return (result);
}

char	*cmd_exist(char **envp, char **arg)
{
	if (access(arg[0], X_OK) == 0)
		return (arg[0]);
	else
	{
		// search + access each
	}
	return (NULL);
}

void	execution_one_cmd(t_shell *shell, t_pipe_node *pipe)
{
	char	*cmd;

	cmd = cmd_exist(shell->envp, pipe->arguments);
	execve(cmd, pipe->arguments, shell->envp);
	exit(EXIT_FAILURE);
}

void	first_cmd(t_shell *shell, t_pipe_node *pipe, int *pids)
{
	pids[0] = ft_fork(shell);
	(void)shell;
}

void	middle_cmd(t_shell *shell, t_pipe_node *pipe)
{
	(void)shell;
}

void	last_cmd(t_shell *shell, t_pipe_node *pipe)
{
	(void)shell;
}

void	ft_waitpids(t_shell *shell, t_pipe_node *pipe, int *pids)
{
	int	status;
	int	i;
	int	len;

	i = 0;
	len = ft_lstsize(pipe);
	while (i < len)
	{
		if (waitpid(pids[i], &status, 0) == -1)
		{
			perror("waitpid");
			ft_exit(WEXITSTATUS(status));
		}
		++i;
	}
	// exit_status = WEXITSTATUS(status);
	(void)shell;
}

void	execution_several_cmds(t_shell *shell, t_pipe_node *pipe)
{
	int			fd[2];
	int			*pids;

	pids = create_pids(pipe);
	ft_pipe(shell, fd);
	first_cmd(shell, pipe, pids);
	if (pipe->input_file_lst != 0)
		ft_close(pipe->input_file_lst);
	ft_close(pipe->output_file_lst);
	while (pipe->next)
	{
		pipe->input_file_lst = fd[1];
		middle_cmd(shell, pipe);
		ft_close(pipe->output_file_lst);
		ft_close(fd[1]);
	}
	last_cmd(shell, pipe);
	ft_close(pipe->input_file_lst);
	ft_close(fd[1]);
	ft_waitpids(shell, pipe, pids);
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

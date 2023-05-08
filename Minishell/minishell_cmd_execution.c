/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cmd_execution.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:06:23 by cmartino          #+#    #+#             */
/*   Updated: 2023/05/08 09:39:49 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution_one_cmd(t_shell *shell, t_pipe_node *pipe)
{	
	char *cmd;
	char *cmd_final;
	int	pids[2];
	int status;

	cmd = cmd_exist(shell->envp, pipe->arguments);
	cmd_final = ft_strjoin_protected(shell, cmd, "/");
	free(cmd);
	pipe->path = ft_strjoin_protected(shell, cmd_final, pipe->arguments[0]);
	free(cmd_final);
	pids[0] = ft_fork(shell);
	if (pids[0] == 0)
	{
		execve(pipe->path, pipe->arguments, shell->envp);
		exit(EXIT_FAILURE);
	}
	if (waitpid(pids[0], &status, 0) == -1)
	{
		perror("waitpid");
		exit(WEXITSTATUS(status));
	}
}

// void	first_cmd(t_shell *shell, t_pipe_node *pipe, int *pids, int *fd)
// {
// 	pipe->path = cmd_exist(shell->envp, pipe->arguments);
// 	pids[0] = ft_fork(shell);
// 	if (pids[0] == 0)
// 	{
// 		if (pipe->input_file_lst == -1 || !pipe->arguments[0])
// 			exit(EXIT_FAILURE);
// 		ft_dup2(shell, pipe->input_file_lst, STDIN_FILENO);
// 		ft_close(pipe->input_file_lst);
// 		ft_dup2(shell, fd[1],  STDOUT_FILENO);
// 		ft_close(fd[1]);
// 		ft_close(fd[0]);
// 		execve(pipe->arguments, pipe->path, shell->envp);
// 		exit(EXIT_FAILURE);
// 	}
// }

// void	middle_cmd(t_shell *shell, t_pipe_node *pipe, int *pids, int *fd)
// {
// 	pipe->path = cmd_exist(shell->envp, pipe->arguments);
// 	pids[0] = ft_fork(shell);
// 	if (pids[0] == 0)
// 	{
// 		if (!!pipe->arguments[0])
// 			exit(EXIT_FAILURE);
// 		ft_dup2(shell, pipe->input_file_lst, STDIN_FILENO);
// 		ft_close(pipe->input_file_lst);
// 		ft_close(pipe->output_file_lst);
// 		ft_dup2(shell, fd[1], STDOUT_FILENO);
// 		ft_close(fd[0]);
// 		ft_close(fd[1]);
// 		execve(pipe->arguments, pipe->path, shell->envp);
// 		exit(EXIT_FAILURE);
// 	}
// }

// void	last_cmd(t_shell *shell, t_pipe_node *pipe, int *pids, int *fd)
// {
// 	pipe->path = cmd_exist(shell->envp, pipe->arguments);
// 	pids[0] = ft_fork(shell);
// 	if (pids[0] == 0)
// 	{
// 		if (!!pipe->arguments[0])
// 			exit(EXIT_FAILURE);
// 		ft_dup2(shell, fd[0], STDIN_FILENO);
// 		ft_close(fd[0]);
// 		ft_dup2(shell, pipe->output_file_lst, STDIN_FILENO);
// 		ft_close(pipe->output_file_lst);
// 		execve(pipe->arguments, pipe->path, shell->envp);
// 		exit(EXIT_FAILURE);
// 	}
// }

// void	ft_waitpids(t_shell *shell, t_pipe_node *pipe, int *pids)
// {
// 	int	status;
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = ft_lstsize(pipe);
// 	while (i < len)
// 	{
// 		if (waitpid(pids[i], &status, 0) == -1)
// 		{
// 			perror("waitpid");
// 			ft_exit(WEXITSTATUS(status));
// 		}
// 		++i;
// 	}
// 	// exit_status = WEXITSTATUS(status);
// 	(void)shell;
// }

// int	*ft_open_files(t_shell *shell, t_pipe_node *pipe)
// {
// 	int	i;
// 	int	fd;
	
// 	i = 0;
// 	while (pipe->input_file_lst && pipe->input_file_lst[i])
// 	{
// 		fd = open(pipe->input_file_lst[i]);
// 		if (pipe->input_file_lst[i])
// 			ft_close(fd);
// 		++i
// 	}
// 	return (fd);
// }

// void	execution_several_cmds(t_shell *shell, t_pipe_node *pipe)
// {
// 	int			*fd;
// 	int			*pids;
// 	int			*temp_pid;

// 	pids = create_pids(pipe);
// 	fd = ft_open_files(shell, pipe);
// 	ft_pipe(shell, fd);
// 	first_cmd(shell, pipe, pids, fd);
// 	if (pipe->input_file_lst != 0)
// 		ft_close(pipe->input_file_lst);
// 	ft_close(fd[1]);
// 	temp_pid = pids;
// 	pipe = pipe->next;
// 	while (pipe->next)
// 	{
// 		pipe->input_file_lst = fd[1];
// 		middle_cmd(shell, pipe, *temp_pid++, fd);
// 		ft_close(pipe->output_file_lst);
// 		ft_close(fd[1]);
// 		pipe = pipe->next;
// 	}
// 	last_cmd(shell, pipe, *temp_pid++, fd);
// 	ft_close(pipe->input_file_lst);
// 	ft_close(fd[1]);
// 	ft_waitpids(shell, pipe, pids);
// }

void	execution(t_shell *shell)
{
	t_pipe_node	*pipe;

	pipe = shell->pipe_lst;
	if (!pipe->next)
		execution_one_cmd(shell, pipe);
	// else
		// execution_several_cmds(shell, pipe);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cmd_execution.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:06:23 by cmartino          #+#    #+#             */
/*   Updated: 2023/05/09 17:14:23 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  solution mettre fdio dans la structure


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
		if (pipe->input_file_lst)
		{
			pipe->fdio[0] = ft_open_infiles(shell, pipe);
			dup2(pipe->fdio[0], STDIN_FILENO);
			if (pipe->fdio[0] != -1)
				ft_close(pipe->fdio[0]);
		}
		if (pipe->output_file_lst)
		{
			pipe->fdio[1] = ft_open_outfiles(shell, pipe);
			dup2(pipe->fdio[1], STDOUT_FILENO);
			ft_close(pipe->fdio[1]);
		}
		execve(pipe->path, pipe->arguments, shell->envp);
		exit(EXIT_FAILURE);
	}
	if (waitpid(pids[0], &status, 0) == -1)
	{
		perror("waitpid");
		exit(WEXITSTATUS(status));
	}
}

void	first_cmd(t_shell *shell, t_pipe_node *pipe, int *pids)
{
	char *cmd;
	char *cmd_final;
	
	cmd = cmd_exist(shell->envp, pipe->arguments);
	cmd_final = ft_strjoin_protected(shell, cmd, "/");
	free(cmd);
	pipe->path = ft_strjoin_protected(shell, cmd_final, pipe->arguments[0]);
	free(cmd_final);
	pids[0] = ft_fork(shell);
	if (pids[0] == 0)
	{
		printf("-> child in first cmd\n");
		if (!pipe->arguments[0])
			exit(EXIT_FAILURE);
		if (pipe->input_file_lst)
		{
			printf("test1\n");
			pipe->fdio[0] = ft_open_infiles(shell, pipe);
			dup2(pipe->fdio[0], STDIN_FILENO);
			if (pipe->fdio[0] != -1)
				ft_close(pipe->fdio[0]);
		}
		if (pipe->output_file_lst)
		{
			printf("test2\n");
			pipe->fdio[1] = ft_open_outfiles(shell, pipe);
			dup2(pipe->fdio[1], STDOUT_FILENO);
			ft_close(pipe->fd[1]);
			pipe->fd[1] = pipe->fdio[1];
		}
		else
		{
			printf("test3\n");
			dup2(pipe->fd[1],  STDOUT_FILENO);
			printf("segfault\n");
		}
		ft_close_files(pipe->fd[1], "fd[1] -> first cmd");
		ft_close_files(pipe->fd[0], "fd[0] -> first cmd");
		execve(pipe->path, pipe->arguments, shell->envp);
		// printf("--> test <--\n");
		exit(EXIT_FAILURE);
	}
}

// void	middle_cmd(t_shell *shell, t_pipe_node *pipe, int *pids)
// {
// 	pipe->path = cmd_exist(shell->envp, pipe->arguments);
// 	pids[0] = ft_fork(shell);
// 	if (pids[0] == 0)
// 	{
// 		if (!pipe->arguments[0])
// 			exit(EXIT_FAILURE);
// 		if (pipe->input_file_lst)
// 		{
// 			ft_close(pipe->fdio[0]);
// 			pipe->fdio[0] = ft_open_infiles(shell, pipe);
// 			dup2(pipe->fdio[0], STDIN_FILENO);
// 		}
// 		else
// 			dup2(pipe->fdio[0], STDIN_FILENO);
// 		ft_close(pipe->fdio[0]);
// 		if (pipe->output_file_lst)
// 		{
// 			pipe->fdio[1] = ft_open_outfiles(shell, pipe);
// 			dup2(pipe->fdio[1], STDOUT_FILENO);
// 			ft_close(pipe->fd[1]);
// 			pipe->fd[1] = pipe->fdio[1];
// 		}
// 		else
// 		{
// 			dup2(pipe->fd[1],  STDOUT_FILENO);
// 		}
// 		ft_close(pipe->fd[0]);
// 		ft_close(pipe->fd[1]);
// 		execve(pipe->path, pipe->arguments, shell->envp);
// 		exit(EXIT_FAILURE);
// 	}
// }

void	last_cmd(t_shell *shell, t_pipe_node *pipe, int *pids, int *fd)
{
	pipe->path = cmd_exist(shell->envp, pipe->arguments);
	pids[0] = ft_fork(shell);
	if (pids[0] == 0)
	{
		if (!pipe->arguments[0])
			exit(EXIT_FAILURE);
		if (pipe->input_file_lst)
		{
			ft_close(pipe->fdio[0]);
			pipe->fdio[0] = ft_open_infiles(shell, pipe);
			dup2(pipe->fdio[0], STDIN_FILENO);
			ft_close(pipe->fdio[0]);
		}
		else
		{
			dup2(fd[0], STDIN_FILENO);
			ft_close(fd[0]);
		}
		if (pipe->output_file_lst)
		{
			dup2(pipe->fdio[1], STDOUT_FILENO);
			ft_close(pipe->fdio[1]);
		}
		else
			dup2(1, STDOUT_FILENO);
		execve(pipe->path, pipe->arguments, shell->envp); // ne marche pas, pq ? 
		exit(EXIT_FAILURE);
	}
}

void	ft_waitpids(t_shell *shell, t_pipe_node *pipe, int *pids)
{
	int	status;
	int	i;
	int	len;

	i = 0;
	len = ft_lstsize_pipe(pipe);
	while (i < len)
	{
		if (waitpid(pids[i], &status, 0) == -1)
		{
			perror("waitpid");
			exit(WEXITSTATUS(status));
		}
		++i;
	}
	// exit_status = WEXITSTATUS(status);
	(void)shell;
}

void	execution_several_cmds(t_shell *shell, t_pipe_node *pipe)
{
	int			*pids;
	int			*temp_pid;

	pids = create_pids(pipe);
	ft_pipe(shell, pipe);
	first_cmd(shell, pipe, pids);
	// if (pipe->fdio[0] != 0)	// pq faire? + initialiser fdio
		// ft_close_files(pipe->fdio[0], pipe->input_file_lst->last->value);
	// ft_close(fd[1]);
	temp_pid = pids;
	// printf("-> temp_pid ok <-\n");
	pipe = pipe->next;
	exit(EXIT_SUCCESS);
	// printf("-> before loop ok <-\n");
	// while (pipe->next)
	// {
	// 	pipe->fdio[0] = fd[1];
	// 	middle_cmd(shell, pipe, temp_pid++, fd);
	// 	ft_close_files(pipe->fdio[1], pipe->output_file_lst->last->value);
	// 	ft_close(fd[1]);
	// 	pipe = pipe->next;
	// }
	// printf("-> after loop ok <-\n");
	// last_cmd(shell, pipe, temp_pid++, fd);
	// ft_close_files(pipe->fdio[0], pipe->input_file_lst->last->value);
	// ft_close(fd[1]);
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

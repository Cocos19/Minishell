/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cmd_execution.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:06:23 by cmartino          #+#    #+#             */
/*   Updated: 2023/05/10 17:17:23 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  regler execve de middle et last cmd



void	ft_copy_fd(t_pipe_node *pipe)
{
	pipe->next->fd[0] = pipe->fd[0];
	pipe->next->fd[1] = pipe->fd[1];
	pipe->next->fdio[0] = pipe->fdio[0];
	pipe->next->fdio[1] = pipe->fdio[1];
}

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

void	first_cmd(t_shell *shell, t_pipe_node *pipe)
{
	char *cmd;
	char *cmd_final;
	
	cmd = cmd_exist(shell->envp, pipe->arguments);
	cmd_final = ft_strjoin_protected(shell, cmd, "/");
	free(cmd);
	pipe->path = ft_strjoin_protected(shell, cmd_final, pipe->arguments[0]);
	free(cmd_final);
	shell->pids[0] = ft_fork(shell);
	if (shell->pids[0] == 0)
	{
		if (!pipe->arguments[0])
			exit(EXIT_FAILURE);
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
			ft_close(pipe->fd[1]);
			pipe->fd[1] = pipe->fdio[1];
		}
		else
			dup2(pipe->fd[1],  STDOUT_FILENO);
		ft_close(pipe->fd[0]);
		execve(pipe->path, pipe->arguments, shell->envp);
		exit(EXIT_FAILURE);
	}
}

void	middle_cmd(t_shell *shell, t_pipe_node *pipe, int i)
{
	char *cmd;
	char *cmd_final;
	
	cmd = cmd_exist(shell->envp, pipe->arguments);
	cmd_final = ft_strjoin_protected(shell, cmd, "/");
	free(cmd);
	pipe->path = ft_strjoin_protected(shell, cmd_final, pipe->arguments[0]);
	free(cmd_final);
	shell->pids[i] = ft_fork(shell);
	if (shell->pids[i] == 0)
	{
		if (!pipe->arguments[0])
			exit(EXIT_FAILURE);
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
		if (pipe->output_file_lst)
		{
			pipe->fdio[1] = ft_open_outfiles(shell, pipe);
			dup2(pipe->fdio[1], STDOUT_FILENO);
			ft_close(pipe->fd[1]);
			pipe->fd[1] = pipe->fdio[1];
		}
		else
			dup2(pipe->fd[1],  STDOUT_FILENO);
		ft_close(pipe->fd[0]);
		ft_close(pipe->fd[1]);
		execve(pipe->path, pipe->arguments, shell->envp);
		printf("teeeeeest\n");
		exit(EXIT_FAILURE);
	}
}

void	last_cmd(t_shell *shell, t_pipe_node *pipe, int i)
{
	char *cmd;
	char *cmd_final;
	
	cmd = cmd_exist(shell->envp, pipe->arguments);
	cmd_final = ft_strjoin_protected(shell, cmd, "/");
	free(cmd);
	pipe->path = ft_strjoin_protected(shell, cmd_final, pipe->arguments[0]);
	free(cmd_final);
	shell->pids[i] = ft_fork(shell);
	if (shell->pids[i] == 0)
	{
		if (!pipe->arguments[0])
			exit(EXIT_FAILURE);
		if (pipe->input_file_lst)
		{
			ft_close(pipe->fdio[0]);
			pipe->fdio[0] = ft_open_infiles(shell, pipe);
			dup2(pipe->fdio[0], STDIN_FILENO);
			if (pipe->fdio[0] != -1)
				ft_close(pipe->fdio[0]);
		}
		else
			dup2(pipe->fd[0], STDIN_FILENO);
		if (pipe->output_file_lst)
		{
			pipe->fdio[1] = ft_open_outfiles(shell, pipe);
			dup2(pipe->fdio[1], STDOUT_FILENO);
			ft_close_files(pipe->fdio[1], "fdio[1] first cmd output");
		}
		else
			dup2(1, STDOUT_FILENO);
		ft_close_files(pipe->fd[0], "fd[0] last cmd");
		execve(pipe->path, pipe->arguments, shell->envp);
		exit(EXIT_FAILURE);
	}
}

void	ft_waitpids(t_shell *shell, t_pipe_node *pipe)
{
	int	status;
	int	i;
	int	len;

	i = 0;
	len = ft_lstsize_pipe(pipe);
	while (i < len)
	{
		printf("pids = %d\n", i);
		if (waitpid(shell->pids[i], &status, 0) == -1)
		{
			perror("waitpid");
			exit(WEXITSTATUS(status));
		}
		++i;
	}
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
	// while (pipe->next)
	// {
	// 	pipe->fdio[0] = pipe->fd[0];
	// 	middle_cmd(shell, pipe, i);
	// 	ft_close_files(pipe->fdio[0], "test1"); // ok
	// 	// ft_close_files(pipe->fd[1], "test2"); // bad file descriptor
	// 	ft_copy_fd(pipe);
	// 	pipe = pipe->next;
	// 	++i;
	// }
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

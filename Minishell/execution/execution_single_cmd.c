/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_single_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:06:23 by cmartino          #+#    #+#             */
/*   Updated: 2023/06/19 11:44:09 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* marche sauf normal + in_outfile */

void	execution_single_cmd2(t_shell *shell, t_pipe_node *pipe)
{
	find_path(shell, pipe);
	create_pids(shell, pipe);
	shell->pids[0] = ft_fork(shell);
	if (shell->pids[0] == 0)
	{
		if (pipe->input_file_lst)
		{
			if (pipe->input_file_lst->mode == 2)
			{
				printf("heredoc\n");
			}
			else
			{
				pipe->fdio[0] = ft_open_infiles(shell, pipe);
				dup2(pipe->fdio[0], STDIN_FILENO);
				if (pipe->fdio[0] != -1)
					ft_close(pipe->fdio[0]);
			}
		}
		else
			pipe->fdio[0] = -1;
		if (pipe->output_file_lst)
		{
			pipe->fdio[1] = ft_open_outfiles(shell, pipe);
			dup2(pipe->fdio[1], STDOUT_FILENO);
			ft_close(pipe->fdio[1]);
		}
		execve(pipe->path, pipe->arguments, shell->envp);
		exit(EXIT_FAILURE);
	}
	ft_waitpids(shell, pipe);
}

void	execution_single_cmd(t_shell *shell, t_pipe_node *pipe)
{
	if (is_builtin(pipe) == 0 && (pipe->input_file_lst || pipe->output_file_lst))
	{
		execution_single_cmd2(shell, pipe);
		return ;
	}
	find_path(shell, pipe);
	create_pids(shell, pipe);
		if (pipe->input_file_lst)
		{
			if (pipe->input_file_lst->mode == 2)
			{
				printf("heredoc\n");
			}
			else
			{
				pipe->fdio[0] = ft_open_infiles(shell, pipe);
				if (is_builtin(pipe) == 0)
					dup2(pipe->fdio[0], STDIN_FILENO);
				if (pipe->fdio[0] != -1)
					ft_close(pipe->fdio[0]);
			}
		}
		if (pipe->output_file_lst)
		{
			pipe->fdio[1] = ft_open_outfiles(shell, pipe);
			if (is_builtin(pipe) == 0)
			{
				dup2(pipe->fdio[1], STDOUT_FILENO);
				ft_close(pipe->fdio[1]);
			}
		}
		else
			pipe->fdio[1] = 1;
		if (redirection_builtin(shell, pipe) == 0)
		{
			shell->pids[0] = ft_fork(shell);
			if (shell->pids[0] == 0)
			{
				execve(pipe->path, pipe->arguments, shell->envp);
				exit(EXIT_FAILURE);
			}
			ft_waitpids(shell, pipe);
		}
}

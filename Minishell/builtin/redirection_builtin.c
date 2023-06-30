/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 09:50:00 by cmartino          #+#    #+#             */
/*   Updated: 2023/06/30 12:53:02 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_pipe_node *pipe)
{
	if (!pipe->arguments)
		return(0);
	if (ft_strcmp(pipe->arguments[0], "cd") == 0)
		return (1);
	if (ft_strcmp(pipe->arguments[0], "echo") == 0)
		return (1);
	if (ft_strcmp(pipe->arguments[0], "env") == 0)
		return (1);
	if (ft_strcmp(pipe->arguments[0], "exit") == 0)
		return (1);
	if (ft_strcmp(pipe->arguments[0], "export") == 0)
		return (1);
	if (ft_strcmp(pipe->arguments[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(pipe->arguments[0], "unset") == 0)
		return (1);
	return (0);
}

int	redirection_builtin(t_shell *shell, t_pipe_node *pipe)
{
	if (ft_strcmp(pipe->arguments[0], "cd") == 0)
		shell->last_exit_status = builtin_cd(shell, pipe);
	else if (ft_strcmp(pipe->arguments[0], "echo") == 0)
		shell->last_exit_status = builtin_echo(shell, pipe);
	else if (ft_strcmp(pipe->arguments[0], "env") == 0)
		shell->last_exit_status = builtin_env(shell, pipe);
	else if (ft_strcmp(pipe->arguments[0], "exit") == 0)
		shell->last_exit_status = builtin_exit(shell, pipe);
	else if (ft_strcmp(pipe->arguments[0], "export") == 0)
		shell->last_exit_status = builtin_export(shell, pipe);
	else if (ft_strcmp(pipe->arguments[0], "pwd") == 0)
		shell->last_exit_status = builtin_pwd();
	else if (ft_strcmp(pipe->arguments[0], "unset") == 0)
		shell->last_exit_status = builtin_unset(shell, pipe);
	else
		return (0);
	return (1);
}

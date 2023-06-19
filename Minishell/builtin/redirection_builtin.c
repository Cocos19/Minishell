/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 09:50:00 by cmartino          #+#    #+#             */
/*   Updated: 2023/06/19 10:23:56 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirection_buitin2(t_shell *shell, t_pipe_node *pipe)
{
	if (ft_strcmp(pipe->arguments[0], "export") == 0)
	{
		builtin_export(shell, pipe);
		return (1);
	}
	if (ft_strcmp(pipe->arguments[0], "pwd") == 0)
	{
		builtin_pwd(shell, pipe);
		return (1);
	}
	if (ft_strcmp(pipe->arguments[0], "unset") == 0)
	{
		builtin_unset(shell, pipe);
		return (1);
	}
	return (0);
}

int	redirection_buitin(t_shell *shell, t_pipe_node *pipe)
{
	printf("test1\n");
	if (ft_strcmp(pipe->arguments[0], "cd") == 0)
	{
		builtin_cd(shell, pipe);
		return (1);
	}
	if (ft_strcmp(pipe->arguments[0], "echo") == 0)
	{
		builtin_echo(shell, pipe);
		return (1);
	}
	if (ft_strcmp(pipe->arguments[0], "env") == 0)
	{
		builtin_env(shell, pipe);
		return (1);
	}
	if (ft_strcmp(pipe->arguments[0], "exit") == 0)
	{
		builtin_exit(shell, pipe);
		return (1);
	}
	return(redirection_buitin2(shell, pipe))
}

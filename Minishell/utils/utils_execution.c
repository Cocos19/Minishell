/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:20:31 by cmartino          #+#    #+#             */
/*   Updated: 2023/06/27 14:13:35 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_copy_fd(t_pipe_node *pipe)
{
	pipe->next->fd[0] = pipe->fd[0];
	pipe->next->fd[1] = pipe->fd[1];
	pipe->next->fdio[0] = pipe->fdio[0];
	pipe->next->fdio[1] = pipe->fdio[1];
}

void	create_pids(t_shell *shell, t_pipe_node *pipe)
{
	int	size;

	size = lstsize_cmd(pipe);
	shell->pids = ft_calloc(sizeof(int), size);
	if (!shell->pids)
		exit(EXIT_FAILURE);
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

void	ft_dup2(t_shell *shell, int fd, int input)
{
	if (dup2(fd, input) == -1)
		exit(EXIT_FAILURE);
	(void)shell;
}

void	ft_exit_cmd(t_shell *shell, int exit_code)
{
	shell->exit = 0;
	shell->last_exit_status = exit_code;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_execution.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:20:31 by cmartino          #+#    #+#             */
/*   Updated: 2023/05/08 09:45:40 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*create_pids(t_pipe_node *pipe)
{
	int	*pids;

	pids = ft_calloc(sizeof(int), ft_lstsize_pipe(pipe));
	if (!pids)
		exit(EXIT_FAILURE);
	return (pids);
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

void	ft_dup2(t_shell *shell, int fd, int input)
{
	if (dup2(fd, input) == -1)
		exit(EXIT_FAILURE);
	(void)shell;
}

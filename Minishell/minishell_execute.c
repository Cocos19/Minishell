/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:53:01 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/18 15:35:12 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*ft_pipe(t_shell *shell)
{
	(void)shell;
	int	fd[2];

	pipe(fd);
	if (fd[0] == -1 || fd[1] == -1)
		exit(EXIT_FAILURE);
}

int	is_buitlins(char **arguments)
{
	if (ft_strcmp(arguments[0], "echo"))
	{
		if (ft_strcmp(arguments[1], "-n"))
			return (10);
		else
			return (11);
	}
	else if (ft_strcmp(arguments[0], "cd"))
		return (2);
	else if (ft_strcmp(arguments[0], "pwd"))
		return (3);
	else if (ft_strcmp(arguments[0], "export"))
		return (4);
	else if (ft_strcmp(arguments[0], "unset"))
		return (5);
	else if (ft_strcmp(arguments[0], "env"))
		return (6);
	else if (ft_strcmp(arguments[0], "exit"))
		return (7);
	return (0);
}

void	execution_pipe(t_shell *shell)
{
	int	*fd;

	fd = ft_pipe(shell);
}
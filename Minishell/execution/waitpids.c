/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpids.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:06:23 by cmartino          #+#    #+#             */
/*   Updated: 2023/05/17 11:21:33 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_waitpids(t_shell *shell, t_pipe_node *pipe)
{
	int	status;
	int	i;
	int	len;

	i = 0;
	len = ft_lstsize_pipe(pipe);
	while (i < len)
	{
		if (waitpid(shell->pids[i], &status, 0) == -1)
		{
			perror("waitpid");
			exit(WEXITSTATUS(status));
		}
		++i;
	}
}

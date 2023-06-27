/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpids.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:06:23 by cmartino          #+#    #+#             */
/*   Updated: 2023/06/27 10:55:20 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_waitpids(t_shell *shell)
{
	int	status;
	int	i;

	i = 0;
	while (i < shell->nbr_cmds)
	{
		if (waitpid(shell->pids[i], &status, 0) == -1)
		{
			perror("waitpid");
			exit(WEXITSTATUS(status));
		}
		++i;
	}
}

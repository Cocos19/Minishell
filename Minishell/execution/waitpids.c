/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpids.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:06:23 by cmartino          #+#    #+#             */
/*   Updated: 2023/06/30 12:36:52 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// quqnd shell->exit == 0 et shell->last_exit_status = 1 --> est changé dans la fonction !!!!

void	ft_waitpids(t_shell *shell)
{
	int	status;
	int	i;

	i = 0;
	while (i < shell->nbr_cmds)
	{
		waitpid(shell->pids[i], &status, 0);
		++i;
	}
	if (status == SIGINT || shell->last_exit_status == 130)
		shell->last_exit_status = EOWNER_DEAD;
	else if (status == SIGQUIT)
	{
		printf("Quit: 3\n");
		shell->last_exit_status = INTERRUPTED_BY_SIGNAL;
	}
	else
	{
		if (status != 256)
			shell->last_exit_status = status / 256;
		else
			shell->last_exit_status = 0;
	}
	shell->nbr_cmds = lstsize_cmd(shell->pipe_lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_open_close.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:35:04 by cmartino          #+#    #+#             */
/*   Updated: 2023/07/04 13:21:00 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_close(int fd, char *msg)
{
	if (close(fd) == -1)
	{
		perror(msg);
	}
}

void	ft_close_parent(int pos, t_pipe_node *cmd, t_shell *shell)
{
	if (cmd->iofiles[0] == 1)
		ft_close(cmd->fdio[0], 0);
	if (cmd->iofiles[1] == 1)
		ft_close(cmd->fdio[1], "8");
	if (shell->nbr_cmds <= 1)
		return ;
	if (pos == 0)
		ft_close(shell->pipefd[0][1], 0);
	else if (pos > 0 && pos == shell->nbr_cmds - 1)
		ft_close(shell->pipefd[shell->nbr_cmds - 2][0], 0);
	else if (pos > 0 && pos < shell->nbr_cmds - 1)
	{
		ft_close(shell->pipefd[pos - 1][0], 0);
		ft_close(shell->pipefd[pos][1], 0);
	}
}

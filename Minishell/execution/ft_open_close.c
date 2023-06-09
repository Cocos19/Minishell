/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:00:10 by cmartino          #+#    #+#             */
/*   Updated: 2023/07/04 14:35:18 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	next_file(t_redir_datas	*temp_lst, int fd, char *value, char type)
{
	while (temp_lst)
	{
		temp_lst = temp_lst->next;
		if (temp_lst)
		{
			if (temp_lst->type == type)
			{
				ft_close(fd, value);
				temp_lst = temp_lst->last;
			}
		}
	}
}

void	quit_open_close(t_shell *shell, int io)
{
	shell->exit = 2;
	shell->last_exit_status = 1;
	shell->pipe_lst->iofiles[io] = 0;
}

void	openiofile(t_shell *shell, t_pipe_node *pipe, t_redir_datas *files)
{
	if (files->type == 'i' && shell->exit == 1)
	{
		if (files->mode == 2)
		{
			pipe->fdio[0] = get_heredoc(shell, files->value);
			if (shell->last_exit_status == 130)
				shell->exit = 0;
		}
		else
			pipe->fdio[0] = ft_open_infile(shell, files);
		if (pipe->fdio[0] == -1)
			return (quit_open_close(shell, 0));
		pipe->iofiles[0] = 1;
	}
	if (files->type == 'o' && shell->exit == 1)
	{
		pipe->fdio[1] = ft_open_outfile(shell, files);
		if (pipe->fdio[1] == -1)
			return (quit_open_close(shell, 1));
		pipe->iofiles[1] = 1;
	}
	if (files->next && shell->exit == 1)
		openiofile(shell, pipe, files->next);
}

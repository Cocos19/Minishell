/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:00:10 by cmartino          #+#    #+#             */
/*   Updated: 2023/06/30 12:37:15 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	next_file(t_redir_datas	*temp_lst, int fd, char *value, char type)
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

int	ft_open_infile(t_shell *shell, t_redir_datas *input_lst)
{
	int				fd;
	t_redir_datas	*temp_lst;

	temp_lst = input_lst;
	fd = open(input_lst->value, O_RDONLY);
	if (fd == -1)
	{
		perror(input_lst->value);
		ft_exit_cmd(shell, 127);
	}
	next_file(temp_lst, fd, input_lst->value, 'i');
	return (fd);
}

int	ft_open_outfile(t_shell *shell, t_redir_datas *output_lst)
{
	int				fd;
	t_redir_datas	*temp_lst;

	temp_lst = output_lst;
	if (output_lst->mode == 1)
		fd = open(output_lst->value,
				O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	else
	{
		fd = open(output_lst->value,
				O_WRONLY | O_APPEND | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	}
	if (fd == -1)
	{
		perror(output_lst->value);
		ft_exit_cmd(shell, 127);
	}
	next_file(temp_lst, fd, output_lst->value, 'o');
	return (fd);
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
		{
			shell->exit = 2;
			shell->last_exit_status = 1;
			return ;
		}
		pipe->iofiles[0] = 1;
	}
	if (files->type == 'o' && shell->exit == 1)
	{
		pipe->fdio[1] = ft_open_outfile(shell, files);
		if (pipe->fdio[1] == -1)
		{
			shell->exit = 2;
			shell->last_exit_status = 1;
			return ;
		}
		pipe->iofiles[1] = 1;
	}
	if (files->next && shell->exit == 1)
		openiofile(shell, pipe, files->next);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_open_close.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:35:04 by cmartino          #+#    #+#             */
/*   Updated: 2023/05/17 09:55:04 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_infiles(t_shell *shell, t_pipe_node *pipe)
{
	int	fd;

	(void)shell;
	while (pipe->input_file_lst->next)
	{
		fd = open(pipe->input_file_lst->value, O_RDONLY);
		if (fd == -1)
			perror(pipe->input_file_lst->value);
		if (pipe->input_file_lst->next)
			ft_close_files(fd, pipe->input_file_lst->value);
		pipe->input_file_lst = pipe->input_file_lst->next;
	}
	fd = open(pipe->input_file_lst->value, O_RDONLY);
	if (fd == -1)
		perror(pipe->input_file_lst->value);
	if (pipe->input_file_lst->next)
		ft_close_files(fd, pipe->input_file_lst->value);
	return (fd);
}

int	ft_open_outfiles(t_shell *shell, t_pipe_node *pipe)
{
	int	fd;

	(void)shell;
	while (pipe->output_file_lst)
	{
		if (pipe->output_file_lst->mode == 1)
			fd = open(pipe->output_file_lst->value, O_WRONLY | O_CREAT | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		else
			fd = open(pipe->output_file_lst->value, O_WRONLY | O_APPEND | O_CREAT,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		pipe->output_file_lst = pipe->output_file_lst->next;
	}
	if (fd == -1)
		perror(pipe->output_file_lst->value);
	return (fd);
}

void	ft_close_files(int fd, char *name)
{
	if (close(fd) == -1)
		perror(name);	// a voir quelle erreur a renvoyer + exit_code ?
}

void	ft_close(int fd)
{
	if (close(fd) == -1)
		perror(NULL);	//quelle erreur ? 
}


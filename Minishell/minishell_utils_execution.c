/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_execution.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:20:31 by cmartino          #+#    #+#             */
/*   Updated: 2023/05/10 13:29:30 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pids(t_shell *shell, t_pipe_node *pipe)
{
	int	size;
	int	i;

	size = ft_lstsize_pipe(pipe);
	shell->pids = ft_calloc(sizeof(int), size);
	if (!shell->pids)
		exit(EXIT_FAILURE);
	i = 0;
}

void ft_pipe(t_shell *shell, t_pipe_node *pip)
{	
	pipe(pip->fd);
	if (pip->fd[0] == -1 || pip->fd[1] == -1)
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
		printf("test\n");
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
		perror(name);	// a voir quelle erreur a renvoyer + exit ?
}

void	ft_close(int fd)
{
	if (close(fd) == -1)
		perror(NULL);	//quelle erreur ? 
}

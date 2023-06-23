/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_open_close.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:35:04 by cmartino          #+#    #+#             */
/*   Updated: 2023/06/23 14:28:12 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	ft_open_infiles(t_shell *shell, t_pipe_node *pipe)
// {
// 	int	fd;

// 	(void)shell;
// 	while (pipe->input_file_lst->next)
// 	{
// 		fd = open(pipe->input_file_lst->value, O_RDONLY);
// 		if (fd == -1)
// 			perror(pipe->input_file_lst->value);
// 		if (pipe->input_file_lst->next)
// 			ft_close_files(fd, pipe->input_file_lst->value);
// 		pipe->input_file_lst = pipe->input_file_lst->next;
// 	}
// 	fd = open(pipe->input_file_lst->value, O_RDONLY);
// 	if (fd == -1)
// 		perror(pipe->input_file_lst->value);
// 	if (pipe->input_file_lst->next)
// 		ft_close_files(fd, pipe->input_file_lst->value);
// 	return (fd);
// }

// int	ft_open_outfiles(t_shell *shell, t_pipe_node *pipe)
// {
// 	int	fd;

// 	(void)shell;
// 	while (pipe->output_file_lst)
// 	{
// 		if (pipe->output_file_lst->mode == 1)
// 			fd = open(pipe->output_file_lst->value,
// 					O_WRONLY | O_CREAT | O_TRUNC,
// 					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
// 		else
// 			fd = open(pipe->output_file_lst->value,
// 					O_WRONLY | O_APPEND | O_CREAT,
// 					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
// 		pipe->output_file_lst = pipe->output_file_lst->next;
// 	}
// 	if (fd == -1)
// 		perror(pipe->output_file_lst->value);
// 	return (fd);
// }

int	ft_open_infiles(t_shell *shell, t_pipe_node *pipe)	//tjrs utilisée? 
{
	int				fd;
	t_file_datas	*input_lst;

	(void)shell;
	input_lst = pipe->input_file_lst;
	while (input_lst->next)
	{
		fd = open(input_lst->value, O_RDONLY);
		if (fd == -1)
			perror(input_lst->value);
		if (input_lst->next)
			ft_close_files(fd, input_lst->value);
		input_lst = input_lst->next;
	}
	fd = open(input_lst->value, O_RDONLY);
	if (fd == -1)
		perror(input_lst->value);
	if (input_lst->next)
		ft_close_files(fd, input_lst->value);
	return (fd);
}

int	ft_open_infile(t_shell *shell, t_redir_datas *input_lst)
{
	int				fd;
	t_redir_datas	*temp_lst;

	temp_lst = input_lst;
	if (input_lst->mode == 1)
	{
		// printf("rentre\n");
		fd = open(input_lst->value, O_RDONLY);
		// printf("fd = %d\n", fd);
	}
	else
	{
		printf("heredoc -> to do\n");
		exit(0);
	}
	if (fd == -1)
	{
		perror(input_lst->value);
		ft_exit_cmd(shell, 127);	// a voir avec bash upgrade
	}
	while(temp_lst->next)
	{
		temp_lst = temp_lst->next;
		if (temp_lst->type == 'i')
		{
			ft_close_files(fd, input_lst->value);
			temp_lst = temp_lst->last;
		}
	}
	return (fd);
}

int	ft_open_outfile(t_shell *shell, t_redir_datas *output_lst)
{
	int				fd;
	t_redir_datas	*temp_lst;

	temp_lst = output_lst;
	// printf("output lst mode = %d\n", output_lst->mode);
	if (output_lst->mode == 1)
		fd = open(output_lst->value,
				O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	else
	{
		fd = open(output_lst->value,
				O_WRONLY | O_APPEND | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		// printf(" ici + fd = %d\n", fd);
	}
	if (fd == -1)
	{
		perror(output_lst->value);
		ft_exit_cmd(shell, 127);	// a voir avec bash upgrade
	}
	while(temp_lst->next)
	{
		temp_lst = temp_lst->next;
		if (temp_lst->type == 'o')
		{
			ft_close_files(fd, output_lst->value);
			temp_lst = temp_lst->last;
		}
	}
	return (fd);
}

int	ft_open_outfiles(t_shell *shell, t_pipe_node *pipe)
{
	int				fd;
	t_file_datas	*output_lst;

	(void)shell;
	output_lst = pipe->output_file_lst;
	while (output_lst)
	{
		if (output_lst->mode == 1)
			fd = open(output_lst->value,
					O_WRONLY | O_CREAT | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		else
			fd = open(output_lst->value,
					O_WRONLY | O_APPEND | O_CREAT,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		output_lst = output_lst->next;
	}
	if (fd == -1)
		perror(output_lst->value);
	return (fd);
}

void	ft_close_files(int fd, char *name)
{
	if (close(fd) == -1)
	{
		perror(name);
		//exit?
	}
}

/* ft_close_files : // a voir quelle erreur a renvoyer + exit_code ?
	ft_close : quelle erreur renvoyer ? */

void	ft_close(int fd)
{
	if (close(fd) == -1)
	{
		perror(NULL);
	}
}

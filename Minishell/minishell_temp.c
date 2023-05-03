/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_temp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:34:18 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/02 14:29:01 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_list_infos(t_token *lst)
{
	t_token	*temp;

	temp = lst;
	while (temp)
	{
		if (temp->value)
			printf("token is:%s\n", temp->value);
		temp = temp->next;
	}
}

void	print_fd_content(int fd)
{
	char	*str;

	str = get_next_line(fd, 10);
	while (str)
	{
		printf("%s", str);
		free(str);
		str = get_next_line(fd, 10);
	}
	close(fd);
}

void	print_file_datas_lst(t_file_datas *datas_lst)
{
	t_file_datas *lst;
	int	i;

	lst = datas_lst;
	i = 0;
	while (lst)
	{
		printf("File %d\n mode: %d\n value: %s\n", ++i, lst->mode, lst->value);
		lst = lst->next;
	}
}

void	print_pipe_lst_content(t_pipe_node *pipe_lst)
{
	t_pipe_node	*current;
	int			i;

	current = pipe_lst;
	i = -1;
	while (current)
	{
		if (current->arguments)
		{
			while (current->arguments[++i])
				printf("argv[%d]: %s\n", i, current->arguments[i]);
			i = -1;
		}
		if (current->input_lst)
		{
			printf("Input file list:\n");
			print_file_datas_lst(current->input_lst);
		}
		if (current->output_lst)
		{
			printf("Output file list:\n");
			print_file_datas_lst(current->output_lst);
		}
		current = current->next;
	}
}

// int	open_input_file(t_shell *shell, t_token *current_token)
// {
// 	int	fd;

// 	fd = open(current_token->next->value, O_RDONLY);
// 	if (fd == -1)
// 		update_exit_status_with_errno(shell);
// 	else
// 		shell_fd_control(shell, '+', 1);
// 	return (fd);
// }

// int	open_output_file(t_shell *shell, t_token *current_token)
// {
// 	int	fd;

// 	if (current_token->value[1] == '\0')
// 	{
// 		shell_fd_control(shell, '+', 1);
// 		fd = open(current_token->next->value, O_WRONLY | O_APPEND | O_CREAT,
// 				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
// 		if (fd == -1)
// 			update_exit_status_with_errno(shell);
// 	}
// 	else
// 	{
// 		shell_fd_control(shell, '+', 1);
// 		fd = open(current_token->next->value, O_WRONLY | O_APPEND | O_CREAT,
// 				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
// 		if (fd == -1)
// 			update_exit_status_with_errno(shell);
// 	}
// 	return (fd);
// }

	// if (token->value[1] == '\0')
	// 	fd = open_input_file(shell, token);
	// else
	// {
	// 	fd = get_heredoc(shell, token->next->value);
	// 	if (g_exit_status != 0)
	// 	{
	// 		export(shell, "?=130");
	// 		return (NULL);
	// 	}
	// }
	// if (node->input_file_fd != -1)
	// 	close_fd(shell, node->input_file_fd);
	// node->input_file_fd = fd;

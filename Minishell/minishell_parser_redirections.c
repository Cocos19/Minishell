/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_redirections.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:02:15 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/20 15:03:07 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_input_file(t_shell *shell, t_token *current_token)
{
	int fd;

	//acces test the fd, if not trow error update ?var and return -1;
	fd = open(current_token->next->value, O_RDONLY);
	if (fd == -1)
	{
		printf("minishell: %s: No such file or directory\n", current_token->next->value);
		export(shell, "?=1");
	}
	else
		shell_fd_control(shell, '+', 1);
	return (fd);
}

int	open_output_file(t_shell *shell, t_token *current_token)
{
	int fd;

	if (current_token->value[1] == '\0')
	{
		shell_fd_control(shell, '+', 1);
		fd = open(current_token->next->value, O_WRONLY | O_APPEND | O_CREAT,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (fd == -1)
			free_and_print_strerror(shell);
	}
	else
	{
		shell_fd_control(shell, '+', 1);
		fd = open(current_token->next->value, O_WRONLY | O_APPEND | O_CREAT,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (fd == -1)
			free_and_print_strerror(shell);
	}
	return (fd);
}

t_token *get_input(t_shell *shell, t_pipe_node *current_node, t_token *current_token)
{
	int	fd;

	if (!current_token->next)
	{
		printf("minishell: syntax error near unexpected token `newline'");
		return (NULL);
	}
	if (current_token->value[1] == '\0')
		fd = open_input_file(shell, current_token);
	else
	{
		fd = get_heredoc(shell, current_token->next->value);
		if (g_exit_status != 0)
		{
			export(shell, "?=130");
			return (NULL);
		}
	}
	if (current_node->input_file_fd != -1)
		close_fd(shell, current_node->input_file_fd);
	current_node->input_file_fd = fd;
	return (current_token->next);
}

t_token *get_output(t_shell *shell, t_pipe_node *current_node, t_token *current_token)
{
	int	fd;

	if (!current_token->next)
	{
		printf("minishell: syntax error near unexpected token `newline'");
		return (NULL);
	}
	//acces test the fd, if not trow error update ?var and return -1;
	fd = open_output_file(shell, current_token);
	if (current_node->output_file_fd != -1)
		close_fd(shell, current_node->output_file_fd);
	current_node->output_file_fd = fd;
	return (current_token->next);
}

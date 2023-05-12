/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:43:03 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/09 15:46:54 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_input_and_exit(char *input, int fd)
{
	free(input);
	close(fd);
	exit(EXIT_SUCCESS);
}

void	print_quit_error_and_exit(int count_line, char *keyword, int *fd)
{
	printf("minishell: warning: here-document at line %d ", count_line);
	printf("delimited by end-of-file (wanted '%s')\n", keyword);
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

void	get_user_input(t_shell *shell, int count_line, char *keyword, int *fd)
{
	char	*input;

	act_sint_handler(shell, &sigint_hered_h);
	while (1)
	{
		input = readline("> ");
		if (g_exit_status != 0)
			free_input_and_exit(input, fd[1]);
		if (!input)
			print_quit_error_and_exit(count_line, keyword, fd);
		if (ft_strcmp(keyword, input) != 0)
		{
			input = search_and_expand_env_var(shell, input);
			write(fd[1], input, ft_strlen(input));
			write(fd[1], "\n", 1);
			free(input);
		}
		else
			free_input_and_exit(input, fd[1]);
	}
	free_input_and_exit(input, fd[1]);
}

void	get_child_process_result_and_free_pipe(t_shell *shell, int *pipe_fds)
{
	int	wstatus;

	wait(&wstatus);
	g_exit_status = WEXITSTATUS(wstatus);
	shell->last_exit_status = g_exit_status;
	g_exit_status = 0;
	close(pipe_fds[1]);
}

int	get_heredoc(t_shell *shell, char *delimiter)
{
	int	pipe_fds[2];
	int	id;

	if (pipe(pipe_fds) == -1)
		print_str_error_and_exit();
	id = fork();
	if (id == -1)
		print_str_error_and_exit();
	if (id == 0)
	{
		close(pipe_fds[0]);
		get_user_input(shell, 0, delimiter, pipe_fds);
	}
	else
		get_child_process_result_and_free_pipe(shell, pipe_fds);
	return (pipe_fds[0]);
}

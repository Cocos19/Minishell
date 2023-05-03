/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:43:03 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/03 14:31:00 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_input_and_exit(char *input)
{
	free(input);
	exit(EXIT_SUCCESS);
}

void	get_user_input(t_shell *shell, int count_line, char *keyword, int fd)
{
	char	*input;

	act_sint_handler(shell, &sigint_hered_h);
	while (1)
	{
		input = readline("> ");
		if (g_exit_status != 0)
			free_input_and_exit(input);
		if (!input)
		{
			printf("minishell: warning: here-document at line %d ", count_line);
			printf("delimited by end-of-file (wanted '%s')\n", keyword);
			exit(EXIT_SUCCESS);
		}
		if (ft_strcmp(keyword, input) != 0)
		{
			input = search_and_expand_env_var(shell, input);
			write(fd, input, ft_strlen(input));
			write(fd, "\n", 1);
			free(input);
		}
		else
			free_input_and_exit(input);
	}
	free_input_and_exit(input);
}

void	get_child_process_result_and_free_pipe(t_shell *shell, int *pipe_fds)
{
	int	wstatus;

	wait(&wstatus);
	g_exit_status = WEXITSTATUS(wstatus);
	shell_fd_control(shell, '-', 1);
	close(pipe_fds[1]);
	free(pipe_fds);
}

int	get_heredoc(t_shell *shell, char *delimiter)
{
	int	*pipe_fds;
	int	id;
	int	fd;

	shell_fd_control(shell, '+', 2);
	pipe_fds = malloc(sizeof(int) * 2);
	if (!pipe_fds)
		free_and_print_strerror(shell);
	if (pipe(pipe_fds) == -1)
		free_and_print_strerror(shell);
	fd = pipe_fds[0];
	id = fork();
	if (id == -1)
		free_and_print_strerror(shell);
	if (id == 0)
		get_user_input(shell, 0, delimiter, pipe_fds[1]);
	else
		get_child_process_result_and_free_pipe(shell, pipe_fds);
	return (fd);
}

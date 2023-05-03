/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer_checker.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:12:58 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/03 14:31:12 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_list_is_valid(t_shell *shell)
{
	if (shell->token_lst->last->value[0] == '|')
		return (1);
	return (0);
}

void	give_pipe_prompt(t_shell *shell, int fd)
{
	char	*input;

	act_sint_handler(shell, &sigint_hered_h);
	input = readline("pipe> ");
	if (!input)
		exit(130);
	write(fd, input, ft_strlen(input));
	free(input);
	exit (EXIT_SUCCESS);
}

void	get_pipe_prompt_result_and_free_pipe(t_shell *shell, int *pipe_fds)
{
	int	wstatus;

	wait(&wstatus);
	g_exit_status = WEXITSTATUS(wstatus);
	close(pipe_fds[1]);
	shell_fd_control(shell, '-', 1);
	free(pipe_fds);
}

int	get_pipe_input(t_shell *shell)
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
		give_pipe_prompt(shell, pipe_fds[1]);
	else
		get_pipe_prompt_result_and_free_pipe(shell, pipe_fds);
	if (g_exit_status != 0)
	{
		close(fd);
		--shell->fd_opened;
		fd = -1;
	}
	return (fd);
}

void	complete_token(t_shell *shell)
{
	char	*new_input;
	int		fd;
	t_token	*add_to_token_lst;

	fd = get_pipe_input(shell);
	if (fd != -1)
	{
		new_input = get_string_from_fd(shell, fd);
		shell_fd_control(shell, '-', 1);
		close(fd);
		--shell->fd_opened;
		if (new_input)
		{
			add_to_token_lst = tokenize(shell, new_input);
			shell->token_lst->last->next = add_to_token_lst;
			shell->token_lst->last = shell->token_lst->last->next->last;
		}
	}
}

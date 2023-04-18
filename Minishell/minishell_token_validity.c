/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_validity.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:12:58 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/17 14:39:01 by mprofett         ###   ########.fr       */
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

	activate_sigint_handler(shell, &sigint_hered_handler);
	input = readline("pipe> ");
	if (!input)
		exit(130);
	write(fd, input, ft_strlen(input));
	free_input_and_exit(input);
}

void	get_pipe_prompt_result_and_free_pipe(int *pipe_fds)
{
	int	wstatus;

	wait(&wstatus);
	g_exit_status = WEXITSTATUS(wstatus);
	close(pipe_fds[1]);
	free(pipe_fds);
}

int get_pipe_input(t_shell *shell)
{
	int *pipe_fds;
	int	id;
	int fd;

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
		get_pipe_prompt_result_and_free_pipe(pipe_fds);
	if (g_exit_status != 0)
	{
		close(fd);
		fd = -1;
	}
	return (fd);
}

void	complete_token(t_shell *shell)
{
	char 	*new_input;
	int		fd;
	t_token *add_to_token_lst;

	fd = get_pipe_input(shell);
	if (fd != -1)
	{
		new_input = get_next_line(fd, 100);
		close(fd);
		add_to_token_lst = tokenize(shell, new_input);
		shell->token_lst->last->next = add_to_token_lst;
		shell->token_lst->last = shell->token_lst->last->next->last;
	}
}

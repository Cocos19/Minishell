/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:12:58 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/29 12:11:33 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	token_list_is_valid(t_shell *shell)
{
	if (shell->token_lst->last->value[0] == '|')
		return (1);
	return (0);
}

// void	give_pipe_prompt(t_shell *shell, int *fd)
void	give_pipe_prompt(int *fd)
{
	char	*input;

	close(fd[0]);
	// act_sint_handler(shell, &sigint_hered_h);
	input = readline("pipe> ");
	if (!input)
		exit(130);
	write(fd[1], input, ft_strlen(input));
	free(input);
	exit (EXIT_SUCCESS);
}

void	get_pipe_prompt_result_and_free_pipe(int *pipe_fds)
{
	int	wstatus;

	wait(&wstatus);
	g_exit_status = WEXITSTATUS(wstatus);
	close(pipe_fds[1]);
}

int	get_pipe_input(void)
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
		activate_signals(HEREDOC_MODE);
		give_pipe_prompt(pipe_fds);
	}
	else
		get_pipe_prompt_result_and_free_pipe(pipe_fds);
	if (g_exit_status != 0)
	{
		close(pipe_fds[0]);
		pipe_fds[0] = -1;
	}
	return (pipe_fds[0]);
}

void	complete_token(t_shell *shell)
{
	char	*new_input;
	int		fd;
	t_token	*add_to_token_lst;

	fd = get_pipe_input();
	shell->last_exit_status = g_exit_status;
	g_exit_status = 0;
	if (fd != -1)
	{
		new_input = get_string_from_fd(fd);
		close(fd);
		if (new_input)
		{
			add_to_token_lst = tokenize(new_input);
			shell->token_lst->last->next = add_to_token_lst;
			shell->token_lst->last = shell->token_lst->last->next->last;
		}
	}
}

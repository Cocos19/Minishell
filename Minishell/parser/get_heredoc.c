/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:43:03 by mprofett          #+#    #+#             */
/*   Updated: 2023/07/03 14:09:48 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_input_and_exit(char *input, int *redir)
{
	free(input);
	close(redir[1]);
	exit(EXIT_SUCCESS);
}

void	print_error_and_exit(int line, char *keyword, int *redir)
{
	printf("minishell: warning: here-document at line %d ", line);
	printf("delimited by end-of-file (wanted '%s')\n", keyword);
	close(redir[1]);
	exit(EXIT_SUCCESS);
}

void	get_user_input(t_shell *shell, char *keyword, int *redir)
{
	char	*input;
	int		line;

	line = 0;
	while (1)
	{
		input = readline("> ");
		if (g_exit_status != 0)
			free_input_and_exit(input, redir);
		if (!input)
			print_error_and_exit(line, keyword, redir);
		if (ft_strcmp(keyword, input) != 0)
		{
			input = search_and_expand_env_var(shell, input);
			write(redir[1], input, ft_strlen(input));
			write(redir[1], "\n", 1);
			free(input);
			++line;
		}
		else
			free_input_and_exit(input, redir);
	}
}

void	get_child_result(t_shell *shell, int *redir)
{
	int		wstatus;

	close(redir[1]);
	wait(&wstatus);
	g_exit_status = WEXITSTATUS(wstatus);
	shell->last_exit_status = g_exit_status;
	g_exit_status = 0;
}

int	get_heredoc(t_shell *shell, char *delimiter)
{
	int	redir[2];
	int	id;

	if (pipe(redir) == -1)
		print_str_error_and_exit();
	id = fork();
	if (id == -1)
		print_str_error_and_exit();
	if (id == 0)
	{
		close(redir[0]);
		activate_signals(HEREDOC_MODE);
		get_user_input(shell, delimiter, redir);
	}
	else
		get_child_result(shell, redir);
	return (redir[0]);
}

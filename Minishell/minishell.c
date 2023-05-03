/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:02:04 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/03 14:37:21 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_prompt(t_shell *shell)
{
	char	*user_input;

	user_input = give_prompt(shell);
	if (input_is_valid(shell) == 0)
	{
		desact_sint_handler(shell);
		desact_squit_handler(shell);
		act_vquit(shell);
		add_history(user_input);
		lexer(shell, user_input);
		parser(shell);
		if (shell->pipe_lst)
			print_pipe_lst_content(shell->pipe_lst);
		// TEMPORARY SHOULD BE REPLACED BY
		//if(t_pipe_node *result) ->execution function that return an exit code
		free_pipe_lst(shell);
		act_sint_handler(shell, &sigint_shell_h);
		act_squit_handler(shell, &sigquit_shell_h);
		desact_vquit(shell);
	}
	g_exit_status = 0;
	free(shell->input);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		free_and_print_strerror(shell);
	g_exit_status = 0;
	init_terminal(shell, envp);
	while (1)
		read_prompt(shell);
	free_shell(shell);
	(void) argc;
	(void) argv;
	return (0);
}

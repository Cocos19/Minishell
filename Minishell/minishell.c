/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:02:04 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/14 13:50:04 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_prompt(t_shell *shell)
{
	char	*user_input;

	user_input = readline(shell->name);
	shell->input = user_input;
	if (!user_input)
		free_and_print_custom_message(shell, "\bexit\n");
	if (input_is_valid(shell) == 0)
	{
		activate_sigint_handler(shell, &sigint_handler_off);
		activate_vquit(shell);
		add_history(user_input);
		shell->token_lst = tokenize(shell, user_input);
		/* PARSE TOKEN FUNCTION MISSING - A function which will if shell->token lst return a t_pipe_node list will be there */
		/* TEMPORARY SHOULD BE REPLACED BY if(t_pipe_node *result) ->execution function*/
		if (shell->token_lst)
		{
			print_token_list_infos(shell->token_lst);
			free_token_lst(shell->token_lst);
			shell->token_lst = NULL;
		}
		/* TEMPORARY SHOULD BE REPLACED BY if(result) ->execution function*/
		activate_sigint_handler(shell, &sigint_shell_handler);
		desactivate_vquit(shell);
	}
	update_exit_status_variable(shell);
	g_exit_status = 0;
	free(shell->input);
}

int	main(void)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		free_and_print_strerror(shell);
	g_exit_status = 0;
	init_terminal(shell);
	/* A GET ENVIRONNEMENT VARIABLE FUNCTION IS MISSING*/
	while (1)
		read_prompt(shell);
	free_shell(shell);
	return (0);
}

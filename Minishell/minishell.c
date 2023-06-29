/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:02:04 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/29 10:20:27 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_prompt(t_shell *shell)
{
	char	*user_input;

	user_input = give_prompt(shell);
	if (user_input && input_is_valid(shell) == 0)
	{
		act_sint_handler(shell, &nosigint_shell_h);
		add_history(user_input);
		lexer(shell, user_input);
		parser(shell);
		if (shell->pipe_lst && !shell->pipe_lst->next
			&& (ft_strcmp("exit", shell->pipe_lst->arguments[0]) == 0))
			single_cmd_builtin_exit(shell, shell->pipe_lst);
		else if (shell->pipe_lst)
			execution(shell);
		free_pipe_lst(shell);
		act_sint_handler(shell, &sigint_shell_h);
	}
	g_exit_status = 0;
	free(shell->input);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		print_str_error_and_exit();
	g_exit_status = 0;
	init_shell(shell, envp);
	while (1)
		read_prompt(shell);
	(void) argc;
	(void) argv;
	return (0);
}

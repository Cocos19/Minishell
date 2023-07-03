/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:02:04 by mprofett          #+#    #+#             */
/*   Updated: 2023/07/03 14:23:43 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_environnement(t_shell *shell, char **envp)
{
	char	*temp;
	char	*new_shlvl;
	int		val;

	shell->envp = ft_strdup_array(envp);
	val = 0;
	temp = search_and_expand_env_var(shell, ft_strdup("$SHLVL"));
	if (temp[0] != '\0')
		ft_atoi(temp, &val);
	free(temp);
	temp = ft_itoa(++val);
	if (!temp)
		print_str_error_and_exit();
	new_shlvl = ft_strjoin_protected("SHLVL=", temp);
	free(temp);
	export(shell, new_shlvl);
	free(new_shlvl);
}

void	init_shell(t_shell *shell)
{
	shell->input = NULL;
	shell->token_lst = NULL;
	shell->pipe_lst = NULL;
	shell->last_exit_status = 0;
	shell->name = ft_strdup("minishell-1.0$ ");
	if (!shell->name)
		print_str_error_and_exit();
}

int	shell_has_to_be_exited(t_shell *shell)
{
	if (shell->pipe_lst && !shell->pipe_lst->next
		&& shell->pipe_lst->arguments
		&& (ft_strcmp("exit", shell->pipe_lst->arguments[0]) == 0))
		return (0);
	return (1);
}

void	read_prompt(t_shell *shell)
{
	char	*user_input;

	user_input = give_prompt(shell);
	if (g_exit_status == EOWNER_DEAD)
		shell->last_exit_status = EOWNER_DEAD;
	if (user_input && input_is_valid(shell) == 0)
	{
		lexer(shell, user_input);
		parser(shell);
		activate_signals(IGNORE_MODE);
		if (shell_has_to_be_exited(shell) == 0)
			single_cmd_builtin_exit(shell, shell->pipe_lst);
		else if (shell->pipe_lst)
			execution(shell);
		add_history(shell->input);
		activate_signals(DEFAULT_MODE);
	}
	g_exit_status = 0;
	free_pipe_lst(shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		print_str_error_and_exit();
	g_exit_status = 0;
	init_shell(shell);
	init_environnement(shell, envp);
	activate_signals(DEFAULT_MODE);
	while (1)
		read_prompt(shell);
	(void) argc;
	(void) argv;
	return (0);
}

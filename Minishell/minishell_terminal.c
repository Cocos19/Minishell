/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_terminal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:39:47 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/20 09:33:00 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	act_vquit(t_shell *shell)
{
	if (tcgetattr(0, shell->term) < 0)
		print_str_error_and_exit();
	shell->term->c_cc[VQUIT] = 1;
	if (tcsetattr(0, TCSANOW, shell->term) < 0)
		print_str_error_and_exit();
}

void	desact_vquit(t_shell *shell)
{
	if (tcgetattr(0, shell->term) < 0)
		print_str_error_and_exit();
	shell->term->c_cc[VQUIT] = 0;
	if (tcsetattr(0, TCSANOW, shell->term) < 0)
		print_str_error_and_exit();
}

void	init_shell_environnement(t_shell *shell, char **envp)
{
	char	*temp;
	char	*new_shlvl;
	int		val;

	if (!envp || !envp[0])
	{
		shell->envp = malloc(sizeof(char *));
		if (!shell->envp)
			print_str_error_and_exit();
		shell->envp[0] = NULL;
	}
	else
		shell->envp = ft_strdup_array(envp);
	temp = search_and_expand_env_var(shell, ft_strdup("$SHLVL"));
	if (temp[0] == '\0')
		val = 0;
	else
		val = ft_atoi(temp);
	free(temp);
	temp = ft_itoa(++val);
	if (!temp)
		print_str_error_and_exit();
	new_shlvl = ft_strjoin_protected("SHLVL=", temp);
	free(temp);
	export(shell, new_shlvl);
	free(new_shlvl);
}

void	init_shell_signals(t_shell *shell)
{
	shell->sigint_processing = malloc(sizeof(struct sigaction));
	if (!shell->sigint_processing)
		print_str_error_and_exit();
	shell->sigquit_processing = malloc(sizeof(struct sigaction));
	if (!shell->sigquit_processing)
		print_str_error_and_exit();
	act_sint_handler(shell, &sigint_shell_h);
	act_squit_handler(shell, &sigquit_shell_h);
}

void	init_terminal(t_shell *shell, char **envp)
{
	shell->term = malloc(sizeof(struct termios));
	if (!shell->term)
		print_str_error_and_exit();
	shell->input = NULL;
	shell->token_lst = NULL;
	shell->pipe_lst = NULL;
	shell->last_exit_status = 0;
	shell->name = ft_strdup("minishell-1.0$ ");
	if (!shell->name)
		print_str_error_and_exit();
	init_shell_environnement(shell, envp);
	init_shell_signals(shell);
	act_vquit(shell);
}

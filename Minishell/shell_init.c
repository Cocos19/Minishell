/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:39:47 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/28 11:28:06 by mprofett         ###   ########.fr       */
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

void	init_signals(t_shell *shell)
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

void	init_shell(t_shell *shell, char **envp)
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
	init_environnement(shell, envp);
	init_signals(shell);
	act_vquit(shell);
}

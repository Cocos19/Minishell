/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_terminal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:39:47 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/03 11:39:32 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	activate_vquit(t_shell *shell)
{
	if (tcgetattr(0, shell->term) < 0)
		free_and_print_strerror(shell);
	shell->term->c_cc[VQUIT] = 1;
	if (tcsetattr(0, TCSANOW, shell->term) < 0)
		free_and_print_strerror(shell);
}

void	desactivate_vquit(t_shell *shell)
{
	if (tcgetattr(0, shell->term) < 0)
		free_and_print_strerror(shell);
	shell->term->c_cc[VQUIT] = 0;
	if (tcsetattr(0, TCSANOW, shell->term) < 0)
		free_and_print_strerror(shell);
}

void	init_shell_environnement(t_shell *shell, char **envp)
{
	shell->envp = ft_strdup_array(envp);
	if (!shell->envp)
		free_and_print_strerror(shell);
	export(shell, "?=0");
}

void	init_shell_signals(t_shell *shell)
{
	shell->sigint_processing = malloc(sizeof(struct sigaction));
	if (!shell->sigint_processing)
		free_and_print_strerror(shell);
	shell->sigquit_processing = malloc(sizeof(struct sigaction));
	if (!shell->sigquit_processing)
		free_and_print_strerror(shell);
	activate_sint_handler(shell, &sigint_shell_handler);
	activate_squit_handler(shell, &sigquit_shell_handler);
}

void	init_terminal(t_shell *shell, char **envp)
{
	shell->term = malloc(sizeof(struct termios));
	if (!shell->term)
		free_and_print_strerror(shell);
	shell->envp = NULL;
	shell->input = NULL;
	shell->token_lst = NULL;
	shell->pipe_lst = NULL;
	shell->fd_opened = 0;
	shell->name = ft_strdup("minishell-1.0$ ");
	if (!shell->name)
		free_and_print_strerror(shell);
	init_shell_environnement(shell, envp);
	init_shell_signals(shell);
	activate_vquit(shell);
	(void) envp;
}

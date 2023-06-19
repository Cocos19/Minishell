/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals_activation.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:20:38 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/19 09:56:33 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	act_sint_handler(t_shell *shell, void f(int, siginfo_t *, void *))
{
	shell->sigint_processing->sa_sigaction = f;
	shell->sigint_processing->sa_flags = 0;
	shell->sigint_processing->sa_mask = 0;
	if (sigaction(SIGINT, shell->sigint_processing, NULL) == -1)
		print_str_error_and_exit();
}

void	desact_sint_handler(t_shell *shell)
{
	shell->sigint_processing->sa_handler = SIG_DFL;
	if (sigaction(SIGINT, shell->sigint_processing, NULL) == -1)
		print_str_error_and_exit();
}

void	act_squit_handler(t_shell *shell, void f(int, siginfo_t *, void *))
{
	shell->sigquit_processing->sa_sigaction = f;
	shell->sigquit_processing->sa_flags = 0;
	shell->sigquit_processing->sa_mask = 0;
	if (sigaction(SIGQUIT, shell->sigquit_processing, NULL) == -1)
		print_str_error_and_exit();
}

void	desact_squit_handler(t_shell *shell)
{
	shell->sigquit_processing->sa_handler = SIG_DFL;
	if (sigaction(SIGQUIT, shell->sigquit_processing, NULL) == -1)
		print_str_error_and_exit();
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals_activation.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:20:38 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/24 15:24:14 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	activate_sint_handler(t_shell *shell, void f(int, siginfo_t *, void *))
{
	shell->sigint_processing->sa_sigaction = f;
	if (sigaction(SIGINT, shell->sigint_processing, NULL) == -1)
		exit (EXIT_FAILURE);
}

void	desactivate_sint_handler(t_shell *shell)
{
	shell->sigint_processing->sa_handler = SIG_DFL;
	if (sigaction(SIGINT, NULL, NULL) == -1)
		exit (EXIT_FAILURE);
}

void	activate_squit_handler(t_shell *shell, void f(int, siginfo_t *, void *))
{
	shell->sigquit_processing->sa_sigaction = f;
	if (sigaction(SIGQUIT, shell->sigquit_processing, NULL) == -1)
		exit (EXIT_FAILURE);
}

void	desactivate_squit_handler(t_shell *shell)
{
	shell->sigquit_processing->sa_handler = SIG_DFL;
	if (sigaction(SIGQUIT, NULL, NULL) == -1)
		exit (EXIT_FAILURE);
}

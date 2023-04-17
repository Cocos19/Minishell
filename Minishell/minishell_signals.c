/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:42:52 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/13 18:11:40 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_shell_handler(int signal_id, siginfo_t *sig_info, void *context)
{
	if (signal_id == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	(void) sig_info;
	(void) context;
}

void	sigint_hered_handler(int signal_id, siginfo_t *sig_info, void *context)
{
	if (signal_id == SIGINT)
		exit(130);
	(void) sig_info;
	(void) context;
}

void	sigint_handler_off(int signal_id, siginfo_t *sig_info, void *context)
{
	(void) signal_id;
	(void) sig_info;
	(void) context;
}

void	activate_sigint_handler(t_shell *shell, void f(int, siginfo_t *, void *))
{
	shell->signal_processing->sa_sigaction = f;
	if (sigaction(SIGINT, shell->signal_processing, NULL) == -1)
		exit (EXIT_FAILURE);
}

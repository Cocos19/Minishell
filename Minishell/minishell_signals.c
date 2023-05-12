/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:42:52 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/09 15:58:10 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_shell_h(int signal_id, siginfo_t *sig_info, void *context)
{
	if (signal_id == SIGINT)
	{
		g_exit_status = EOWNER_DEAD;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	(void) sig_info;
	(void) context;
}

void	nosigint_shell_h(int signal_id, siginfo_t *sig_info, void *context)
{
	(void) signal_id;
	(void) sig_info;
	(void) context;
}

void	sigquit_shell_h(int signal_id, siginfo_t *sig_info, void *context)
{
	(void) signal_id;
	(void) sig_info;
	(void) context;
}

void	sigint_hered_h(int signal_id, siginfo_t *sig_info, void *context)
{
	if (signal_id == SIGINT)
		exit(EOWNER_DEAD);
	(void) sig_info;
	(void) context;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:42:52 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/30 11:40:06 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_default(int signal_id)
{
	g_exit_status = EOWNER_DEAD;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void) signal_id;
}

void	sigint_heredoc(int signal_id)
{
	exit (EOWNER_DEAD);
	(void) signal_id;
}

void	sigint_ignore(int signal_id)
{
	write(1, "\n", 1);
	(void) signal_id;
}

void	activate_signals(int mode)
{
	if (mode == DEFAULT_MODE)
	{
		signal(SIGINT, sigint_default);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == HEREDOC_MODE)
	{
		signal(SIGINT, sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == CHILD_MODE)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == IGNORE_MODE)
	{
		signal(SIGINT, sigint_ignore);
		signal(SIGQUIT, SIG_IGN);
	}
	(void) mode;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free_and_print_msg.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:12:43 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/08 10:56:33 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_print_strerror(t_shell *shell)
{
	printf("%s\n", strerror(errno));
	// free_shell(shell);
	(void) shell;
	exit (errno);
}

void	free_and_print_custom_message(t_shell *shell, char *message)
{
	write(1, message, ft_strlen(message));
	// free_shell(shell);
	(void) shell;
	exit (g_exit_status);
}

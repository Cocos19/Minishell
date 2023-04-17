/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_terminal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:39:47 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/14 13:47:06 by mprofett         ###   ########.fr       */
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

void	init_terminal(t_shell *shell)
{
	shell->term = malloc(sizeof(struct termios));
	if (!shell->term)
		free_and_print_strerror(shell);
	shell->envp = NULL;
	shell->input = NULL;
	shell->token_lst = NULL;
	shell->varloc_list = NULL;
	add_new_locale_variable(shell, ft_strdup("?"), ft_strdup("0"));
	if (shell->varloc_list->name == NULL || shell->varloc_list->value == NULL)
		free_and_print_strerror(shell);
	shell->name = ft_strdup("minishell-1.0$ ");
	if (!shell->name)
		free_and_print_strerror(shell);
	shell->signal_processing = malloc(sizeof(struct sigaction));
	if (!shell->signal_processing)
		free_and_print_strerror(shell);
	activate_sigint_handler(shell, &sigint_shell_handler);
	activate_vquit(shell);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_local_variables.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:46:52 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/14 13:27:46 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_locale_variable(t_shell *shell, char *name, char *value)
{
	t_local_var	*new;

	new = malloc(sizeof(t_local_var));
	if (!new)
		free_and_print_strerror(shell);
	new->name = name;
	new->value = value;
	if (shell->varloc_list)
		shell->varloc_list->last->next = new;
	else
		shell->varloc_list = new;
	shell->varloc_list->last = new;
	shell->varloc_list->next = NULL;
}

void	update_exit_status_variable(t_shell *shell)
{
	free(shell->varloc_list->value);
	shell->varloc_list->value = ft_strdup(ft_itoa(g_exit_status));
}

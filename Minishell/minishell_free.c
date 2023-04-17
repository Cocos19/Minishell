/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:45:35 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/14 14:48:05 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_locales_variables_list(t_local_var *lst)
{
	t_local_var	*temp;

	temp = lst->next;
	while (lst)
	{
		free(lst);
		lst = temp;
		if (lst)
			temp = lst->next;
	}
}

void	free_shell(t_shell *shell)
{
	if (shell->envp)
		shell->envp= ft_free_str_array(shell->envp);
	if (shell->varloc_list)
		free_locales_variables_list(shell->varloc_list);
	if (shell->token_lst)
		free_token_lst(shell->token_lst);
	if (shell->term)
	{
		activate_vquit(shell);
		free(shell->term);
	}
	if (shell->signal_processing)
		free(shell->signal_processing);
	if (shell->name)
		free(shell->name);
	if (shell->input)
		free(shell->input);
	if (shell)
		free(shell);
}

void	free_node(t_pipe_node *node)
{
	t_pipe_node *temp;

	temp = node->next;
	while (node)
	{
		if (node->arguments)
			ft_free_str_array(node->arguments);
		if (node->temp_varlist)
			free_locales_variables_list(node->temp_varlist);
		free(node);
		node = temp;
		if (node)
			temp = node->next;
	}
}

void	free_token_lst(t_token *lst)
{
	t_token *temp;

	if (lst)
	{
		temp = lst;
		while (lst)
		{
			if (lst->value)
				free(lst->value);
			temp = lst->next;
			free(lst);
			lst = temp;
		}
	}
}

void	free_and_print_strerror(t_shell *shell)
{
	printf("%s\n", strerror(errno));
	free_shell(shell);
	exit (errno);
}

void	free_and_print_custom_message(t_shell *shell, char *message)
{
	write(1, message, ft_strlen(message));
	free_shell(shell);
	exit (g_exit_status);
}

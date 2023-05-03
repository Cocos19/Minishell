/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:45:35 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/03 15:11:10 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *shell)
{
	if (shell->envp)
		ft_free_str_array(shell->envp);
	if (shell->token_lst)
		free_token_lst(shell);
	if (shell->term)
	{
		act_vquit(shell);
		free(shell->term);
	}
	if (shell->sigint_processing)
		free(shell->sigint_processing);
	if (shell->sigquit_processing)
		free(shell->sigquit_processing);
	if (shell->name)
		free(shell->name);
	if (shell->input)
		free(shell->input);
	if (shell)
		free(shell);
}

void	free_file_datas_list(t_file_datas *lst)
{
	t_file_datas	*temp;

	while (lst)
	{
		temp = lst->next;
		if (lst->value)
			free(lst->value);
		lst = temp;
	}
}

void	free_pipe_lst(t_shell *shell)
{
	t_pipe_node	*temp;

	while (shell->pipe_lst)
	{
		if (shell->pipe_lst->arguments)
			shell->pipe_lst->arguments
				= ft_free_str_array(shell->pipe_lst->arguments);
		if (shell->pipe_lst->input_file_lst)
			free_file_datas_list(shell->pipe_lst->input_file_lst);
		if (shell->pipe_lst->output_file_lst)
			free_file_datas_list(shell->pipe_lst->output_file_lst);
		temp = shell->pipe_lst->next;
		free(shell->pipe_lst);
		shell->pipe_lst = temp;
	}
}

void	free_token_lst(t_shell *shell)
{
	t_token	*temp;

	if (shell->token_lst)
	{
		while (shell->token_lst)
		{
			if (shell->token_lst->value)
				free(shell->token_lst->value);
			temp = shell->token_lst->next;
			free(shell->token_lst);
			shell->token_lst = temp;
		}
		shell->token_lst = NULL;
	}
}

t_token	*free_token_lst_without_content(t_token *lst)
{
	t_token	*temp;

	if (lst)
	{
		while (lst)
		{
			temp = lst->next;
			free(lst);
			lst = temp;
		}
	}
	return (NULL);
}

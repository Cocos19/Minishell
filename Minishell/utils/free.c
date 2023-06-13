/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:45:35 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/05 13:53:35 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	free_all_tab(char **p_tab, int len)
{
	int	i;

	i = 0;
	while (p_tab && i < len && p_tab[i])
	{
		free(p_tab[i]);
		p_tab[i] = NULL;
		++i;
	}
	free(p_tab);
	p_tab = NULL;
}

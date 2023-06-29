/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:45:35 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/29 12:34:26 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_shell(t_shell *shell)
{
	if (shell->envp)
		ft_free_str_array(shell->envp);
	if (shell->token_lst)
		free_token_lst(shell);
	if (shell->name)
		free(shell->name);
	if (shell->input)
		free(shell->input);
	if (shell)
		free(shell);
}

void	free_redir_datas_list(t_redir_datas *lst)
{
	t_redir_datas	*temp;

	while (lst)
	{
		temp = lst->next;
		if (lst->value)
			free(lst->value);
		free(lst);
		lst = temp;
	}
	lst = NULL;
}

void	free_pipe_lst(t_shell *shell)
{
	t_pipe_node	*temp;

	while (shell->pipe_lst)
	{
		if (shell->pipe_lst->arguments)
			shell->pipe_lst->arguments
				= ft_free_str_array(shell->pipe_lst->arguments);
		if (shell->pipe_lst->in_out_redir_list)
			free_redir_datas_list(shell->pipe_lst->in_out_redir_list);
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

void	ft_free_execution(t_shell *shell)
{
	t_pipe_node	*cmd;

	cmd = shell->pipe_lst;
	if (shell->pipefd)
		ft_free_all(shell->pipefd, shell->nbr_cmds);
	while (cmd->path)
	{
		free(cmd->path);
		cmd = cmd->next;
	}
	if (cmd->pids)
		free(cmd->pids);
	if (shell->pids)
		free(shell->pids);
}

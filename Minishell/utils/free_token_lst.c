/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:45:35 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/05 13:53:35 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

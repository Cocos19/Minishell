/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_arguments.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:17:49 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/24 15:29:24 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_arg(t_shell *shell, t_token *arg_list, t_token *token)
{
	t_token	*result;

	result = init_token(shell);
	result->value = expander(shell, token->value);
	if (!arg_list)
	{
		arg_list = result;
		arg_list->last = result;
	}
	else
	{
		arg_list->last->next = result;
		arg_list->last = result;
	}
	return (arg_list);
}

int	get_token_list_size(t_token *lst)
{
	t_token	*temp;
	int		i;

	temp = lst;
	i = 0;
	while (temp)
	{
		++i;
		temp = temp->next;
	}
	return (i);
}

char	**init_argument_array(t_shell *shell, t_token *arg_list)
{
	char	**result;
	t_token	*lst;
	int		i;

	result = malloc(sizeof(char *) * get_token_list_size(arg_list) + 1);
	if (!result)
		free_and_print_strerror(shell);
	lst = arg_list;
	i = -1;
	while (lst)
	{
		result[++i] = ft_strdup(lst->value);
		lst = lst->next;
	}
	result[++i] = NULL;
	return (result);
}

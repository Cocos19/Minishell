/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_redirections.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:02:15 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/03 11:54:43 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file_datas	*init_file_datas(t_shell *shell, char *val, int mode)
{
	t_file_datas	*result;

	result = malloc(sizeof(t_file_datas));
	if (!result)
		free_and_print_strerror(shell);
	result->value = ft_strdup(val);
	result->next = NULL;
	result->last = NULL;
	result->mode = mode;
	return (result);
}

t_token	*get_input(t_shell *shell, t_pipe_node *node, t_token *token)
{
	int	mode;

	if (!token->next)
	{
		printf("minishell: syntax error near unexpected token `newline'");
		return (NULL);
	}
	token->next->value = expander(shell, token->next->value);
	if (token->value[1] == '\0')
		mode = 1;
	else
		mode = 2;
	if (!node->input_lst)
	{
		node->input_lst = init_file_datas(shell, token->next->value, mode);
		node->input_lst->last = node->input_lst;
	}
	else
	{
		node->input_lst->last->next
			= init_file_datas(shell, token->next->value, mode);
		node->input_lst->last = node->input_lst->last->next;
	}
	return (token->next);
}

t_token	*get_output(t_shell *shell, t_pipe_node *node, t_token *token)
{
	int	mode;

	if (!token->next)
	{
		printf("minishell: syntax error near unexpected token `newline'");
		return (NULL);
	}
	token->next->value = expander(shell, token->next->value);
	if (token->value[1] == '\0')
		mode = 1;
	else
		mode = 2;
	if (!node->output_lst)
	{
		node->output_lst = init_file_datas(shell, token->next->value, mode);
		node->output_lst->last = node->output_lst;
	}
	else
	{
		node->output_lst->last->next
			= init_file_datas(shell, token->next->value, mode);
		node->output_lst->last = node->output_lst->last->next;
	}
	return (token->next);
}

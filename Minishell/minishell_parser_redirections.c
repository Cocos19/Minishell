/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_redirections.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:02:15 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/19 15:40:47 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file_datas	*init_file_datas(char *val, int mode)
{
	t_file_datas	*result;

	result = malloc(sizeof(t_file_datas));
	if (!result)
		print_str_error_and_exit();
	result->value = ft_strdup(val);
	result->next = NULL;
	result->last = NULL;
	result->mode = mode;
	return (result);
}

t_token	*get_input(t_shell *shell, t_pipe_node *node, t_token *token)
{
	int		mode;
	char	*value;

	if (!token->next)
	{
		printf("minishell: syntax error near unexpected token `newline'");
		shell->last_exit_status = 2;
		return (NULL);
	}
	if (token->value[1] == '\0')
		mode = 1;
	else
		mode = 2;
	value = expander(shell, token->next->value);
	if (!node->input_file_lst)
	{
		node->input_file_lst = init_file_datas(value, mode);
		node->input_file_lst->last = node->input_file_lst;
	}
	else
	{
		node->input_file_lst->last->next
			= init_file_datas(value, mode);
		node->input_file_lst->last = node->input_file_lst->last->next;
	}
	free(value);
	return (token->next);
}

t_token	*get_output(t_shell *shell, t_pipe_node *node, t_token *token)
{
	int		mode;
	char	*value;

	mode = 2;
	if (!token->next)
	{
		printf("minishell: syntax error near unexpected token `newline'");
		shell->last_exit_status = 2;
		return (NULL);
	}
	value = expander(shell, token->next->value);
	if (token->value[1] == '\0')
		mode = 1;
	if (!node->output_file_lst)
	{
		node->output_file_lst = init_file_datas(value, mode);
		node->output_file_lst->last = node->output_file_lst;
	}
	else
	{
		node->output_file_lst->last->next = init_file_datas(value, mode);
		node->output_file_lst->last = node->output_file_lst->last->next;
	}
	free(value);
	return (token->next);
}

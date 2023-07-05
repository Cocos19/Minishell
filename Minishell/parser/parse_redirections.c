/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:02:15 by mprofett          #+#    #+#             */
/*   Updated: 2023/07/05 09:11:41 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir_datas	*init_redir_datas(char *val, int mode, char type)
{
	t_redir_datas	*result;

	result = malloc(sizeof(t_redir_datas));
	if (!result)
		print_str_error_and_exit();
	result->value = ft_strdup(val);
	result->type = type;
	result->mode = mode;
	result->next = NULL;
	result->last = NULL;
	return (result);
}

void	*print_err_and_update_status(t_shell *shell, t_token *token, int err)
{
	if (err == 0)
		printf("minishell: syntax error near unexpected token `newline'\n");
	else if (err == 1)
		printf("minishell: syntax error near unexpected token `%s'\n",
			token->next->value);
	shell->last_exit_status = 2;
	return (NULL);
}

t_token	*get_input(t_shell *shell, t_pipe_node *node, t_token *token)
{
	int		mode;
	char	*value;

	mode = 2;
	if (!token->next)
		return (print_err_and_update_status(shell, token, 0));
	else if (token->next->value && (token->next->value[0] == '>'
			|| token->next->value[0] == '<' || token->next->value[0] == '|'))
		return (print_err_and_update_status(shell, token, 1));
	if (token->value[1] == '\0')
		mode = 1;
	value = expander(shell, token->next->value);
	if (!node->in_out_redir_list)
	{
		node->in_out_redir_list = init_redir_datas(value, mode, 'i');
		node->in_out_redir_list->last = node->in_out_redir_list;
	}
	else
	{
		node->in_out_redir_list->last->next
			= init_redir_datas(value, mode, 'i');
		node->in_out_redir_list->last = node->in_out_redir_list->last->next;
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
		return (print_err_and_update_status(shell, token, 0));
	else if (token->next->value && (token->next->value[0] == '>'
			|| token->next->value[0] == '<' || token->next->value[0] == '|'))
		return (print_err_and_update_status(shell, token, 1));
	value = expander(shell, token->next->value);
	if (token->value[1] == '\0')
		mode = 1;
	if (!node->in_out_redir_list)
	{
		node->in_out_redir_list = init_redir_datas(value, mode, 'o');
		node->in_out_redir_list->last = node->in_out_redir_list;
	}
	else
	{
		node->in_out_redir_list->last->next
			= init_redir_datas(value, mode, 'o');
		node->in_out_redir_list->last = node->in_out_redir_list->last->next;
	}
	free(value);
	return (token->next);
}

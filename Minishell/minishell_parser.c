/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:25:09 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/02 14:30:50 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe_node	*init_pipe_node(t_shell *shell)
{
	t_pipe_node	*result;

	result = malloc(sizeof(t_pipe_node));
	if (!result)
		free_and_print_strerror(shell);
	result->arguments = NULL;
	result->input_lst = NULL;
	result->output_lst = NULL;
	result->next = NULL;
	return (result);
}

int	next_token_is_valid(t_shell *shell, t_token *token)
{
	if (token->next && (token->next->value[0] == '>'
			|| token->next->value[0] == '|' || token->next->value[0] == '<'))
	{
		printf("minishell: syntax error near unexpected token `|'");
		export(shell, "?=2");
		return (1);
	}
	return (0);
}

t_pipe_node	*next(t_shell *shell, t_pipe_node *nod, t_token *tok, t_token *arg)
{
	if (!arg)
	{
		printf("minishell: syntax error near unexpected token `newline'");
		export(shell, "?=2");
		free_pipe_lst(shell);
	}
	if (next_token_is_valid(shell, tok) != 0)
		free_pipe_lst(shell);
	nod->arguments = init_argument_array(shell, arg);
	nod->next = init_pipe_node(shell);
	nod = nod->next;
	return (nod);
}

void	get_pipes(t_shell *shell, t_pipe_node *node, t_token *token)
{
	t_token	*arg_list;

	arg_list = NULL;
	while (token && shell->pipe_lst)
	{
		if (token->value[0] == '<')
			token = get_input(shell, node, token);
		else if (token->value[0] == '>')
			token = get_output(shell, node, token);
		else if (token->value[0] == '|')
		{
			node = next(shell, node, token, arg_list);
			arg_list = free_token_lst_without_content(arg_list);
		}
		else
			arg_list = get_arg(shell, arg_list, token);
		if (!token)
			free_pipe_lst(shell);
		else
			token = token->next;
	}
	if (g_exit_status == 0)
		node->arguments = init_argument_array(shell, arg_list);
	arg_list = free_token_lst_without_content(arg_list);
}

void	parser(t_shell *shell)
{
	t_pipe_node	*first_node;
	t_token		*first_token;

	shell->pipe_lst = init_pipe_node(shell);
	first_node = shell->pipe_lst;
	first_token = shell->token_lst;
	get_pipes(shell, first_node, first_token);
	g_exit_status = 0;
	free_token_lst(shell);
}

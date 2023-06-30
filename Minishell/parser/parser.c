/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:25:09 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/30 12:59:19 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pipe_node	*init_pipe_node(void)
{
	t_pipe_node	*result;

	result = malloc(sizeof(t_pipe_node));
	if (!result)
		print_str_error_and_exit();
	result->arguments = NULL;
	result->in_out_redir_list = NULL;
	result->next = NULL;
	result->path = NULL;
	result->pids = NULL;
	return (result);
}

int	next_token_is_valid(t_shell *shell, t_token *token)
{
	if (token->next && token->value[0] == '|' && token->next->value[0] == '|' )
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		shell->last_exit_status = 2;
		return (1);
	}
	return (0);
}

t_pipe_node	*next(t_shell *shell, t_pipe_node *nod, t_token *tok, t_token *arg)
{
	if (next_token_is_valid(shell, tok) != 0)
		free_pipe_lst(shell);
	nod->arguments = init_argument_array(arg);
	nod->next = init_pipe_node();
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
			arg_list = free_arg_lst(arg_list);
		}
		else
			arg_list = get_arg(shell, arg_list, token);
		if (!token)
			free_pipe_lst(shell);
		else
			token = token->next;
	}
	if (g_exit_status == 0 && arg_list)
		node->arguments = init_argument_array(arg_list);
	if (arg_list)
		arg_list = free_arg_lst(arg_list);
}

void	parser(t_shell *shell)
{
	t_pipe_node	*first_node;
	t_token		*first_token;

	shell->pipe_lst = init_pipe_node();
	first_node = shell->pipe_lst;
	first_token = shell->token_lst;
	get_pipes(shell, first_node, first_token);
	g_exit_status = 0;
	free_token_lst(shell);
}

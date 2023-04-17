/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipe_node_list.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:25:09 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/14 15:37:28 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe_node *init_pipe_node(t_shell *shell)
{
	t_pipe_node *result;

	result = init_pipe_node(shell);
	if (!result)
		free_and_print_strerror(shell);
	result->arguments = malloc(sizeof(char **));
	if (!result->arguments)
		free_and_print_strerror(shell);
	result->arguments[0] = NULL;
	result->temp_varlist = NULL;
	result->input_file_lst = NULL;
	result->output_file_lst = NULL;
	result->next = NULL;
	return (result);
}

t_pipe_node *get_next_node(t_shell *shell, t_pipe_node *current_node, t_token *token)
{
	if (!token->next)
	{
		//give back prompt;
			//if user ctrl D -> exit minishell and trow syntax error: unexpected end of file
			//if user ctrl C -> exit parsing
			//if user return nothing, give back prompt until there is some arg
		//tokenize result;
		//add to tokenlist;
		// current_node->next = init_pipe_node(shell);
		// return (current_node->next);
	}
	else if (token->next->value[0] == '|')
	{
		printf("minishell: syntax error near unexpected token `|'");
		g_exit_status = ERR_SYNTAX;
		update_exit_status_variable(shell);
		g_exit_status = 0;
		return (NULL);
	}
	else
	{
		current_node->next = init_pipe_node(shell);
		return (current_node->next);
	}
}

void	get_next_argument(t_shell *shell, t_pipe_node *node, t_token *token)
{
	char	**result;
	char	*str_to_add;

	str_to_add = ft_strdup(token->value);
	if (!str_to_add)
		free_and_print_strerror(shell);
	result = ft_add_to_str_array(node->arguments, str_to_add);
	if (!result)
		free_and_print_strerror(shell);
	free(node->arguments);
	node->arguments = result;
}

t_pipe_node *parse(t_shell *shell)
{
	t_pipe_node *result;
	t_pipe_node	*current_node;
	t_token *current_token;

	result = init_pipe_node(shell);
	current_node = result;
	current_token = shell->token_lst;
	while(current_token)
	{
		if (current_token->value[0] == '<')
			current_token = get_input(shell, current_node, current_token);
		else if (current_token->value[0] == '>')
			current_token = get_output(shell, current_node, current_token);
		else if (current_token->value[0] == '|')
		{
			current_node = get_next_node((shell, current_node, current_token));
			if (!current_node)
				return (NULL);
		}
		else
			get_next_argument(shell, current_node, current_token);
		current->token = current_token->next;
	}
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:25:09 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/18 12:12:55 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe_node *init_pipe_node(t_shell *shell)
{
	t_pipe_node *result;

	result = malloc(sizeof(t_pipe_node));
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

int	next_token_is_valid(t_token *token)
{
	if (token->next->value[0] == '|')
	{
		printf("minishell: syntax error near unexpected token `|'");
		g_exit_status = ERR_SYNTAX;
		update_exit_status_variable(shell);
		g_exit_status = 0;
		return (1);
	}
	return (0);
}

t_pipe_node *get_next_node(t_shell *shell, t_pipe_node *current_node, t_token *token)
{
	if (token->next->value[0] == '|')
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

void	get_next_argument(t_shell *shell, t_token *arg_list, t_token *token)
{
	// char	**result;
	// char	*str_to_add;

	// str_to_add = ft_strdup(token->value);
	// if (!str_to_add)
	// 	free_and_print_strerror(shell);
	// result = ft_add_to_str_array(node->arguments, str_to_add);
	// if (!result)
	// 	free_and_print_strerror(shell);
	// free(node->arguments);
	// node->arguments = result;
	t_token	*result;

	result = init_token();
	result->value = token->value;
	if (!arg_list)
		arg_list = result;
	else
		arg_list->last->next = result;
		arg_list->last = result;
}

int		get_token_list_size(t_token *lst)
{
	t_token	*temp;
	int		i;

	temp = lst;
	i = 0;
	while(temp)
	{

	}
}

char	**init_argument_array(t_token *arg_list)
{

}

t_pipe_node *parse(t_shell *shell)
{
	t_pipe_node *result;
	t_pipe_node	*current_node;
	t_token 	*current_token;
	t_token		*arg_list

	result = init_pipe_node(shell);
	current_node = result;
	current_token = shell->token_lst;
	arg_list = NULL;
	while(current_token)
	{
		// if (current_token->value[0] == '<')
		// 	current_token = get_input(shell, current_node, current_token);
		// else if (current_token->value[0] == '>')
		// 	current_token = get_output(shell, current_node, current_token);
		// else if (current_token->value[0] == '|')
		if (current_token->value[0] == '|') //temp
		{
			if (next_token_is_valid(t_token *token) != 0)
				return (NULL);
			current_node->arguments = init_argument_array(arg_list);
			current_node = get_next_node(shell, current_node, current_token);
			if (!current_node)
				return (NULL);
		}
		else
			get_next_argument(shell, current_node, current_token);
		current_token = current_token->next;
		}
	}
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 10:30:48 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/24 15:33:03 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *init_token(t_shell *shell)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		free_and_print_strerror(shell);
	new->value = NULL;
	new->last = NULL;
	new->next = NULL;
	return (new);
}

char	*get_token_end(t_shell *shell, char *input, t_token *current, char *token_start)
{
	char	*return_val;

	while (input)
	{
		if (*input == '\'')
		{
			++input;
			while (input && *input != '\'')
				++input;
		}
		else if (*input == '\"')
		{
			++input;
			while (input && *input != '\"')
				++input;
		}
		if (is_special_character(*input))
		{
			return_val = input - 1;
			input = NULL;
		}
		if (input)
			++input;
	}
	current->value = ft_substr_delimited(token_start, return_val);
	if (!current->value)
		free_and_print_strerror(shell);
	return (++return_val);
}

char	*tokenize_special_char(t_shell *shell, char *input, t_token *current, char *start)
{
	if (*(start) == '|')
		return (get_pipe(shell, input, current, start));
	else if (*(start) == '<' || *(start) == '>')
		return (get_redir(shell, input, current, start));
	current->value = NULL;
	current->next = NULL;
	return (NULL);
}

t_token	*tokenize(t_shell *shell, char *input)
{
	t_token *token_lst;
	t_token *current;
	char	*token_start;

	token_lst = init_token(shell);
	current = token_lst;
	input = ft_skip_character(input, ' ');
	while (input && *input)
	{
		token_start = input;
		if (is_special_character(*token_start) == 1)
			input = tokenize_special_char(shell, input, current, token_start);
		else
			input = get_token_end(shell, input, current, token_start);
		input = ft_skip_character(input, ' ');
		if (input && *input)
		{
			current->next = init_token(shell);
			current = current->next;
		}
	}
	token_lst->last = current;
	if (g_exit_status != 0)
		free_token_lst(shell);
	return (token_lst);
}

void	lexer(t_shell *shell, char *user_input)
{
	shell->token_lst = tokenize(shell, user_input);
	while (g_exit_status == 0 && token_list_is_valid(shell) != 0)
		complete_token(shell);
}

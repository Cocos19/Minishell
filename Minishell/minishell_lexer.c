/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 10:30:48 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/09 15:54:29 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_token(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		print_str_error_and_exit();
	new->value = NULL;
	new->last = NULL;
	new->next = NULL;
	return (new);
}

char	*get_token_end(char *input, t_token *cur, char *start)
{
	char	*return_val;

	while (input)
	{
		if (*input == '\'')
			input = ft_skip_all_but_character(++input, '\'');
		else if (*input == '\"')
			input = ft_skip_all_but_character(++input, '\"');
		if (is_special_character(*input))
		{
			return_val = input - 1;
			input = NULL;
		}
		if (input)
			++input;
	}
	cur->value = ft_substr_delimited(start, return_val);
	if (!cur->value)
		print_str_error_and_exit();
	return (++return_val);
}

char	*tokenize_s_char(char *input, t_token *cur, char *start)
{
	if (*(start) == '|')
		return (get_pipe(input, cur, start));
	else if (*(start) == '<' || *(start) == '>')
		return (get_redir(input, cur, start));
	cur->value = NULL;
	cur->next = NULL;
	return (NULL);
}

t_token	*tokenize(char *input)
{
	t_token	*token_lst;
	t_token	*current;
	char	*token_start;

	token_lst = init_token();
	current = token_lst;
	input = ft_skip_character(input, ' ');
	while (input && *input)
	{
		token_start = input;
		if (is_special_character(*token_start) == 1)
			input = tokenize_s_char(input, current, token_start);
		else
			input = get_token_end(input, current, token_start);
		input = ft_skip_character(input, ' ');
		if (input && *input)
		{
			current->next = init_token();
			current = current->next;
		}
	}
	token_lst->last = current;
	return (token_lst);
}

void	lexer(t_shell *shell, char *user_input)
{
	shell->token_lst = tokenize(user_input);
	while (g_exit_status == 0 && token_list_is_valid(shell) != 0)
		complete_token(shell);
}

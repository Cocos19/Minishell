/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 10:30:48 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/14 14:47:39 by mprofett         ###   ########.fr       */
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
	new->next = NULL;
	return (new);
}

int	is_special_character(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '\'' || c == '\"'
		|| c == ' ' || c == '\0')
		return (1);
	return (0);
}

char	*get_token_end(t_shell *shell, char *input, t_token *current, char *token_start)
{
	while (is_special_character(*(input + 1)) == 0)
		++input;
	current->value = ft_substr_delimited(token_start, input);
	if (!current->value)
		free_and_print_strerror(shell);
	return (++input);
}

char	*tokenize_special_char(t_shell *shell, char *input, t_token *current, char *start)
{
	if (*(start) == '|')
		return (tokenize_pipe_operator(shell, input, current, start));
	else if (*(start) == '<' || *(start) == '>')
		return (tokenize_redirection_operator(shell, input, current, start));
	else if (*(start) == '\'' || *(start) == '\"')
		return (tokenize_quotes(shell, input, current, start));
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
	while (input)
	{
		input = ft_skip_character(input, ' ');
		token_start = input;
		if (is_special_character(*token_start) == 1)
			input = tokenize_special_char(shell, input, current, token_start);
		else
			input = get_token_end(shell, input, current, token_start);
		current->next = init_token(shell);
		current = current->next;
	}
	if (g_exit_status != 0)
	{
		free_token_lst(token_lst);
		token_lst = NULL;
	}
	return (token_lst);
}

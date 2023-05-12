/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer_special_tokens.c					:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:08:40 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/20 14:55:48 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_character(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ' ' || c == '\0')
		return (1);
	return (0);
}

char	*get_pipe(char *input, t_token *current, char *start)
{
	current->value = ft_substr_delimited(start, start);
	if (!current->value)
		print_str_error_and_exit();
	return (++input);
}

char	*get_redir(char *input, t_token *current, char *start)
{
	if (*(input + 1) != *start)
	{
		current->value = ft_substr_delimited(start, start);
		if (!current->value)
			print_str_error_and_exit();
		return (++input);
	}
	else
	{
		current->value = ft_substr_delimited(start, input + 1);
		if (!current->value)
			print_str_error_and_exit();
		return (input + 2);
	}
}

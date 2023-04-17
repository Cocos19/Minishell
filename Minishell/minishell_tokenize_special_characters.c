/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokenize_special_characters.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:08:40 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/14 14:47:04 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*tokenize_pipe_operator(t_shell *shell, char *input, t_token *current, char *start)
{
	current->value = ft_substr_delimited(start, start);
	if (!current->value)
		free_and_print_strerror(shell);
	return (++input);
}

char	*tokenize_redirection_operator(t_shell *shell, char *input, t_token *current, char *start)
{
	if (*(input + 1) != *start)
	{
		current->value = ft_substr_delimited(start, start);
		if (!current->value)
			free_and_print_strerror(shell);
		return (++input);
	}
	else
	{
		current->value = ft_substr_delimited(start, input + 1);
		if (!current->value)
			free_and_print_strerror(shell);
		return (input + 2);
	}
}

char	*tokenize_quotes(t_shell *shell, char *input, t_token *current, char *start)
{
	++input;
	input = ft_strchr(input, *start);
	current->value = ft_substr_delimited(start, input);
	if (!current->value)
		free_and_print_strerror(shell);
	return (++input);
}

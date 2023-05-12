/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expander.c		                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:46:52 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/20 10:31:54 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_substr_len(char *str, int *str_i, char c)
{
	int	result_len;
	int	i;

	result_len = 0;
	if (c == '\'' || c == '\"')
	{
		(*str_i)++;
		i = *str_i;
		while (str[i++] != c)
			++result_len;
	}
	else
	{
		i = *str_i;
		while (str[i] != '\'' && str[i] != '\"' && str[i] != '\0')
		{
			++i;
			++result_len;
		}
	}
	return (result_len);
}

char	*get_next_substr(t_shell *shell, char *str, int *str_i, char c)
{
	char	*result;
	int		result_len;
	int		i;

	result_len = get_substr_len(str, str_i, c);
	result = malloc(sizeof(char) * result_len + 1);
	if (!result)
		print_str_error_and_exit();
	i = -1;
	while (++i < result_len)
		result[i] = str[(*str_i)++];
	result[i] = '\0';
	if (c == '\'' || c == '\"')
		(*str_i)++;
	if (c != '\'')
		result = search_and_expand_env_var(shell, result);
	return (result);
}

char	*expander(t_shell *shell, char *str)
{
	int		str_i;
	char	*result;

	str_i = 0;
	result = malloc(sizeof(char));
	if (!result)
		print_str_error_and_exit();
	result[0] = '\0';
	while (str[str_i])
	{
		if (str[str_i] == '\'')
			result = ft_strjoin_and_free_srcs(result,
					get_next_substr(shell, str, &str_i, '\''));
		else if (str[str_i] == '\"')
			result = ft_strjoin_and_free_srcs(result,
					get_next_substr(shell, str, &str_i, '\"'));
		else
			result = ft_strjoin_and_free_srcs(result,
					get_next_substr(shell, str, &str_i, '\0'));
		if (!result)
			print_str_error_and_exit();
	}
	return (result);
}

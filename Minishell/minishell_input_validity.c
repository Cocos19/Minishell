/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_input_validity.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:15:24 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/14 13:06:31 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_error(t_shell *shell, int s_quotes, int d_quotes)
{
	if (s_quotes % 2 != 0)
		printf("%sunexpected EOF while looking for matching '\''\n",
			shell->name);
	else if (d_quotes % 2 != 0)
		printf("%sunexpected EOF while looking for matching '\"'\n",
			shell->name);
	g_exit_status = ERR_SYNTAX;
}

int	check_quotes_validity(t_shell *shell, char *str)
{
	int		s_quotes;
	int		d_quotes;

	s_quotes = 0;
	d_quotes = 0;
	while (str && *str)
	{
		if (*str == '\"' && s_quotes % 2 == 0)
			++d_quotes;
		if (*str == '\'' && d_quotes % 2 == 0)
			++s_quotes;
		++str;
	}
	if (s_quotes % 2 != 0 || d_quotes % 2 != 0)
		print_syntax_error(shell, s_quotes, d_quotes);
	return (g_exit_status);
}

int	input_is_valid(t_shell *shell)
{
	char	*str;

	str = shell->input;
	if (!(ft_strlen(str) > 0))
		return (-1);
	else if (check_quotes_validity(shell, str) != 0)
		return (g_exit_status);
	return (0);
}

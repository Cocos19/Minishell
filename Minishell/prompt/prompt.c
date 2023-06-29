/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:15:24 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/29 12:25:25 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	input_is_readable(t_shell *shell)
{
	char	*str;

	str = shell->input;
	while (str && *str)
	{
		if (*str != 9 && *str != ' ')
			return (0);
		++str;
	}
	return (1);
}

int	input_is_valid(t_shell *shell)
{
	char	*str;

	str = shell->input;
	if (!(input_is_readable(shell) == 0))
		return (-1);
	if (!(ft_strlen(shell->input) > 0))
		return (-1);
	else if (check_quotes_validity(shell, str) != 0)
		return (g_exit_status);
	return (0);
}

char	*give_prompt(t_shell *shell)
{
	char	*user_input;

	user_input = readline(shell->name);
	if (g_exit_status != 0)
	{
		shell->last_exit_status = EOWNER_DEAD;
		g_exit_status = 0;
	}
	shell->input = user_input;
	if (!user_input)
		print_info_and_exit("exit\n", shell->last_exit_status);
	return (user_input);
}

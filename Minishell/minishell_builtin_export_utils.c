/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_export_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:16:45 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/04 15:15:17 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_export_mode(char *var)
{
	int	i;
	int	result;

	i = -1;
	result = -1;
	while (var && var[++i])
	{
		if (var[i] == '?')
			return (-2);
		if (var[i] == '+')
		{
			result = 1;
			while (var[++i] == '+')
				;
			if (var[i] == '=')
				return (result);
			result = -1;
		}
		if (var[i] == '=')
			return (0);
	}
	return (result);
}

int	check_export_variable_validity(char *var)
{
	if (var[0] == '=' || (var[0] == '+' && var[1] == '='))
		return (-1);
	return (0);
}

int	var_to_search_len(char *var, char c)
{
	int	i;

	i = -1;
	while (var && var[++i])
	{
		if (var[i] == c)
			return (i);
	}
	return (-1);
}

char	*get_value_to_append(t_shell *shell, char *var)
{
	int		var_len;
	int		result_len;
	int		i;
	char	*result;

	var_len = var_to_search_len(var, '+');
	result_len = ft_strlen(var) - var_len;
	result = malloc(sizeof(char) * result_len + 1);
	if (!result)
		free_and_print_strerror(shell);
	i = -1;
	++var_len;
	while (++i < result_len)
	{
		result[i] = var[++var_len];
	}
	result[i] = '\0';
	return (result);
}

int	export_variable_is_in_envp(t_shell *shell, char *var, char c)
{
	int	i;
	int	len;

	i = -1;
	len = var_to_search_len(var, c);
	while (shell->envp && shell->envp[++i])
	{
		if (ft_strncmp(shell->envp[i], var, len) == 0)
			return (i);
	}
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expander_env_var.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:01:14 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/19 12:58:40 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_an_envp_var(t_shell *shell, char *str)
{
	char	*result;
	int		var_len;
	int		i;

	i = -1;
	var_len = ft_strlen(str);
	while (shell->envp[++i])
	{
		if (ft_strncmp(shell->envp[i], str, var_len) == 0)
		{
			result = ft_substr(shell->envp[i], var_len,
					ft_strlen(shell->envp[i]) - var_len);
			if (!result)
				print_str_error_and_exit();
			return (result);
		}
	}
	return (NULL);
}

int	get_var_to_search_size(char *str, int i)
{
	int	size;

	size = i;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"' || str[i] == ' '
			|| str[i] == '=' || str[i] == '+' || str[i] == '$')
			return (i - size - 1);
	}
	return (i - size - 1);
}

char	*get_expanded_var(char *str, char *var_to_s, char *var_to_ex, int *i)
{
	char	*result;

	if (var_to_ex)
			result = ft_expand(str, str + *i, var_to_s, var_to_ex);
	else
		result = ft_expand(str, str + *i, var_to_s, "");
	if (!result)
		print_str_error_and_exit();
	*i += ft_strlen(var_to_ex);
	free(var_to_s);
	free(var_to_ex);
	free(str);
	return (result);
}

char	*search_and_remplace_var(t_shell *shell, char *str, int *i)
{
	char	*result;
	char	*var_to_expand;
	char	*var_to_search;
	int		var_size;

	var_size = get_var_to_search_size(str, *i);
	if (var_size != 0)
	{
		result = ft_substr(str, *i + 1, var_size);
		if (!result)
			print_str_error_and_exit();
		var_to_search = ft_strjoin_protected(result, "=");
		if (ft_strcmp(var_to_search, "?=") == 0)
		{
			var_to_expand = ft_itoa(shell->last_exit_status);
			if (!var_to_expand)
				print_str_error_and_exit();
		}
		else
			var_to_expand = is_an_envp_var(shell, var_to_search);
		free(var_to_search);
		var_to_search = ft_strdup(result);
		free(result);
		if (!var_to_search)
			print_str_error_and_exit();
		result = get_expanded_var(str, var_to_search, var_to_expand, i);
		return (result);
	}
	return (str);
}

char	*search_and_expand_env_var(t_shell *shell, char *str)
{
	int		i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '$')
			str = search_and_remplace_var(shell, str, &i);
	}
	return (str);
}

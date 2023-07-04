/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:01:14 by mprofett          #+#    #+#             */
/*   Updated: 2023/07/04 13:28:26 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*exit_status_to_str(t_shell *shell, char *str)
{
	char	*n;

	n = ft_itoa(shell->last_exit_status);
	if (!n)
		print_str_error_and_exit();
	return (ft_strjoin_and_free_srcs(n, strndup(str + 1, ft_strlen(str) - 2)));
}

char	*is_an_envp_var(t_shell *shell, char *str)
{
	char	*res;
	int		var_len;
	int		i;

	if (ft_strncmp(str, "?", 1) == 0)
		return (exit_status_to_str(shell, str));
	i = -1;
	var_len = ft_strlen(str);
	while (shell->envp && shell->envp[++i])
	{
		if (ft_strncmp(shell->envp[i], str, var_len) == 0)
		{
			res = ft_substr(shell->envp[i], var_len,
					ft_strlen(shell->envp[i]) - var_len);
			if (!res)
				print_str_error_and_exit();
			return (res);
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
	char	*cut;

	cut = ft_strjoin_protected("$", var_to_s);
	free(var_to_s);
	if (var_to_ex)
		result = ft_expand(str, str + *i, cut, var_to_ex);
	else
		result = ft_expand(str, str + *i, cut, "");
	if (!result)
		print_str_error_and_exit();
	*i += ft_strlen(var_to_ex);
	free(cut);
	free(var_to_ex);
	free(str);
	str = result;
	return (result);
}

char	*search_and_remplace_var(t_shell *shell, char *str, int *i)
{
	char	*result;
	char	*var_to_expand;
	char	*var_to_search;
	int		var_size;

	var_size = get_var_to_search_size(str, *i);
	if (var_size == 0)
	{
		printf("var_size == 0\n");
		return (str);
	}
	result = ft_substr(str, *i + 1, var_size);
	if (!result)
		print_str_error_and_exit();
	var_to_search = ft_strjoin_protected(result, "=");
	var_to_expand = is_an_envp_var(shell, var_to_search);
	free(var_to_search);
	var_to_search = ft_strdup(result);
	free(result);
	if (!var_to_search)
		print_str_error_and_exit();
	result = get_expanded_var(str, var_to_search, var_to_expand, i);
	return (result);
}

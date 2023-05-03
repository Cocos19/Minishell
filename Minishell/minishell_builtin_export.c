/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_export.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:58:55 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/02 16:28:26 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_mode(char	*var)
{
	int	i;
	int	result;

	i = -1;
	result = -1;
	while (var && var[++i])
	{
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

int	variable_is_valid(char *var)
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

int	is_in_envp(t_shell *shell, char *var, char c)
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

void	add_var_to_envp(t_shell *shell, char *var)
{
	char	**new_envp;

	new_envp = ft_add_to_str_array(shell->envp, var);
	ft_free_str_array(shell->envp);
	shell->envp = new_envp;
}

char	*get_value_to_add(t_shell *shell, char *var)
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
	return(result);
}

void	remplace_envp_var(t_shell *shell, char *new_var, int index)
{
	free(shell->envp[index]);
	shell->envp[index] = ft_strdup(new_var);
}

void	export_variable(t_shell *shell, char *var)
{
	int		envp_index;

	envp_index = is_in_envp(shell, var, '=');
	if (envp_index == -1)
		add_var_to_envp(shell, var);
	else
		remplace_envp_var(shell, var, envp_index);
}

void	export_variable_in_append_mode(t_shell *shell, char *var)
{
	int		envp_index;
	char	*str_to_add;

	envp_index = is_in_envp(shell, var, '+');
	if (envp_index == -1)
		add_var_to_envp(shell, var);
	else
	{
		str_to_add = get_value_to_add(shell, var);
		var = ft_strjoin_protected(shell, shell->envp[envp_index], str_to_add);
		free(str_to_add);
		remplace_envp_var(shell, var, envp_index);
	}
}

int	export(t_shell *shell, char *var)
{
	int		mode;

	//expand var before export
	mode = get_mode(var);
	if (mode == -1)
		add_var_to_envp(shell, var);
	else
	{
		if (variable_is_valid(var) == 0)
		{
			if (mode == 0)
				export_variable(shell, var);
			else
				export_variable_in_append_mode(shell, var);
		}
		else
		{
			printf("minishell: export: '%s': not a valid identifier\n", var);
			return (1);
		}
	}
	return (0);
}

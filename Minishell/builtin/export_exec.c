/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exec.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:45:34 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/09 16:04:13 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_var_to_envp(t_shell *shell, char *var)
{
	char	**new_envp;

	new_envp = ft_add_to_str_array(shell->envp, var);
	ft_free_str_array(shell->envp);
	shell->envp = new_envp;
}

void	export_variable(t_shell *shell, char *var)
{
	int		envp_index;

	envp_index = export_variable_is_in_envp(shell, var, '=');
	if (envp_index == -1)
		add_var_to_envp(shell, var);
	else
	{
		free(shell->envp[envp_index]);
		shell->envp[envp_index] = ft_strdup(var);
	}
}

void	export_variable_in_append_mode(t_shell *shell, char *var)
{
	int		envp_index;
	char	*str_to_add;

	envp_index = export_variable_is_in_envp(shell, var, '+');
	if (envp_index == -1)
		add_var_to_envp(shell, var);
	else
	{
		str_to_add = get_value_to_append(var);
		var = ft_strjoin_protected(shell->envp[envp_index], str_to_add);
		free(str_to_add);
		free(shell->envp[envp_index]);
		shell->envp[envp_index] = ft_strdup(var);
	}
}

int	export(t_shell *shell, char *var)
{
	int		mode;
	int		var_validity;

	mode = get_export_mode(var);
	var_validity = check_export_variable_validity(var);
	if (mode == 0 && var_validity == 0)
		export_variable(shell, var);
	else if (mode == 1 && var_validity == 0)
		export_variable_in_append_mode(shell, var);
	else if (mode == -3)
		return (0);
	else if (mode == -2 || mode == -4
		|| !(check_export_variable_validity(var) == 0))
	{
		printf("minishell: export: '%s': not a valid identifier\n", var);
		return (1);
	}
	return (0);
}

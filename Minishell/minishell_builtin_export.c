/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_export.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:58:55 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/03 12:23:25 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remplace_envp_var(t_shell *shell, char *new_var, int index)
{
	free(shell->envp[index]);
	shell->envp[index] = ft_strdup(new_var);
}

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
		remplace_envp_var(shell, var, envp_index);
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
		str_to_add = get_value_to_append(shell, var);
		var = ft_strjoin_protected(shell, shell->envp[envp_index], str_to_add);
		free(str_to_add);
		remplace_envp_var(shell, var, envp_index);
	}
}

int	export(t_shell *shell, char *var)
{
	int		mode;

	mode = get_export_mode(var);
	if (mode == -1)
		add_var_to_envp(shell, var);
	else
	{
		if (check_export_variable_validity(var) == 0)
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

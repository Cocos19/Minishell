/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_export.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:58:55 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/04 19:07:59 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		str_to_add = get_value_to_append(shell, var);
		var = ft_strjoin_protected(shell, shell->envp[envp_index], str_to_add);
		free(str_to_add);
		free(shell->envp[envp_index]);
		shell->envp[envp_index] = ft_strdup(var);
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
		if (check_export_variable_validity(var) == 0 && mode != -2)
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

void	builtin_export(t_shell *shell, t_pipe_node *node)
{
	int		i;
	int		exit_status;
	char	**env;

	i = 0;
	exit_status = 0;
	if (!node->arguments[1])
	{
		env = ft_strdup_array(shell->envp);
		ft_sort_str_array(env);
		ft_print_str_array(env);
		ft_free_str_array(env);
	}
	else
	{
		open_close_inputs(shell, node->input_file_lst);
		open_close_outputs(node->input_file_lst);
		while (node->arguments[++i])
			exit_status = export(shell, node->arguments[i]);
	}
	exit (exit_status);
}

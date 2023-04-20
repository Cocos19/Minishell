/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_export.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:58:55 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/20 15:12:49 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_name_len(char *var)
{
	int	i;

	i = -1;
	while (var && var[++i])
		if (var[i] == '=')
			return (i);
	return (-1);
}

int	is_in_envp(t_shell *shell, char *var)
{
	int	i;
	int	len;

	i = -1;
	len = var_name_len(var);
	if (len < 0)
		return (-1);
	while (shell->envp && shell->envp[++i])
		if (ft_strncmp(shell->envp[i], var, len) == 0)
			return (i);
	return (-1);
}

void	export(t_shell *shell, char *var)
{
	int		envp_index;
	char	**new_envp;

	envp_index = is_in_envp(shell, var);
	if (envp_index == -1)
	{
		new_envp = ft_add_to_str_array(shell->envp, var);
		ft_free_str_array(shell->envp);
		shell->envp = new_envp;
	}
	else
	{
		free(shell->envp[envp_index]);
		shell->envp[envp_index] = ft_strdup(var);
	}
}

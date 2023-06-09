/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:14:30 by mprofett          #+#    #+#             */
/*   Updated: 2023/07/06 10:04:15 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env_var(t_shell *shell, char *to_update, char *new_val)
{
	char	*new_var;
	int		var_index;
	int		free_new_val;

	free_new_val = 0;
	if (new_val[0] == '$')
	{
		new_val = search_and_expand_env_var(shell, new_val);
		free_new_val = 1;
	}
	new_var = ft_strjoin_protected(to_update, new_val);
	var_index = export_variable_is_in_envp(shell, to_update, '=');
	if (var_index >= 0)
	{
		free(shell->envp[var_index]);
		shell->envp[var_index] = new_var;
	}
	else
		export(shell, new_var);
	if (free_new_val == 1)
		free(new_val);
}

void	update_envp(t_shell *shell, char *old_pwd)
{
	char	*result;

	update_env_var(shell, "OLDPWD=", old_pwd);
	result = NULL;
	result = getcwd(result, NAME_MAX);
	update_env_var(shell, "PWD=", result);
	free(result);
}

int	execute_change_dir(t_shell *shell, char *path)
{
	int		result;
	char	*old_pwd;

	result = 0;
	if (!path)
		return (EPERM);
	if (access(path, X_OK | F_OK) != 0)
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		return (EPERM);
	}
	old_pwd = NULL;
	old_pwd = getcwd(old_pwd, NAME_MAX);
	if (!old_pwd)
	{
		handle_getcwd_error(shell);
		return (EPERM);
	}
	result = chdir(path);
	if (result == 0)
		update_envp(shell, old_pwd);
	free(path);
	free(old_pwd);
	return (result);
}

char	*get_path(t_shell *shell, t_pipe_node *node)
{
	char	*path;

	path = NULL;
	if (!node->arguments[1])
		path = get_home_relative_path(shell, NULL);
	else if (node->arguments[2])
		printf("minishell: cd: too many arguments\n");
	else if (node->arguments[1][0] == '~')
		path = get_home_relative_path(shell, node->arguments[1]);
	else
	{
		path = ft_strdup(node->arguments[1]);
		if (!path)
			print_str_error_and_exit();
	}
	return (path);
}

int	builtin_cd(t_shell *shell, t_pipe_node *node)
{
	char	*path;

	if (node->arguments[1] && node->arguments[1][0] == '-'
		&& node->arguments[1][1] == '\0')
		return (get_old_pwd_path(shell));
	path = get_path(shell, node);
	return (execute_change_dir(shell, path));
}

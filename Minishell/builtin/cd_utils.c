/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:37:09 by mprofett          #+#    #+#             */
/*   Updated: 2023/07/06 10:04:21 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_getcwd_error(t_shell *shell)
{
	printf("minishell: cd: error retrieving current directory:");
	printf("getcwd: cannot access parent directories: \n");
	shell->last_exit_status = EPERM;
	return (NULL);
}

char	*get_home_relative_path(t_shell *shell, char *arg)
{
	char	*res;
	char	*temp;
	int		env_index;

	env_index = export_variable_is_in_envp(shell, "HOME=", '=');
	if (env_index < 0)
	{
		printf("minishell: cd: HOME not set\n");
		return (NULL);
	}
	else if (!arg)
		res = search_and_expand_env_var(shell, ft_strdup("$HOME"));
	else
	{
		temp = search_and_expand_env_var(shell, ft_strdup("$HOME"));
		if (!temp)
			print_str_error_and_exit();
		res = ft_expand(arg, arg, "~", temp);
		free(temp);
	}
	if (!res)
		print_str_error_and_exit();
	return (res);
}

int	execute_change_dir_to_old_pwd(t_shell *shell, char *path)
{
	int		result;
	char	*str;

	result = chdir(path);
	if (result == 0)
	{
		write(1, path, ft_strlen(path));
		write(1, "\n", 1);
		update_env_var(shell, "OLDPWD=", ft_strdup("$PWD"));
		str = NULL;
		str = getcwd(str, NAME_MAX);
		update_env_var(shell, "PWD=", str);
		free(str);
	}
	free(path);
	return (result);
}

int	get_old_pwd_path(t_shell *shell)
{
	int		oldpwd_index;
	char	*path;

	oldpwd_index = export_variable_is_in_envp(shell, "OLDPWD=", '=');
	if (oldpwd_index < 0)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (EPERM);
	}
	path = search_and_expand_env_var(shell, ft_strdup("$OLDPWD"));
	if (!path)
		print_str_error_and_exit();
	if (access(path, X_OK | F_OK) != 0)
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		return (EPERM);
	}
	return (execute_change_dir_to_old_pwd(shell, path));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:37:09 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/27 14:24:18 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_dot_relative_path(t_shell *shell, t_pipe_node *node)
{
	char	*result;
	char	*temp;
	char	*new_str_end;

	temp = search_and_expand_env_var(shell, ft_strdup("$PWD"));
	if (!temp)
		print_str_error_and_exit();
	if (node->arguments[1][1] == '.')
	{
		if (temp[0] == '/' && ft_strlen(temp) == 1)
			return (temp);
		new_str_end = ft_strrchr(temp, '/');
		result = ft_substr_delimited(temp, new_str_end - 1);
	}
	else
		result = ft_strjoin_protected(temp, node->arguments[1] + 1);
	if (!result)
		print_str_error_and_exit();
	free(temp);
	return (result);
}

char	*get_home_relative_path(t_shell *shell, char *arg)
{
	char	*res;
	char	*temp;
	int		env_index;

	env_index = export_variable_is_in_envp(shell, "HOME=", '=');
	if (env_index < 0)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (NULL);
	}
	else if (!arg)
		res = ft_strdup(search_and_expand_env_var(shell, ft_strdup("$HOME")));
	else
	{
		temp = ft_strdup(search_and_expand_env_var(shell, ft_strdup("$HOME")));
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
	int	result;

	result = chdir(path);
	if (result == 0)
	{
		write(1, path, ft_strlen(path));
		write(1, "\n", 1);
		update_env_var(shell, "OLDPWD=", ft_strdup("$PWD"));
		update_env_var(shell, "PWD=", path);
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

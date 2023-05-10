/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_cd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:14:30 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/10 15:51:41 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_shell *shell, char *arg)
{
	char	*res;
	char	*temp;
	int		env_index;

	res = NULL;
	env_index = export_variable_is_in_envp(shell, "HOME=", '=');
	if (env_index < 0)
		print_info_and_exit("minishell: cd: HOME not set\n", EPERM);
	else if (!arg)
	{
		res = ft_strdup(search_and_expand_env_var(shell, ft_strdup("$HOME")));
		if (!res)
			print_info_str_error_and_exit(arg);
	}
	else
	{
		temp = ft_strdup(search_and_expand_env_var(shell, ft_strdup("$HOME")));
		if (!temp)
			print_str_error_and_exit();
		res = ft_expand(arg, arg, "~", temp);
		if (!res)
			print_str_error_and_exit();
		free(temp);
	}
	return (res);
}

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

void	update_envp(t_shell *shell, char *path)
{
	if (export_variable_is_in_envp(shell, "PWD=", '=') >= 0)
		update_env_var(shell, "OLDPWD=", ft_strdup("$PWD"));
	update_env_var(shell, "PWD=", path);
}

void	handle_minus_argument(t_shell *shell)
{
	int		oldpwd_index;
	int		result;
	char	*path;

	oldpwd_index = export_variable_is_in_envp(shell, "OLDPWD=", '=');
	if (oldpwd_index < 0)
		print_info_and_exit("minishell: cd: OLDPWD not set\n", EPERM);
	path = ft_strdup(search_and_expand_env_var(shell, ft_strdup("$OLDPWD")));
	if (!path)
		print_str_error_and_exit();
	if (access(path, X_OK | F_OK) != 0)
		print_builtin_info_str_error_and_exit("cd", path);
	result = chdir(path);
	if (result == 0)
	{
		update_env_var(shell, "OLDPWD=", ft_strdup("$PWD"));
		update_env_var(shell, "PWD=", path);
	}
	free(path);
	exit(result);
}

void	builtin_cd(t_shell *shell, t_pipe_node *node)
{
	char	*path;
	int		result;

	open_close_inputs(shell, node->input_file_lst);
	open_close_outputs(node->output_file_lst);
	path = NULL;
	if (!node->arguments[1])
		path = get_path(shell, NULL);
	else if (node->arguments[2])
		print_info_and_exit("minishell: cd: too many arguments\n", EPERM);
	else if (node->arguments[1][0] == '-' && node->arguments[1][1] == '\0')
		handle_minus_argument(shell);
	else if (node->arguments[1][0] == '~')
		path = get_path(shell, node->arguments[1]);
	else
		path = strdup(node->arguments[1]);
	if (access(path, X_OK | F_OK) != 0)
		print_builtin_info_str_error_and_exit("cd", path);
	result = chdir(path);
	if (result == 0)
		update_envp(shell, path);
	free(path);
	exit(result);
}

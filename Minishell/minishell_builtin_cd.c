/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_cd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:14:30 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/09 12:08:14 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//home marche toujours si HOME est unset
//cd sans arg renvoie toujours vers HOME meme si unset
// ./+nomdudossier descend dans le directory
// ..remonte le directory (si on est dans le root il ne faut pas remonter)
// cd - si old PWD est pas set, declare bash: cd: OLDPWD not set -> pas en bash 5.2
// idem si on a pas encore change de directory, OLDPWD est pas encore set
// ~ si gere avec, il faut gere ~/+dossier dans le dossier home
// pas oublier d'update le OLDPWD et de changer PWD a chauque fois
// utilise pas le result du pipe

char	*get_path(t_shell *shell, char *arg)
{
	char	*result;
	char	*temp;

	if (!arg)
	{
		result = ft_strdup(getenv("HOME"));
		printf("result: %s\n", result);
		if (!result)
		{
			printf("minishell: %s: %s\n", arg, strerror(errno));
			exit (errno);
		}
	}
	else
	{
		temp = ft_strdup(getenv("HOME"));
		result = ft_expand(arg, arg, "~", temp);
		if (!result)
			free_and_print_strerror(shell);
		free(temp);
	}
	return (result);
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
	new_var = ft_strjoin_protected(shell, to_update, new_val);
	var_index = export_variable_is_in_envp(shell, to_update, '=');
	free(shell->envp[var_index]);
	shell->envp[var_index] = new_var;
	if (free_new_val == 1)
		free(new_val);
}

void	check_path_access(char *path)
{
	if (access(path, X_OK | F_OK) != 0)
	{
		printf("minishell: %s: %s\n", path, strerror(errno));
		exit (errno);
	}
}

void	update_envp(t_shell *shell, char *path)
{
	update_env_var(shell, "OLDPWD=", ft_strdup("$PWD"));
	update_env_var(shell, "PWD=", path);
}

void	builtin_cd(t_shell *shell, t_pipe_node *node)
{
	char	*path;
	int		result;

	open_close_inputs(shell, node->input_file_lst);
	open_close_outputs(node->output_file_lst);
	if (!node->arguments[1])
		path = get_path(shell, NULL);
	else if (node->arguments[2])
	{
		printf("minishell: cd: too many arguments\n");
		exit (1);
	}
	else
	{
		if (node->arguments[1][0] == '~')
			path = get_path(shell, node->arguments[1]);
		else
			path = strdup(node->arguments[1]);
		check_path_access(path);
	}
	result = chdir(path);
	if (result == 0)
		update_envp(shell, path);
	free(path);
	ft_print_str_array(shell->envp);
	exit(result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:23:35 by cmartino          #+#    #+#             */
/*   Updated: 2023/06/29 11:01:15 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	cmd_not_found(char *str)
{
	write(2, "minishell: ", 12);
	write(2, str, ft_strlen(str));
	write(2, ": command not found\n", 20);
}

static int	ft_test_cmd(char *path, char *cmd)
{
	char	*cmd_test;
	char	*test;

	cmd_test = ft_strjoin("/", cmd);
	if (!cmd_test)
		exit(EXIT_FAILURE);
	test = ft_strjoin(path, cmd_test);
	free(cmd_test);
	if (!test)
		exit(EXIT_FAILURE);
	if (access(test, X_OK) == 0)
	{
		free(test);
		test = NULL;
		return (0);
	}
	free(test);
	test = NULL;
	return (1);
}

char	*cmd_does_not_exist(t_shell *shell, char **arg)
{
	shell->last_exit_status = 127;
	shell->exit = 0;
	cmd_not_found(arg[0]);
	return (NULL);
}

char	*cmd_exist(t_shell *shell, char **envp, char **arg)
{
	int		i;
	char	*result;
	char	**path;

	result = NULL;
	if (access(arg[0], X_OK) == 0)
		return (arg[0]);
	else
	{
		path = get_envp_paths(envp);
		i = 0;
		while (path && path[i])
		{
			if (ft_test_cmd(path[i], arg[0]) == 0)
			{
				result = ft_strdup(path[i]);
				free_all_tab(path, len_tab(path));
				return (result);
			}
			++i;
		}
		free_all_tab(path, len_tab(path));
	}
	return (cmd_does_not_exist(shell, arg));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cmd_exist.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:23:35 by cmartino          #+#    #+#             */
/*   Updated: 2023/04/27 11:30:27 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_not_found(char *str)
{
	write(2, "command not found :\n", 20);
	write(2, str, ft_strlen(str));
}

static int	ft_test_cmd(char *path, char *cmd, int i)
{
	int		cmd_ok;
	char	*cmd_test;
	char	*test;

	cmd_ok = 0;
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

char	*cmd_exist(char **envp, char **arg)	// fct leaks avec path -> fixed ? 
{
	int		i;
	char	**path;

	if (access(arg[0], X_OK) == 0)
		return (arg[0]);
	else
	{
		path = get_envp_paths(envp);
		i = 0;
		while (path && path[i])
		{
			if (test_cmd(path[i], arg[0], i) == 0)
				return (path[i]);
			++i;
		}
		free_all_tab(path, len_tab(path));
	}
	cmd_not_found(arg[0]);
	return (NULL);
}

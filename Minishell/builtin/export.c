/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:58:55 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/30 15:41:53 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_export_array_fd(char **str_array)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (str_array)
	{
		while (str_array && str_array[++i])
		{
			if (!(str_array[i][0] == '_' && str_array[i][1] == '='))
			{
				write(1, "declare -x ", 11);
				while (str_array[i][j] != '=' && str_array[i][j] != '\0')
					write(1, &str_array[i][j++], 1);
				write(1, "=\"", 2);
				++j;
				while (str_array[i][j] != '=' && str_array[i][j] != '\0')
					write(1, &str_array[i][j++], 1);
				write(1, "\"\n", 2);
				j = 0;
			}
		}
	}
	else
		write(1, "\n", 1);
}

int	execute_export(t_shell *shell, t_pipe_node *node)
{
	int		i;
	int		result;

	i = 0;
	while (node->arguments[++i])
	{
		result = export(shell, node->arguments[i]);
		if (result != 0)
			return (result);
	}
	return (0);
}

int	builtin_export(t_shell *shell, t_pipe_node *node)
{
	char	**env;

	printf("ici\n");
	if (!node->arguments[1])
	{
		env = ft_strdup_array(shell->envp);
		ft_sort_str_array(env);
		ft_print_export_array_fd(env);
		ft_free_str_array(env);
		return (0);
	}
	return (execute_export(shell, node));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:58:55 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/26 10:01:02 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_export_array_fd(char **str_array, int fd)
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
				write(fd, "declare -x ", 11);
				while (str_array[i][j] != '=' && str_array[i][j] != '\0')
					write(fd, &str_array[i][j++], 1);
				write(fd, "=\"", 2);
				++j;
				while (str_array[i][j] != '=' && str_array[i][j] != '\0')
					write(fd, &str_array[i][j++], 1);
				write(fd, "\"\n", 2);
				j = 0;
			}
		}
	}
	else
		write(fd, "\n", 1);
}

int	write_export_array_to_outputs(char **result, t_file_datas *output_lst)
{
	t_file_datas	*current_output;
	int				fd;

	current_output = output_lst;
	while (current_output)
	{
		if (current_output->mode == 1)
			fd = open(current_output->value, O_WRONLY | O_CREAT | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		else
			fd = open(current_output->value, O_WRONLY | O_APPEND | O_CREAT,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (fd == -1)
			print_info_str_error_and_exit(current_output->value);
		if (!current_output->next)
		{
			ft_print_export_array_fd(result, fd);
			return (1);
		}
		close(fd);
		current_output = current_output->next;
	}
	return (0);
}

int	execute_export(t_shell *shell, t_pipe_node *node)
{
	int		i;
	int		result;

	i = 0;
	while (node->arguments[++i])
	{
		printf("arg: [%s]\n", node->arguments[i]);
		result = export(shell, node->arguments[i]);
		if (result != 0)
			return (result);
	}
	return (0);
}

int	builtin_export(t_shell *shell, t_pipe_node *node)
{
	char	**env;

	if (!node->arguments[1])
	{
		env = ft_strdup_array(shell->envp);
		ft_sort_str_array(env);
		ft_print_export_array_fd(env, node->fdio[1]);
		ft_free_str_array(env);
		return (0);
	}
	else if (node->fdio[0] == 1 && node->fdio[1] != 1)
		return (execute_export(shell, node));
	return (0);
}

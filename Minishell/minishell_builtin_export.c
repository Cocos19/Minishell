/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_export.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:58:55 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/12 12:19:53 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	check_export_arg_validity(char *arg)
{
	int	i;

	if (!((arg[0] >= 'a' && arg[0] <= 'z') || (arg[0] >= 'A' && arg[0] <= 'Z')))
	{
		printf("minishell: export: %s: not a valid identifier\n", arg);
		return (EPERM);
	}
	i = 0;
	while (arg[++i])
	{
		if (!((arg[i] >= 'a' && arg[i] <= 'z') || (arg[i] >= 'A' && arg[i] <= 'Z') ||
			(arg[i] >= '0' && arg[i] <= '9')))
		{
			printf("minishell: export: %s: not a valid identifier\n", arg);
			return (EPERM);
		}
	}
	return (0);
}

int	builtin_export(int fd_in, t_shell *shell, t_pipe_node *node, int fd_out)
{
	int		i;
	int		result;
	char	**env;

	i = 0;
	result = open_close_inputs(shell, node->input_file_lst);
	if (result != 0)
		return (result);
	result = open_close_outputs(node->input_file_lst);
	if (result != 0)
		return (result);
	if (!node->arguments[1])
	{
		env = ft_strdup_array(shell->envp);
		ft_sort_str_array(env);
		if (write_export_array_to_outputs(env, node->output_file_lst) == 0)
			ft_print_export_array_fd(env, fd_out);
		ft_free_str_array(env);
		return (0);
	}
	else if (fd_in == -1 && fd_out == 1)
	{
		while (node->arguments[++i])
		{
			if (check_export_arg_validity(node->arguments[i]) != 0)
				return (EPERM);
			result = export(shell, node->arguments[i]);
			if (result != 0)
				return (result);
		}
	}
	return (result);
}

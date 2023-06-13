/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:15:18 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/11 14:31:06 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	str_is_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (2);
	}
	return (0);
}

int	handle_exit_args(t_pipe_node *node)
{
	unsigned char	result;

	if (str_is_digit(node->arguments[1]) != 0)
	{
		printf("minishell: exit: %s: numeric argument required\n",
			node->arguments[1]);
		result = ERR_SYNTAX;
	}
	else if (node->arguments[2])
	{
		printf("minishell: exit: too many arguments\n");
		result = EPERM;
	}
	else
		result = ft_atoi(node->arguments[1]);
	return (result);
}

int	builtin_exit(t_shell *shell, t_pipe_node *node)
{
	int	result;

	result = open_close_inputs(shell, node->input_file_lst);
	if (result != 0)
		return (result);
	result = open_close_outputs(node->input_file_lst);
	if (result != 0)
		return (result);
	if (!node->arguments[1])
		return (0);
	if (node->arguments[1])
		return (handle_exit_args(node));
	return (0);
}

void	handle_single_cmd_exit_args(t_shell *shell, t_pipe_node *node)
{
	unsigned char	result;

	if (str_is_digit(node->arguments[1]) != 0)
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n",
			node->arguments[1]);
		exit (2);
	}
	else if (node->arguments[2])
	{
		printf("minishell: too many arguments\n");
		shell->last_exit_status = EPERM;
	}
	else
	{
		result = ft_atoi(node->arguments[1]);
		printf("exit\n");
		exit (result);
	}
}

void	single_cmd_builtin_exit(t_shell *shell, t_pipe_node *node)
{
	open_close_inputs(shell, node->input_file_lst);
	open_close_outputs(node->output_file_lst);
	if (!node->arguments[1])
	{
		printf("exit\n");
		exit (EXIT_SUCCESS);
	}
	if (node->arguments[1])
		handle_single_cmd_exit_args(shell, node);
}

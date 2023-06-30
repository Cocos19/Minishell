/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:15:18 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/30 14:09:36 by mprofett         ###   ########.fr       */
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
	int				check;
	int				res;

	check = ft_atoi(node->arguments[1], &res);
	if (check == 2)
	{
		printf("minishell: exit: %s: numeric argument required\n",
			node->arguments[1]);
		res = ERR_SYNTAX;
	}
	else if (node->arguments[2])
	{
		printf("minishell: exit: too many arguments\n");
		res = EPERM;
	}
	return ((unsigned char)res);
}

int	builtin_exit(t_shell *shell, t_pipe_node *node)
{
	if (!node->arguments[1])
		return (0);
	if (node->arguments[1])
		return (handle_exit_args(node));
	(void) shell;
	return (0);
}

void	handle_single_cmd_exit_args(t_shell *shell, t_pipe_node *node)
{
	int				check;
	int				res;

	check = ft_atoi(node->arguments[1], &res);
	if (check == 2)
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n",
			node->arguments[1]);
		exit (2);
	}
	else if (node->arguments[2])
	{
		printf("exit\nminishell: exit: too many arguments\n");
		shell->last_exit_status = EPERM;
		return ;
	}
	else if (check == 1)
		res = 255;
	printf("exit\n");
	exit ((unsigned char)res);
}

void	single_cmd_builtin_exit(t_shell *shell, t_pipe_node *node)
{
	if (!node->arguments[1])
	{
		printf("exit\n");
		exit (EXIT_SUCCESS);
	}
	if (node->arguments[1])
		handle_single_cmd_exit_args(shell, node);
}

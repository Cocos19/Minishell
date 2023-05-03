/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:53:01 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/27 11:31:03 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_buitlins(char **arguments)
{
	if (ft_strcmp(arguments[0], "echo"))
	{
		if (ft_strcmp(arguments[1], "-n"))
			return (10);
		else
			return (11);
	}
	else if (ft_strcmp(arguments[0], "cd"))
		return (2);
	else if (ft_strcmp(arguments[0], "pwd"))
		return (3);
	else if (ft_strcmp(arguments[0], "export"))
		return (4);
	else if (ft_strcmp(arguments[0], "unset"))
		return (5);
	else if (ft_strcmp(arguments[0], "env"))
		return (6);
	else if (ft_strcmp(arguments[0], "exit"))
		return (7);
	return (0);
}

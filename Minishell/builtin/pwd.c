/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:14:42 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/26 10:20:37 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(t_shell *shell, t_pipe_node *node)
{
	char	*result;

	result = NULL;
	result = getcwd(result, NAME_MAX);
	if (!result)
		print_str_error_and_exit();
	write(node->fdio[1], result, ft_strlen(result));
	write(node->fdio[1], "\n", 1);
	free(result);
	(void) shell;
	return (0);
}

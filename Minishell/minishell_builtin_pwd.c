/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_pwd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:14:42 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/05 11:29:27 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(t_shell *shell, t_pipe_node *node, int fd_out)
{
	char	*result;

	result = NULL;
	result = getcwd(result, NAME_MAX);
	open_close_inputs(shell, node->input_file_lst);
	if (result)
	{
		if (write_to_outputs(result, node->output_file_lst) == 0)
		{
			write(fd_out, result, ft_strlen(result));
			write(fd_out, "\n", 1);
		}
		if (fd_out != 1 && fd_out != 3)
			close(fd_out);
		free(result);
	}
	else
	{
		printf("%s\n", strerror(errno));
		exit (errno);
	}
	exit(EXIT_SUCCESS);
}

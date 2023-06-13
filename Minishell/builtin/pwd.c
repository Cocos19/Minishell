/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:14:42 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/11 16:00:23 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(t_shell *shell, t_pipe_node *node, int fd_out)
{
	int		redirections_check;
	char	*result;

	result = NULL;
	redirections_check = open_close_inputs(shell, node->input_file_lst);
	if (redirections_check != 0)
		return (redirections_check);
	result = getcwd(result, NAME_MAX);
	if (!result)
		print_str_error_and_exit();
	redirections_check = write_to_outputs(result, node->output_file_lst);
	if (redirections_check != 0)
	{
		free(result);
		return (redirections_check);
	}
	write(fd_out, result, ft_strlen(result));
	write(fd_out, "\n", 1);
	free(result);
	return (0);
}

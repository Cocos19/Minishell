/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:15:31 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/05 11:38:07 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_shell *shell, t_pipe_node *node, int fd_out)
{
	open_close_inputs(shell, node->input_file_lst);
	if (write_array_to_outputs(shell->envp, node->output_file_lst) == 0)
		ft_print_str_array_fd(shell->envp, fd_out);
	if (fd_out != 1 && fd_out != 3)
		close(fd_out);
	exit(EXIT_SUCCESS);
}
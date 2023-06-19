/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:14:42 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/19 10:11:33 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(t_shell *shell, t_pipe_node *node, int fd_out)
{
	int		redirections_check;
	char	*result;

	printf("test3 -> %d\n", fd_out);
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
	printf("test4 -> %d\n", fd_out);
	return (0);
}

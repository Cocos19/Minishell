/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:15:31 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/21 13:32:10 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*This function can be launched in multiples pipe in forks or as a single
pipe in a fork*/

int	builtin_env(t_shell *shell)
{
	// int	redir_check;

	// redir_check = open_close_inputs(shell, node->input_file_lst);
	// if (redir_check != 0)
	// 	return (redir_check);
	// redir_check = write_array_to_outputs(shell->envp, node->output_file_lst);
	// free_file_datas_list(node->input_file_lst);
	// free_file_datas_list(node->input_file_lst);
	// if (redir_check != 0)
	// 	return (redir_check);
	// else
	ft_print_str_array_fd(shell->envp, 1);
	return (0);
}

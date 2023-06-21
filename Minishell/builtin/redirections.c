/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:20:08 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/21 12:58:11 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	print_err_and_return_errno(char *redir_value)
// {
// 	printf("minishell: '%s': %s\n", redir_value, strerror(errno));
// 	return (errno);
// }

// int	open_close_inputs(t_shell *shell, t_file_datas *input_lst)
// {
// 	t_file_datas	*current_input;
// 	int				fd;

// 	current_input = input_lst;
// 	while (current_input)
// 	{
// 		if (current_input->mode == 1)
// 			fd = open(current_input->value, O_RDONLY);
// 		else
// 		{
// 			fd = get_heredoc(shell, current_input->value);
// 			if (g_exit_status == 130)
// 			{
// 				close(fd);
// 				return (130);
// 			}
// 		}
// 		if (fd == -1)
// 			return (print_err_and_return_errno(current_input->value));
// 		close(fd);
// 		current_input = current_input->next;
// 	}
// 	return (0);
// }

// int	write_array_to_outputs(char **result, t_file_datas *output_lst)
// {
// 	t_file_datas	*current_output;
// 	int				fd;

// 	current_output = output_lst;
// 	while (current_output)
// 	{
// 		if (current_output->mode == 1)
// 			fd = open(current_output->value, O_WRONLY | O_CREAT | O_TRUNC,
// 					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
// 		else
// 			fd = open(current_output->value, O_WRONLY | O_APPEND | O_CREAT,
// 					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
// 		if (fd == -1)
// 			return (print_err_and_return_errno(current_output->value));
// 		if (!current_output->next)
// 		{
// 			ft_print_str_array_fd(result, fd);
// 			return (1);
// 		}
// 		close(fd);
// 		current_output = current_output->next;
// 	}
// 	return (0);
// }

// int	write_to_outputs(char *result, t_file_datas *output_lst)
// {
// 	t_file_datas	*current_output;
// 	int				fd;

// 	current_output = output_lst;
// 	while (current_output)
// 	{
// 		if (current_output->mode == 1)
// 			fd = open(current_output->value, O_WRONLY | O_CREAT | O_TRUNC,
// 					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
// 		else
// 			fd = open(current_output->value, O_WRONLY | O_APPEND | O_CREAT,
// 					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
// 		if (fd == -1)
// 			return (print_err_and_return_errno(current_output->value));
// 		if (!current_output->next)
// 		{
// 			write(fd, result, ft_strlen(result));
// 			write(fd, "\n", 1);
// 			return (0);
// 		}
// 		close(fd);
// 		current_output = current_output->next;
// 	}
// 	return (0);
// }

// int	open_close_outputs(t_file_datas *output_lst)
// {
// 	t_file_datas	*current_output;
// 	int				fd;

// 	current_output = output_lst;
// 	while (current_output)
// 	{
// 		if (current_output->mode == 1)
// 			fd = open(current_output->value, O_WRONLY | O_CREAT | O_TRUNC,
// 					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
// 		else
// 			fd = open(current_output->value, O_WRONLY | O_APPEND | O_CREAT,
// 					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
// 		if (fd == -1)
// 			return (print_err_and_return_errno(current_output->value));
// 		close(fd);
// 		current_output = current_output->next;
// 	}
// 	return (0);
// }

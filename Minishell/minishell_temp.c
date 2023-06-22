/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_temp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:34:18 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/22 10:28:18 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_list_infos(t_token *lst)
{
	t_token	*temp;

	temp = lst;
	while (temp)
	{
		if (temp->value)
			printf("token is:%s\n", temp->value);
		temp = temp->next;
	}
}

void	print_fd_content(int fd)
{
	char	*str;

	str = get_next_line(fd, 10);
	while (str)
	{
		printf("%s", str);
		free(str);
		str = get_next_line(fd, 10);
	}
	close(fd);
}

void	print_file_datas_lst(t_file_datas *datas_lst)
{
	t_file_datas	*lst;
	int				i;

	lst = datas_lst;
	i = 0;
	while (lst)
	{
		printf("File %d\n mode: %d\n value: %s\n", ++i, lst->mode, lst->value);
		lst = lst->next;
	}
}

void	print_redir_datas_lst(t_redir_datas *datas_lst)
{
	t_redir_datas	*lst;
	int				i;

	lst = datas_lst;
	i = 0;
	while (lst)
	{
		printf("File %d\n type: %c mode: %d\n value: %s\n", ++i, lst->type, lst->mode, lst->value);
		lst = lst->next;
	}
}

// void	print_pipe_lst_content(t_shell *shell, t_pipe_node *pipe_lst)
// {
// 	t_pipe_node	*current;
// 	int			i;

// 	current = pipe_lst;
// 	i = -1;
// 	while (current)
// 	{
// 		if (current->arguments)
// 		{
// 			while (current->arguments[++i])
// 			{
// 				if (i == 0 && ft_strcmp("echo", current->arguments[i]) == 0)
// 					builtin_echo(-1, shell, current, 1);
// 				if (i == 0 && ft_strcmp("export", current->arguments[i]) == 0)
// 					builtin_export(shell, current, 1);
// 				if (i == 0 && ft_strcmp("pwd", current->arguments[i]) == 0)
// 					builtin_pwd(-1, shell, current, 1);
// 				if (i == 0 && ft_strcmp("env", current->arguments[i]) == 0)
// 					builtin_env(-1, shell, current, 1);
// 				if (i == 0 && ft_strcmp("unset", current->arguments[i]) == 0)
// 					builtin_unset(shell, current);
// 				if (i == 0 && ft_strcmp("exit", current->arguments[i]) == 0)
// 					builtin_exit(shell, current);
// 				if (i == 0 && ft_strcmp("cd", current->arguments[i]) == 0)
// 					builtin_cd(-1, shell, current, 1);
// 			}
// 			i = -1;
// 		}
// 		if (current->input_file_lst)
// 		{
// 			printf("Input file list:\n");
// 			print_file_datas_lst(current->input_file_lst);
// 		}
// 		if (current->output_file_lst)
// 		{
// 			printf("Output file list:\n");
// 			print_file_datas_lst(current->output_file_lst);
// 		}
// 		current = current->next;
// 		printf("*************\n");
// 	}
// 	(void) shell;
// }

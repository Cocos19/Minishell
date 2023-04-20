/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_temp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:34:18 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/19 17:47:59 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_list_infos(t_token *lst)
{
	t_token *temp;

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
	char *str;

	str = get_next_line(fd, 10);
	while (str)
	{
		printf("%s", str);
		free(str);
		str = get_next_line(fd, 10);
	}
	close(fd);
}

void	print_pipe_lst_content(t_pipe_node *pipe_lst)
{
	t_pipe_node	*current;
	int			i;

	current = pipe_lst;
	i = -1;
	while (current)
	{
		if (current->arguments)
		{
			while(current->arguments[++i])
				printf("argv[%d]: %s\n", i, current->arguments[i]);
			i = -1;
		}
		printf("input file fd: %d\n", current->input_file_fd);
		printf("output file fd: %d\n", current->output_file_fd);
		i = -1;
		current = current->next;
	}
}

// void	init_some_locales_variables(t_shell *shell)
// {
// 	add_new_locale_variable(shell, ft_strdup("var2"), ft_strdup("second locale variable"));
// 	add_new_locale_variable(shell, ft_strdup("var3"), ft_strdup("third locale variable"));
// 	add_new_locale_variable(shell, ft_strdup("var4"), ft_strdup("fourth locale variable"));
// 	add_new_locale_variable(shell, ft_strdup("var5"), ft_strdup("fifth locale variable"));
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_temp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:34:18 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/18 11:03:43 by mprofett         ###   ########.fr       */
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
	t_pipe_node 	*current;
	t_input_file 	*current_input_file_lst;
	t_output_file 	*current_output_file_lst;
	t_local_var 	*current_temp_var_lst;
	int			i;

	current = pipe_lst;
	i = -1;
	printf("la ca va\n");
	while (current)
	{
		if (current->arguments)
		{
			while(current->arguments[++i])
				printf("argv[%d]: %s\n", i, current->arguments[i]);
			i = -1;
		}
		current_input_file_lst = current->input_file_lst;
		while (current_input_file_lst)
		{
			++i;
			if (current_input_file_lst->name)
				printf("input_file %d name: %s. Fd: %d\n", i, current_input_file_lst->name, current_input_file_lst->fd);
			else
				printf("input_file %d is heredoc. Fd: %d\n", i, current_input_file_lst->fd);
			current_input_file_lst = current_input_file_lst->next;
		}
		i = -1;
		current_output_file_lst = current->output_file_lst;
		while (current_output_file_lst)
		{
			++i;
			printf("output_file %d name: %s. is in happen mode: %d\n", i, current_output_file_lst->name, current_output_file_lst->in_happend_mode);
			current_output_file_lst = current_output_file_lst->next;
		}
		i = -1;
		current_temp_var_lst = current->temp_varlist;
		while (current_temp_var_lst)
		{
			++i;
			printf("temp_var %d name: %s. var value is: %s\n", i, current_temp_var_lst->name, current_temp_var_lst->value);
			current_temp_var_lst = current_temp_var_lst->next;
		}
		i = -1;
		current = current->next;
	}
}

void	init_some_locales_variables(t_shell *shell)
{
	add_new_locale_variable(shell, ft_strdup("var2"), ft_strdup("second locale variable"));
	add_new_locale_variable(shell, ft_strdup("var3"), ft_strdup("third locale variable"));
	add_new_locale_variable(shell, ft_strdup("var4"), ft_strdup("fourth locale variable"));
	add_new_locale_variable(shell, ft_strdup("var5"), ft_strdup("fifth locale variable"));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_temp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:34:18 by mprofett          #+#    #+#             */
/*   Updated: 2023/07/04 09:08:40 by mprofett         ###   ########.fr       */
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

void	print_redir_datas_lst(t_redir_datas *datas_lst)
{
	t_redir_datas	*lst;
	int				i;

	lst = datas_lst;
	i = 0;
	while (lst)
	{
		printf("File %d\n type: %c mode: %d\n value: %s\n",
			++i, lst->type, lst->mode, lst->value);
		lst = lst->next;
	}
}

void	print_pipe_lst_content(t_shell *shell)
{
	t_pipe_node	*lst;
	int			i;
	int			j;

	lst = shell->pipe_lst;
	if (lst)
	{
		j = 0;
		while (lst)
		{
			printf("node %d\n", j);
			if (lst->arguments)
			{
				i = -1;
				while (lst->arguments[++i])
					printf("value arg %d: [%s]\n", i, lst->arguments[i]);
				printf("end of argv on arg %d\n", i);
			}
			if (lst->in_out_redir_list)
				print_redir_datas_lst(lst->in_out_redir_list);
			lst = lst->next;
			++j;
		}
		printf("end of pipe lst on node %d\n", j);
	}
}

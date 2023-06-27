/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_open_close.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:35:04 by cmartino          #+#    #+#             */
/*   Updated: 2023/06/27 12:01:57 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open_infile(t_shell *shell, t_redir_datas *input_lst)
{
	int				fd;
	t_redir_datas	*temp_lst;

	temp_lst = input_lst;
	if (input_lst->mode == 1)
		fd = open(input_lst->value, O_RDONLY);
	else
	{
		printf("heredoc -> to do\n");
		exit(0);
	}
	if (fd == -1)
	{
		perror(input_lst->value);
		ft_exit_cmd(shell, 127);
	}
	while(temp_lst)
	{
		temp_lst = temp_lst->next;
		if (temp_lst)
		{
			if (temp_lst->type == 'i')
			{
				ft_close(fd, input_lst->value);
				temp_lst = temp_lst->last;
			}
		}
	}
	return (fd);
}

int	ft_open_outfile(t_shell *shell, t_redir_datas *output_lst)
{
	int				fd;
	t_redir_datas	*temp_lst;

	temp_lst = output_lst;
	if (output_lst->mode == 1)
		fd = open(output_lst->value,
				O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	else
	{
		fd = open(output_lst->value,
				O_WRONLY | O_APPEND | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	}
	if (fd == -1)
	{
		perror(output_lst->value);
		ft_exit_cmd(shell, 127);
	}
	while(temp_lst)
	{
		temp_lst = temp_lst->next;
		if (temp_lst)
		{
			if (temp_lst->type == 'o')
			{
				ft_close(fd, output_lst->value);
				temp_lst = temp_lst->last;
			}
		}
	}
	return (fd);
}

/* ft_close_files : // a voir quelle erreur a renvoyer + exit_code ?
	ft_close : quelle erreur renvoyer ? */

void	ft_close(int fd, char *msg)
{
	if (close(fd) == -1)
	{
		perror(msg);
	}
}

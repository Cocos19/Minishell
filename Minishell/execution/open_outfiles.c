/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 13:27:28 by cmartino          #+#    #+#             */
/*   Updated: 2023/07/05 10:51:57 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		write(1, "minishell: ", 11);
		perror(output_lst->value);
		ft_exit_cmd(shell, 127);
	}
	else
		next_file(temp_lst, fd, output_lst->value, 'o');
	return (fd);
}
 
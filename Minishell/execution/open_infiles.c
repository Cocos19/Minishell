/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 13:27:15 by cmartino          #+#    #+#             */
/*   Updated: 2023/07/05 10:49:26 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open_infile(t_shell *shell, t_redir_datas *input_lst)
{
	int				fd;
	t_redir_datas	*temp_lst;

	temp_lst = input_lst;
	fd = open(input_lst->value, O_RDONLY);
	if (fd == -1)
	{
		write(1, "minishell: ", 11);
		perror(input_lst->value);
		ft_exit_cmd(shell, 127);
	}
	else
		next_file(temp_lst, fd, input_lst->value, 'i');
	return (fd);
}

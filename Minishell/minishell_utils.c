/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:09:02 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/20 13:46:50 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_protected(t_shell *shell, char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (!result)
		free_and_print_strerror(shell);
	return (result);
}

void	shell_fd_control(t_shell *shell, char operation, int i)
{
	if (operation == '+')
		shell->fd_opened += i;
	else
		shell->fd_opened -= i;
	if (shell->fd_opened > FOPEN_MAX)
	{
		printf("minishell: Max opened fd limit reached\n");
		free_shell(shell);
		exit(EXIT_FAILURE);
	}
}

void	close_fd(t_shell *shell, int fd)
{
	shell_fd_control(shell, '-', 1);
	close(fd);
}

char	*get_string_from_fd(t_shell *shell, int fd)
{
		char	*str;
		char	*temp;
		char	*result;

		str = get_next_line(fd, 100);
		result = NULL;
		while (str)
		{
			temp = ft_strjoin_protected(shell, result, str);
			free(str);
			if (result)
				free(result);
			result = temp;
			str = get_next_line(fd, 100);
		}
		return (result);
}

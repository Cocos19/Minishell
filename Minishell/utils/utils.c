/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:09:02 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/29 10:31:36 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_protected(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (!result)
		print_str_error_and_exit();
	return (result);
}

int	lstsize_cmd(t_pipe_node *cmd)
{
	int			i;
	t_pipe_node	*tmp;

	i = 0;
	if (!cmd)
		return (0);
	tmp = cmd;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	*get_string_from_fd(int fd)
{
	char	*str;
	char	*temp;
	char	*result;

	str = get_next_line(fd, 100);
	result = NULL;
	while (str)
	{
		temp = ft_strjoin_protected(result, str);
		free(str);
		if (result)
			free(result);
		result = temp;
		str = get_next_line(fd, 100);
	}
	return (result);
}

void	find_path(t_shell *shell, t_pipe_node *pipe)
{
	char	*cmd;
	char	*cmd_final;

	cmd = cmd_exist(shell, shell->envp, pipe->arguments);
	printf("cmd = %s\n", cmd);
	if (shell->exit == 0)
	{
		free(cmd);
		return ;
	}
	cmd_final = ft_strjoin_protected(cmd, "/");
	free(cmd);
	pipe->path = ft_strjoin_protected(cmd_final, pipe->arguments[0]);
	free(cmd_final);
}

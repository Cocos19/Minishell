/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:09:02 by mprofett          #+#    #+#             */
/*   Updated: 2023/07/04 13:17:40 by cmartino         ###   ########.fr       */
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

void	find_path(t_shell *shell, t_pipe_node *pipe)
{
	char	*cmd;
	char	*cmd_final;

	cmd_final = NULL;
	cmd = cmd_exist(shell, shell->envp, pipe->arguments);
	if (shell->exit == 0 || shell->exit == 3)
	{
		if (shell->exit == 3)
		{
			write(1, "minishell: ", 11);
			write(1, pipe->arguments[0], ft_strlen(pipe->arguments[0]));
			write(1, ": No such file or directory\n", 28);
		}
		pipe->path = NULL;
		return ;
	}
	if (cmd != NULL)
	{
		cmd_final = ft_strjoin_protected(cmd, "/");
		free(cmd);
	}
	pipe->path = ft_strjoin_protected(cmd_final, pipe->arguments[0]);
	free(cmd_final);
}

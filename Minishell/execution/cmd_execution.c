/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:06:23 by cmartino          #+#    #+#             */
/*   Updated: 2023/06/27 11:52:49 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_path(t_shell *shell, t_pipe_node *pipe)
{
	char	*cmd;
	char	*cmd_final;

	cmd = cmd_exist(shell, shell->envp, pipe->arguments);
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

static int	lstsize_cmd(t_pipe_node *cmd)
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

static int	*create_mini_pipe(void)
{
	int	*array;

	array = malloc(sizeof(int) * 2);
	if (!array)
		return (NULL);
	return (array);
}

int	**init_pipes(int nbr_pipes)
{
	int	i;
	int	**array;

	array = malloc(sizeof(int *) * (nbr_pipes + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (i < nbr_pipes)
	{
		array[i] = create_mini_pipe();
		i++;
	}
	array[i] = NULL;
	return (array);
}

int	ft_pipe2(int **array, int pos)
{
	int	ret;

	ret = pipe(array[pos]);
	return (ret);
}

void	ft_close_children(int pos, t_shell *shell, t_pipe_node *cmd)
{
	if (shell->nbr_cmds <= 1)
		return ;
	if (pos == 0)
	{
		ft_close(shell->pipefd[0][0], 0);
		if (cmd->iofiles[1] == 1)
			ft_close(shell->pipefd[0][1], 0);
	}
	if (pos == shell->nbr_cmds - 1 && cmd->iofiles[0] == 1)
		ft_close(shell->pipefd[pos - 1][0], 0);
	if (pos < shell->nbr_cmds - 1 && pos > 0)
	{
		ft_close(shell->pipefd[pos][0], 0);
		if (cmd->iofiles[0] == 1)
			ft_close(shell->pipefd[pos - 1][0],0);
		if (cmd->iofiles[1] == 1)
			ft_close(shell->pipefd[pos][1], 0);
	}
}

void	ft_children(t_shell *shell, t_pipe_node *cmd, int pos)
{
	ft_close_children(pos, shell, cmd);
	if (pos == 0)
		first_cmd(shell, shell->pipe_lst);
	else if (pos == shell->nbr_cmds - 1)
		last_cmd(shell, cmd, pos);
	else
		middle_cmd(shell, cmd, pos);
	if (redirection_builtin(shell, cmd) == 0)
		execve(cmd->path, cmd->arguments, shell->envp);
	exit(EXIT_FAILURE);
}

void	ft_close_parent(int pos, t_pipe_node *cmd, t_shell *shell)
{
	if (cmd->iofiles[0] == 1)
		ft_close(cmd->fdio[0], 0);
	if (cmd->iofiles[1] == 1)
		ft_close(cmd->fdio[1],0);
	if (shell->nbr_cmds <= 1)
		return ;
	if (pos == 0)
		ft_close(shell->pipefd[0][1], 0);
	else if (pos > 0 && pos == shell->nbr_cmds - 1)
		ft_close(shell->pipefd[shell->nbr_cmds - 2][0], 0);
	else if (pos > 0 && pos < shell->nbr_cmds - 1)
	{
		ft_close(shell->pipefd[pos - 1][0],0);
		ft_close(shell->pipefd[pos][1],0);
	}
}

void	execution(t_shell *shell)
{
	t_pipe_node	*cmd;
	int			i;

	cmd = shell->pipe_lst;
	shell->exit = 1;
	if (!cmd->next && is_builtin(cmd))
	{
		execution_single_cmd(shell, cmd);
		return ;
	}
	shell->nbr_cmds = lstsize_cmd(cmd);
	shell->pipefd = init_pipes(shell->nbr_cmds);
	create_pids(shell, cmd);
	i = 0;
	while (cmd)
	{
		cmd->iofiles[0] = 0;
		cmd->iofiles[1] = 0;
		if (cmd->next)
			ft_pipe2(shell->pipefd, i);
		if (cmd->in_out_redir_list)
			openiofile(shell, cmd, cmd->in_out_redir_list);
		shell->pids[i] = ft_fork(shell);
		if (shell->pids[i] == -1)
			return ;
		if (shell->pids[i] == 0)
			ft_children(shell, cmd, i);
		ft_close_parent(i, cmd, shell);
		cmd = cmd->next;
		i++;
	}
	ft_waitpids(shell);
}

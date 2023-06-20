/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:09:02 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/20 15:37:42 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_empty_env_array(t_shell *shell)
{
	shell->envp = malloc(sizeof(char *));
	if (!shell->envp)
		print_str_error_and_exit();
	shell->envp[0] = NULL;
}

char	*ft_strjoin_protected(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (!result)
		print_str_error_and_exit();
	return (result);
}

int	len_tab(char **tb)
{
	int	i;

	i = 0;
	if (!tb)
		return (0);
	while (tb[i])
		++i;
	return (i);
}

int	ft_lstsize_pipe(t_pipe_node *lst)
{
	int		result;

	if (!lst)
		return (0);
	result = 1;
	while (lst->next)
	{
		lst = lst->next;
		result++;
	}
	return (result);
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

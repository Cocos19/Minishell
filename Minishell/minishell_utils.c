/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:09:02 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/08 13:28:24 by cmartino         ###   ########.fr       */
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

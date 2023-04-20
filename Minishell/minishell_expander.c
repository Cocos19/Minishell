/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expander.c		                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:46:52 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/20 10:31:54 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(t_shell *shell, char *str)
{
	char	*new_str;
	int		new_str_len;
	int		i;

	new_str_len = ft_strlen(str) - 2;
	new_str = malloc(sizeof(char) * new_str_len + 1);
	if (!new_str)
		free_and_print_strerror(shell);
	i = -1;
	while (++i < new_str_len)
		new_str[i] = str[i + 1];
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

char	*is_an_envp_var(t_shell *shell, char *str)
{
	char	*result;
	int		var_len;
	int		i;

	i = -1;
	var_len = ft_strlen(str);
	while (shell->envp[++i])
	{
		if (ft_strncmp(shell->envp[i], str, var_len) == 0)
		{
			result = ft_substr(shell->envp[i], var_len,
				ft_strlen(shell->envp[i]) - var_len);
			return (result);
		}
	}
	return (NULL);
}

char	*expand_var(t_shell *shell, char *str)
{
	char	*temp;
	char	*var_to_expand;
	char	*var_to_search;
	int		i;

	i = -1;
	while(str && str[++i])
	{
		if (str[i] == '$')
		{
			temp = ft_substr(str, i + 1, ft_strlen(str) - i + 1);
			var_to_search = ft_strjoin_protected(shell, temp, "=");
			free(temp);
			var_to_expand = (is_an_envp_var(shell, var_to_search));
			if (var_to_expand)
				temp = ft_expand(str, str + i, var_to_search, var_to_expand);
			else
				temp = ft_expand(str, str + i, var_to_search, "");
			free(var_to_search);
			free(var_to_expand);
			free(str);
			return(temp);
		}
	}
	return (str);
}

void	expander(t_shell *shell)
{
	t_pipe_node *node;
	int			i;

	node = shell->pipe_lst;
	i = -1;
	while (node)
	{
		while (node->arguments && node->arguments[++i])
		{
			if (node->arguments[i][0] == '\'')
				node->arguments[i] = remove_quotes(shell, node->arguments[i]);
			else
			{
				if (node->arguments[i][0] == '\"')
					node->arguments[i]
						= remove_quotes(shell, node->arguments[i]);
				node->arguments[i] = expand_var(shell, node->arguments[i]);
			}
		}
		i = -1;
		node = node->next;
	}
}

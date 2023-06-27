/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:17:21 by cmartino          #+#    #+#             */
/*   Updated: 2023/06/27 14:18:06 by cmartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	init_empty_env_array(t_shell *shell)
{
	shell->envp = malloc(sizeof(char *));
	if (!shell->envp)
		print_str_error_and_exit();
	shell->envp[0] = NULL;
}

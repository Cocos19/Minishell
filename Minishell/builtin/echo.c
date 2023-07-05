/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:03:59 by mprofett          #+#    #+#             */
/*   Updated: 2023/07/05 09:12:41 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_and_free_input(char *input, char *to_add)
{
	char	*result;

	result = ft_strjoin_protected(input, to_add);
	free(input);
	return (result);
}

int	check_n_arg_validity(char *arg)
{
	int	i;

	if (ft_strncmp("-n", arg, 2) == 0)
	{
		i = 1;
		while (arg[++i])
		{
			if (!(arg[i] == 'n'))
				return (1);
		}
		return (0);
	}
	return (1);
}

char	*get_echo_result(char **argv)
{
	char	*result;
	int		i;
	int		n_option;

	if (!argv[1])
		return (ft_strdup("\n"));
	i = 0;
	n_option = check_n_arg_validity(argv[1]);
	if (n_option == 0)
		while (argv[i + 1] && check_n_arg_validity(argv[i + 1]) == 0)
			++i;
	result = malloc(sizeof(char));
	if (!result)
		print_str_error_and_exit();
	result[0] = '\0';
	while (argv[++i])
	{
		if (result[0] != '\0')
			result = ft_strjoin_and_free_input(result, " ");
		result = ft_strjoin_and_free_input(result, argv[i]);
	}
	if (n_option != 0)
		result = ft_strjoin_and_free_input(result, "\n");
	return (result);
}

int	builtin_echo(t_shell *shell, t_pipe_node *node)
{
	char	*result;

	result = get_echo_result(node->arguments);
	write(1, result, ft_strlen(result));
	free(result);
	(void) shell;
	return (0);
}

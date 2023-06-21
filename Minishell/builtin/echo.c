/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:03:59 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/21 12:58:55 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*This function can be launched in multiples pipe in forks or
as a single pipe in a fork*/

char	*ft_strjoin_and_free_input(char *input, char *to_add)
{
	char	*result;

	result = ft_strjoin_protected(input, to_add);
	free(input);
	return (result);
}

char	*get_echo_result(char **argv)
{
	char	*result;
	int		i;
	int		n_option;

	result = malloc(sizeof(char));
	if (!result)
		print_str_error_and_exit();
	result[0] = '\0';
	if (!argv[1])
		return (result);
	i = 0;
	n_option = ft_strcmp("-n", argv[1]);
	if (n_option == 0)
		++i;
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
	// int		redirections_check;

	// redirections_check = open_close_inputs(shell, node->input_file_lst);
	// if (redirections_check != 0)
	// 	return (redirections_check);
	result = get_echo_result(node->arguments);
	// if (node->output_file_lst)
	// {
	// 	redirections_check = write_to_outputs(result, node->output_file_lst);
	// 	if (redirections_check != 0)
	// 	{
	// 		free(result);
	// 		return (redirections_check);
	// 	}
	// }
	// else
		write(node->fdio[1], result, ft_strlen(result));
	free(result);
	(void) shell;
	return (0);
}

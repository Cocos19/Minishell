/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_echo.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:03:59 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/09 12:08:40 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_and_free_input(t_shell *shell, char *input, char *to_add)
{
	char	*result;

	result = ft_strjoin_protected(shell, input, to_add);
	free(input);
	return (result);
}

char	*get_echo_result(t_shell *shell, char **argv)
{
	char	*result;
	int		i;
	int		n_option;

	result = malloc(sizeof(char));
	if (!result)
		free_and_print_strerror(shell);
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
			result = ft_strjoin_and_free_input(shell, result, " ");
		result = ft_strjoin_and_free_input(shell, result, argv[i]);
	}
	if (n_option != 0)
		result = ft_strjoin_and_free_input(shell, result, "\n");
	return (result);
}

void	builtin_echo(t_shell *shell, t_pipe_node *node, int fd_out)
{
	char	*result;

	result = get_echo_result(shell, node->arguments);
	open_close_inputs(shell, node->input_file_lst);
	if (write_to_outputs(result, node->output_file_lst) == 0)
		write(fd_out, result, ft_strlen(result));
	if (fd_out != 1 && fd_out != 3)
		close(fd_out);
	free(result);
	exit(EXIT_SUCCESS);
}

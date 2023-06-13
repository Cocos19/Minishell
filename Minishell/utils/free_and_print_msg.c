/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_print_msg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:12:43 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/09 16:09:52 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_str_error_and_exit(void)
{
	printf("minishell: %s\n", strerror(errno));
	exit (errno);
}

void	print_info_str_error_and_exit(char *info)
{
	printf("minishell: '%s': %s\n", info, strerror(errno));
	exit (errno);
}

void	print_builtin_info_str_error_and_exit(char *builtin, char *info)
{
	printf("minishell: %s: %s: %s\n", builtin, info, strerror(errno));
	exit (errno);
}

void	print_info_and_exit(char *info, int exit_status)
{
	printf("%s", info);
	exit (exit_status);
}

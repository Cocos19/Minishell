/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_print_msg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:12:43 by mprofett          #+#    #+#             */
/*   Updated: 2023/07/04 09:17:48 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_str_error_and_exit(void)
{
	printf("minishell: %s\n", strerror(errno));
	exit (errno);
}

void	print_info_and_exit(char *info, int exit_status)
{
	printf("%s", info);
	exit (exit_status);
}

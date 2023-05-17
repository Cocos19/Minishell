/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_array_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:25:29 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/08 10:47:36 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_str_array_fd(char **str_array, int fd)
{
	int	i;

	i = -1;
	if (str_array)
	{
		while (str_array && str_array[++i])
		{
			write(fd, str_array[i], ft_strlen(str_array[i]));
			write(fd, "\n", 1);
		}
	}
	else
		write(fd, "\n", 1);
}

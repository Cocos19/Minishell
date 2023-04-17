/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hexa_char_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 11:06:56 by mprofett          #+#    #+#             */
/*   Updated: 2022/11/26 11:06:58 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_put_hexa_char_fd(char c, int lowercase, int fd)
{
	char	a;

	if (c >= 10 && c <= 16)
	{
		if (lowercase == 0)
			a = c + 55;
		else
			a = c + 87;
		write(fd, &a, 1);
	}
	else
	{
		a = c + 48;
		write(fd, &a, 1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:13:43 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/04 19:05:38 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_str_array(char **str_array)
{
	int	i;

	i = -1;
	if (str_array)
	{
		while (str_array && str_array[++i])
			ft_printf("%s\n", str_array[i]);
	}
	else
		write(1, "\n", 1);
}

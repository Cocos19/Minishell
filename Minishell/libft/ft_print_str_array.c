/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:38:00 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/19 14:38:59 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_str_array(char **str_array)
{
	int	i;

	i = -1;
	while (str_array && str_array[++i])
		ft_printf("%s\n", str_array[i]);
}

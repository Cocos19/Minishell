/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_all_but_character.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:07:49 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/03 12:08:12 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_skip_all_but_character(char	*str, char c)
{
	while (str && *str && *str != c)
		++str;
	return (str);
}

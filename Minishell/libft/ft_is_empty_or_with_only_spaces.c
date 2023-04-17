/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_empty_or_with_only_spaces.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:18:27 by mprofett          #+#    #+#             */
/*   Updated: 2023/04/06 14:19:52 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_empty_or_with_only_spaces(const char *str)
{
	int	i;

	i = 0;
	while (*(str + i) && *(str + i) == ' ')
		++i;
	if (*(str + i) == '\0')
		return (1);
	return (0);
}

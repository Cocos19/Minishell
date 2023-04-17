/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:26:35 by mprofett          #+#    #+#             */
/*   Updated: 2023/03/30 15:38:19 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_expand(char *str, char *start, char *cut, char *paste)
{
	char		*new_str;
	char		*result;
	char		*old_str;
	size_t		len;

	len = ft_strlen(str) - ft_strlen(cut) + ft_strlen(paste);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	old_str = str;
	result = new_str;
	while (old_str != start)
		*(new_str++) = *(old_str++);
	*new_str = '\0';
	len = -1;
	while (++len < ft_strlen(paste))
		*(new_str++) = *(paste + len);
	len = -1;
	while (++len < ft_strlen(cut))
		++old_str;
	while (*old_str)
		*(new_str++) = *(old_str++);
	*new_str = '\0';
	return (result);
}

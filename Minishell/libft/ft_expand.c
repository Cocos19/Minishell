/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartino <cmartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:26:35 by mprofett          #+#    #+#             */
/*   Updated: 2023/07/05 09:09:28 by cmartino         ###   ########.fr       */
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
	if (!new_str || !str)
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
	while (old_str && *old_str)
		*(new_str++) = *(old_str++);
	*new_str = '\0';
	return (result);
}

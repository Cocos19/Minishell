/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:19:17 by mprofett          #+#    #+#             */
/*   Updated: 2023/03/01 11:52:55 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_nbr_of_str(char const *s, char c)
{
	int	nbr_of_str;

	nbr_of_str = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			nbr_of_str++;
		while (*s != c && *s)
			s++;
	}
	return (nbr_of_str);
}

static char	*get_next_str(char const *s, char c)
{
	char	*next_str;
	int		nbr_of_char;

	nbr_of_char = 0;
	while (*(s + nbr_of_char) != c && *(s + nbr_of_char))
		nbr_of_char++;
	next_str = malloc(sizeof(char) * (nbr_of_char + 1));
	if (!next_str)
		return (NULL);
	*(next_str + nbr_of_char) = '\0';
	while (nbr_of_char-- > 0)
		*(next_str + nbr_of_char) = *(s + nbr_of_char);
	return (next_str);
}

char	**ft_split(char const *s, char c)
{
	char	**str_array;
	char	**str_array_start;

	if (!s)
		return (NULL);
	str_array = malloc(sizeof(char *) * (count_nbr_of_str(s, c) + 1));
	if (!str_array)
		return (NULL);
	str_array_start = str_array;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			*str_array = get_next_str(s, c);
			if (!*str_array)
				return (ft_free_str_array(str_array_start));
			str_array++;
		}
		while (*s != c && *s)
			s++;
	}
	*str_array = NULL;
	return (str_array_start);
}

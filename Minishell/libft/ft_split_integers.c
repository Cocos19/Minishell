/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_integers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:01:36 by mprofett          #+#    #+#             */
/*   Updated: 2022/12/31 12:01:39 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_nbr_of_int(char const *s)
{
	int	nbr_of_int;

	nbr_of_int = 0;
	while (*s)
	{
		while (*s == ' ')
			s++;
		if (*s)
			nbr_of_int++;
		while (*s != ' ' && *s)
			s++;
	}
	return (nbr_of_int);
}

static int	*free_int_array(int *int_array)
{
	free(int_array);
	return (NULL);
}

static long long int	get_next_int(char const *s)
{
	char			*temp_str;
	long long int	result;
	int				i;

	i = 0;
	while (s[i] != ' ' && s[i])
		++i;
	temp_str = malloc(sizeof(char) * (i + 1));
	if (!temp_str)
	{
		result = INT_MAX;
		return (++result);
	}
	i = 0;
	while (*s && *s != ' ')
	{
		temp_str[i++] = *s;
		s++;
	}
	temp_str[i] = '\0';
	result = safe_atoi(temp_str);
	free(temp_str);
	return (result);
}

int	*fill_tab(char const *s, int *result)
{
	long long int	temp_int;
	int				i;

	i = 0;
	while (*s)
	{
		while (*s == ' ')
			s++;
		if (*s)
		{
			temp_int = get_next_int(s);
			if (temp_int > INT_MAX)
				return (free_int_array(result));
			result[i++] = temp_int;
		}
		while (*s != ' ' && *s)
			s++;
	}
	return (result);
}

int	*ft_split_integers(char const *s)
{
	int				*result;
	int				tab_len;

	tab_len = count_nbr_of_int(s);
	if (tab_len == 0)
		return (NULL);
	result = malloc(sizeof(int) * tab_len);
	if (!result)
		return (NULL);
	return (fill_tab(s, result));
}

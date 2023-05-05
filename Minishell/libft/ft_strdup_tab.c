/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:45:31 by cmartino          #+#    #+#             */
/*   Updated: 2023/05/03 15:16:15 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_tab(const char **tab)
{
	int	len;

	len = 0;
	if (!tab)
		return (-1);
	while (tab[len])
		++len;
	return (len);
}

char	**ft_strdup_tab(const char **tab)
{
	char	**result;
	int		i;
	int		j;
	int		len_tab;

	i = 0;
	len_tab = ft_len_tab(tab);
	if (len_tab == -1)
		return (NULL);
	result = malloc(sizeof(char *) * len_tab + 1);
	if (!result)
		exit(EXIT_FAILURE);
	while (i < len_tab)
	{
		result[i] = malloc (sizeof(char) * ft_strlen(tab[i]) + 1);
		if (!result)
			exit(EXIT_FAILURE);
		j = 0;
		while(tab[i][j])
		{
			result[i][j] = tab[i][j];
			++j;
		}
		result[i][j] = '\0';
	}
	result[i] = NULL;
	return (result);
}

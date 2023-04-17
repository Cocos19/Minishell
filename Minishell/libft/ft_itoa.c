/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:21:36 by mprofett          #+#    #+#             */
/*   Updated: 2022/10/05 10:04:56 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	get_length(int n)
{
	int		result;

	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		result = 2;
		n *= -1;
	}
	else
		result = 1;
	while (n / 10 > 0)
	{
		result++;
		n /= 10;
	}
	return (result);
}

char	*fill_n(char *result, int n, int i)
{
	result[i] = (n % 10) + '0';
	if (n / 10 > 0)
		fill_n(result, (n / 10), (i - 1));
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		i;

	result = (char *)malloc(sizeof(char) * (get_length(n) + 1));
	if (!result)
		return (NULL);
	i = get_length(n) - 1;
	result[i + 1] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		if (n == -2147483648)
		{
			result[1] = '2';
			n += 2000000000;
		}
		n *= -1;
	}
	return (fill_n(result, n, i));
}

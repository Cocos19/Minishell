/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:23:21 by mprofett          #+#    #+#             */
/*   Updated: 2022/10/04 16:23:23 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long int	get_result(const char *str, int i, int sign)
{
	unsigned long long int	result;

	result = 0;
	while (ft_isdigit(*(str + i)))
	{
		result = result * 10 + *(str + i) - '0';
		if (result > 9223372036854775807)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
		i++;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	sign = 1;
	i = 0;
	while (*(str + i) == ' ' || (*(str + i) >= 9 && *(str + i) <= 13))
		i++;
	if (*(str + i) == '-' || *(str + i) == '+')
	{
		if (*(str + i) == '-')
			sign = -1;
		i++;
	}
	result = get_result(str, i, sign);
	return (result * sign);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:23:21 by mprofett          #+#    #+#             */
/*   Updated: 2023/06/21 13:59:55 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str, int *n)
{
	long long int	result;
	int				sign;
	int				i;

	result = 0;
	sign = 1;
	i = 0;
	while (*(str + i) == ' ' || (*(str + i) >= 9 && *(str + i) <= 13))
		i++;
	if (*(str + i) == '-' || *(str + i) == '+')
		if (*(str + i++) == '-')
			sign = -1;
	if (!*(str + i))
		return (1);
	while (*(str + i) >= '0' && *(str + i) <= '9')
	{
		result = result * 10 + *(str + i++) - '0';
		if (result > INT_MAX && (result * sign != INT_MIN))
			return (1);
	}
	if (*(str + i) && !(*(str + i) >= '0' && *(str + i) <= '9'))
		return (2);
	*n = (int)result * sign;
	return (0);
}

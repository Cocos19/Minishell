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

long long int	safe_atoi(const char *str)
{
	long long int	result;
	int				sign;
	int				i;

	sign = 1;
	i = 0;
	result = 0;
	while (*(str + i) == ' ' || (*(str + i) >= 9 && *(str + i) <= 13))
		i++;
	if (*(str + i) == '-' || *(str + i) == '+')
		if (*(str + i++) == '-')
			sign = -1;
	if (!*(str + i))
		return (++result + INT_MAX);
	while (ft_isdigit(*(str + i)))
	{
		result = result * 10 + *(str + i++) - '0';
		if (result > INT_MAX && (result * sign != INT_MIN))
			return (result);
	}
	if (*(str + i) && !ft_isdigit(*(str + i)))
		return (++result + INT_MAX);
	return (result * sign);
}

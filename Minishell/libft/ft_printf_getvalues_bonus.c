/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:07:27 by mprofett          #+#    #+#             */
/*   Updated: 2022/11/24 10:07:29 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	get_pointer_len(unsigned long long nbr, t_var_specs *var)
{
	var->len = 3;
	while ((nbr / 16) != 0)
	{
		nbr = nbr / 16;
		++var->len;
	}
}

void	get_nbr_len(long long int nbr, t_var_specs *var)
{
	int	div;

	div = 16;
	if (var->type == 'i' || var->type == 'd' || var->type == 'u')
		div = 10;
	var->len = 1;
	if (nbr < 0)
		nbr *= -1;
	while (nbr / div != 0)
	{
		nbr = nbr / div;
		++var->len;
	}
	if ((var->precision > var->len) && var->precision != 2147483641)
	{
		var->precision -= var->len;
		var->len += var->precision;
	}
	else if (var->precision != 0)
		var->precision = 2147483641;
}

void	get_nbr_specs(t_var_specs *var, long long int nbr)
{
	if (var->precision != 2147483641)
		var->width_type = ' ';
	get_nbr_len(nbr, var);
	get_sign_len(var, nbr);
	if (nbr == 0 && var->precision == 0)
	{
		var->len = 0;
		if (var->sign != 0
			&& ((nbr != 0) || (var->type != 'x' && var->type != 'X')))
			++var->len;
		if (var->width != 0)
			var->width = var->width - var->len;
	}
	else if (var->width > var->len)
		var->width = var->width - var->len;
	else
		var->width = 0;
	var->len += var->width;
}

void	get_sign_len(t_var_specs *var, long long int nbr)
{
	if (nbr < 0 && (var->type == 'd' || var->type == 'i'))
		++var->len;
	else if ((var->type == 'd' || var->type == 'i') && var->sign != 0)
		++var->len;
	else if (var->sign == '#'
		&& (var->type == 'x' || var->type == 'X') && nbr != 0)
		var->len += 2;
}

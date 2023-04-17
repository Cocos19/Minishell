/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putvalues_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:24:22 by mprofett          #+#    #+#             */
/*   Updated: 2022/12/02 16:24:24 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	put_nbr(t_var_specs *var, long long int nbr, int var_len)
{
	if (nbr < 0)
		nbr *= -1;
	if (var->precision != 2147483641 && var->precision != 0)
		while (var->precision-- > 0)
			ft_putchar_fd('0', 1);
	if ((var->type == 'i' || var->type == 'd' || var->type == 'u')
		&& (nbr != 0 || var->precision != 0))
	{
		if (nbr / 10 != 0)
			put_nbr(var, nbr / 10, var_len);
		ft_putchar_fd(((nbr % 10) + 48), 1);
	}
	else if ((var->type == 'x' || var->type == 'X')
		&& (nbr != 0 || var->precision != 0))
	{
		if ((nbr / 16) != 0 && var_len-- > 0)
			put_nbr(var, nbr / 16, var_len);
		if (var->type == 'X')
			ft_put_hexa_char_fd(nbr % 16, 0, 1);
		else
			ft_put_hexa_char_fd(nbr % 16, 1, 1);
	}
}

void	put_pointer(unsigned long long nbr)
{
	if ((nbr / 16) != 0)
		put_pointer(nbr / 16);
	ft_put_hexa_char_fd(nbr % 16, 1, 1);
}

void	put_sign(t_var_specs *var, long long int nbr)
{
	if (nbr < 0 && (var->type == 'd' || var->type == 'i'))
		ft_putchar_fd('-', 1);
	else if ((var->type == 'd' || var->type == 'i') && var->sign != 0)
		ft_putchar_fd(var->sign, 1);
	else if (var->sign == '#'
		&& (var->type == 'x' || var->type == 'X') && nbr != 0)
	{
		if (var->type == 'X')
			write (1, "0X", 2);
		else
			write (1, "0x", 2);
	}
}

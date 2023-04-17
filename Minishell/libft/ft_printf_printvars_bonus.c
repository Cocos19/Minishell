/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_printvars_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:19:18 by mprofett          #+#    #+#             */
/*   Updated: 2022/12/02 16:19:24 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	print_str_with_spec(va_list *ap, t_var_specs *var)
{
	char	*s;
	int		i;

	s = va_arg(*ap, char *);
	i = -1;
	if (!s)
		s = "(null)";
	var->len = ft_strlen(s);
	if (var->precision < var->len)
		var->len = var->precision;
	if (var->width > var->len)
		var->width = var->width - var->len;
	else
		var->width = 0;
	if (var->left_justified == 1)
		write(1, s, var->len);
	if (var->width > 0)
		while (var->width-- > 0)
			ft_putchar_fd(var->width_type, 1);
	if (var->left_justified == 0)
		write(1, s, var->len);
	var->len += var->width;
}

void	print_numeric_with_spec(va_list *ap, t_var_specs *var)
{
	long long int	nbr;

	if (var->type == 'u' || var->type == 'x' || var->type == 'X')
		nbr = va_arg(*ap, unsigned int);
	else if (var->type == 'i' || var->type == 'd')
		nbr = va_arg(*ap, int);
	else
		nbr = va_arg(*ap, unsigned long long);
	get_nbr_specs(var, nbr);
	if (var->left_justified == 0 && var->width_type == '0' )
		put_sign(var, nbr);
	if (var->left_justified == 1)
	{
		put_sign(var, nbr);
		put_nbr(var, nbr, var->len);
	}
	while (var->width-- > 0)
		ft_putchar_fd(var->width_type, 1);
	if (var->left_justified == 0)
	{
		if (var->width_type != '0')
			put_sign(var, nbr);
		put_nbr(var, nbr, var->len);
	}
}

void	print_pointer_with_spec(va_list *ap, t_var_specs *var)
{
	unsigned long long	nbr;

	nbr = va_arg(*ap, unsigned long long);
	get_pointer_len(nbr, var);
	if (var->width > var->len)
		var->width = var->width - var->len;
	else
		var->width = 0;
	var->len += var->width;
	if (var->left_justified == 1)
	{
		write(1, "0x", 2);
		put_pointer(nbr);
	}
	while (var->width-- > 0)
		ft_putchar_fd(var->width_type, 1);
	if (var->left_justified == 0)
	{
		write(1, "0x", 2);
		put_pointer(nbr);
	}
}

void	print_char_with_spec(va_list *ap, t_var_specs *var)
{
	char	c;
	int		i;

	i = -1;
	if (var->type == '%')
		c = '%';
	else
		c = va_arg(*ap, int);
	if (var->width > var->len)
		var->width = var->width - var->len;
	else
		var->width = 0;
	var->len += var->width;
	if (var->left_justified == 1)
		ft_putchar_fd(c, 1);
	if (var->width > 0)
		while (var->width-- > 0)
			ft_putchar_fd(var->width_type, 1);
	if (var->left_justified == 0)
		ft_putchar_fd(c, 1);
}

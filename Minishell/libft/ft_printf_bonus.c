/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:07:16 by mprofett          #+#    #+#             */
/*   Updated: 2022/11/24 10:07:18 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	get_numeric_flag_value(t_var_specs *var, const char *s)
{
	unsigned long long int	result;
	int						width;

	result = 0;
	width = 0;
	if (s[var->i] == '.')
		++var->i;
	else
		width = 1;
	while (ft_isdigit(s[var->i]))
	{
		result = result * 10 + s[var->i++] - '0';
		if (result >= 2147483641)
		{
			result = 2147483641;
			while (ft_isdigit(s[++var->i]))
				;
		}
	}
	if (width == 1)
		var->width = result;
	else
		var->precision = result;
}

void	get_first_flags(t_var_specs *var, const char *s)
{
	while (s[var->i] == ' ' || s[var->i] == '+' || s[var->i] == '#'
		|| s[var->i] == '0' || s[var->i] == '-')
	{
		if (s[var->i] == ' ' && var->sign != '+')
			var->sign = ' ';
		else if (s[var->i] == '+' && var->sign != '+')
			var->sign = '+';
		else if (s[var->i] == '#' && var->sign != '#')
			var->sign = '#';
		else if (s[var->i] == '-' && var->left_justified == 0)
		{
			var->left_justified = 1;
			var->width_type = ' ';
		}
		else if (s[var->i] == '0' && var->left_justified == 0)
			var->width_type = '0';
		++var->i;
	}
}

void	get_var_specs(t_var_specs *var, const char *s)
{
	++var->i;
	var->type = 0;
	var->sign = 0;
	var->len = -1;
	var->precision = 2147483641;
	var->width = 0;
	var->width_type = ' ';
	var->left_justified = 0;
	get_first_flags(var, s);
	if (ft_isdigit(s[var->i]))
		get_numeric_flag_value(var, s);
	if (s[var->i] == '.')
		get_numeric_flag_value(var, s);
	var->type = s[var->i];
	if (var->type == '%' || var->type == 'c')
		var->len = 1;
}

void	print_variable(va_list *ap, t_var_specs *var, const char *s)
{
	get_var_specs(var, s);
	if (var->type == 'c' || var->type == '%')
		return (print_char_with_spec(ap, var));
	else if (var->type == 's')
		return (print_str_with_spec(ap, var));
	else if (var->type == 'p')
		return (print_pointer_with_spec(ap, var));
	else if (var->type == 'd' || var->type == 'i' || var->type == 'u'
		|| var->type == 'x' || var->type == 'X')
		return (print_numeric_with_spec(ap, var));
}

int	ft_printf(const char *s, ...)
{
	va_list		ap;
	t_var_specs	var;
	int			count;

	var.i = -1;
	count = 0;
	va_start(ap, s);
	while (s[++var.i])
	{
		if (s[var.i] == '%')
		{
			print_variable(&ap, &var, s);
			if (var.len == -1)
				return (-1);
			count += var.len - 1;
		}
		else
			write(1, s + var.i, 1);
		++count;
	}
	va_end(ap);
	return (count);
}

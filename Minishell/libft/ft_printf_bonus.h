/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:29:54 by mprofett          #+#    #+#             */
/*   Updated: 2022/11/24 10:29:55 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include "libft.h"

typedef struct s_variable_specifications
{
	int		i;
	int		len;
	int		precision;
	int		width;
	int		left_justified;
	char	type;
	char	sign;
	char	width_type;
}	t_var_specs;

int		ft_printf(const char *s, ...);
void	put_nbr(t_var_specs *var, long long int nbr, int var_len);
void	put_pointer(unsigned long long nbr);
void	put_sign(t_var_specs *var, long long int nbr);
void	get_nbr_specs(t_var_specs *var, long long int nbr);
void	get_sign_len(t_var_specs *var, long long int nbr);
void	get_nbr_len(long long int nbr, t_var_specs *var);
void	get_pointer_len(unsigned long long nbr, t_var_specs *var);
void	print_char_with_spec(va_list *ap, t_var_specs *var);
void	print_str_with_spec(va_list *ap, t_var_specs *var);
void	print_numeric_with_spec(va_list *ap, t_var_specs *var);
void	print_pointer_with_spec(va_list *ap, t_var_specs *var);

#endif

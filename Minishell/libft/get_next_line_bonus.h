/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:37:13 by mprofett          #+#    #+#             */
/*   Updated: 2023/07/05 10:50:45 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "libft.h"

char	*get_next_line(int fd, int buffer_size);
char	*read_until_next_line(char *buffer, const int fd, int buffer_size);
char	*get_current_line(char *buffer, int end_of_line);
char	*save_end_of_buffer(char *buffer, int end_of_line);
char	*add_to_buffer(char *buffer, char *new_read);
char	*reset_str(char *buffer);
int		strchr_eol(const char *buffer, int c);

#endif

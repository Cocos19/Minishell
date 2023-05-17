/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:55:28 by mprofett          #+#    #+#             */
/*   Updated: 2023/05/05 14:41:24 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int				ft_isalpha(unsigned char c);
int				ft_isdigit(unsigned char c);
int				ft_isalnum(unsigned char c);
int				ft_isascii(unsigned char c);
int				ft_isprint(unsigned char c);
size_t			ft_strlen(const char *s);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, char *src, size_t dstsize);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strnstr(const char *haystack,
					const char *needle, size_t len);
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s1);
char			**ft_strdup_tab(const char **tab);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_put_hexa_char_fd(char c, int lowercase, int fd);

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

void			ft_put_hexa_char_fd(char c, int lowercase, int fd);
long long int	safe_atoi(const char *str);
char			*get_next_line(int fd, int buffer_size);
int				ft_printf(const char *s, ...);
int				*ft_split_integers(const char *s);
char			**ft_free_str_array(char **str_array);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_expand(char *str, char *start, char *cut, char *paste);
char			*ft_strjoin_and_free_srcs(char *s1, char *s2);
char			*ft_substr_delimited(char *start, const char *end);
int				ft_is_empty_or_with_only_spaces(const char *str);
int				ft_strarraylen(char **strarray);
char			**ft_strarrayjoin_and_free_srcs(char **sarr1, char **sarr2);
char			*ft_skip_character(char *str, char c);
char			**ft_add_to_str_array(char **src, char *str_to_add);
char			**ft_strdup_array(char **str_array);
void			ft_print_str_array(char **str_array);
char			*ft_strndup(const char *s1, int end_index);
char			*ft_skip_all_but_character(char	*str, char c);
void			ft_sort_str_array(char **array);
void			ft_print_str_array_fd(char **str_array, int fd);
char			**ft_retrieve_from_str_array(char **src, int index_to_remove);

#endif

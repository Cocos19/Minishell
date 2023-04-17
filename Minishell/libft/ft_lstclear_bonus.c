/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:39:33 by mprofett          #+#    #+#             */
/*   Updated: 2022/10/05 15:39:35 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*list;
	t_list	*buff;

	if (lst && *lst && del)
	{
		list = *lst;
		while (list->next)
		{
			buff = list->next;
			ft_lstdelone(list, del);
			list = buff;
		}
		ft_lstdelone(list, del);
		*lst = NULL;
	}
}

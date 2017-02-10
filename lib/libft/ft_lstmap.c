/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 09:32:42 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/19 01:11:06 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

t_dlist		*ft_lstmap(t_list *lst, t_list *(f)(t_list *elem))
{
	t_dlist	*new;

	new = NULL;
	while (lst)
	{
		ft_lstadd_end(&new, f(lst));
		lst = lst->next;
	}
	return (new);
}

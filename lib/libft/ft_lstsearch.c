/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsearch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 10:25:41 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/19 01:25:05 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstsearch(t_list *lst, int (*f)(t_list *, void *), void *data)
{
	while (lst && f)
	{
		if (f(lst, data))
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

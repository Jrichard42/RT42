/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 13:06:19 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/17 17:41:40 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static void	special(t_dlist **alst, t_list *current)
{
	if ((*alst)->head == current)
	{
		(*alst)->head = current->next;
		if (current->next)
			current->next->prev = NULL;
	}
	else
		current->prev->next = current->next;
	if ((*alst)->tail == current)
	{
		(*alst)->tail = current->prev;
		if (current->prev)
			current->prev->next = NULL;
	}
	else
		current->next->prev = current->prev;
}

void		ft_lstdelone(t_dlist **alst, t_list *current,
							void (*del)(void*, size_t))
{
	if (alst && current)
	{
		if (*alst)
		{
			del(current->content, current->content_size);
			special(alst, current);
			free(current);
			if (!((*alst)->head) && !((*alst)->tail))
			{
				free(*alst);
				*alst = NULL;
			}
		}
	}
}

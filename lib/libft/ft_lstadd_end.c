/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 19:09:47 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/17 02:15:14 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int			ft_lstadd_end(t_dlist **alst, t_list *new)
{
	if (new && alst)
	{
		if (!*alst)
		{
			new->next = NULL;
			new->prev = NULL;
			if (!(*alst = malloc(sizeof(**alst))))
				return (0);
			(*alst)->head = new;
			(*alst)->tail = new;
		}
		else
		{
			new->prev = (*alst)->tail;
			(*alst)->tail->next = new;
			(*alst)->tail = new;
		}
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 09:31:52 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/17 02:14:55 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int		ft_lstadd(t_dlist **alst, t_list *new)
{
	if (new && alst)
	{
		if (!(*alst))
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
			new->next = (*alst)->head;
			(*alst)->head->prev = new;
			(*alst)->head = new;
		}
		return (1);
	}
	return (0);
}

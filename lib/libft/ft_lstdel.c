/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 13:15:27 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/17 02:17:13 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

void		ft_lstdel(t_dlist **alst, void (*del)(void *, size_t))
{
	if (alst)
	{
		while ((*alst))
			ft_lstdelone(alst, ((*alst)->head), del);
	}
}

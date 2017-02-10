/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 18:51:46 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/17 01:23:13 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

void		*ft_memalloc(size_t size)
{
	void	*tab;

	if (!(tab = malloc(size)))
		return (NULL);
	ft_memset(tab, 0, size);
	return (tab);
}

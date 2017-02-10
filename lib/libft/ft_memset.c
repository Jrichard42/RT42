/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 09:43:27 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/17 01:25:59 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void		*ft_memset(void *b, int c, size_t len)
{
	void	*save;

	save = b;
	while ((int)len)
	{
		*((char*)b) = (unsigned char)c;
		++b;
		--len;
	}
	return (save);
}

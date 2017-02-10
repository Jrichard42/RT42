/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 11:00:10 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/17 01:25:05 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	int		diff;

	diff = *((int*)dst) - *((int*)src);
	if (ABS(diff) >= (int)len)
		ft_memcpy(dst, src, len);
	else
	{
		if (diff > 0)
		{
			dst += (int)len - 1;
			src += (int)len - 1;
			while ((int)len)
			{
				*((char *)dst) = *((char *)src);
				--dst;
				--src;
				--len;
			}
			++dst;
		}
		else
			ft_memcpy(dst, src, len);
	}
	return (dst);
}

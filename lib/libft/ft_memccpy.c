/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 10:29:23 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/17 01:23:27 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memccpy(void *restrict dst, const void *restrict src,
					int c, size_t n)
{
	while ((int)n && ((unsigned char)*((char *)src) != (unsigned char)c))
	{
		*((char *)dst) = *((char *)src);
		++dst;
		++src;
		--n;
	}
	if ((int)n && ((unsigned char)*((char *)src) == (unsigned char)c))
	{
		*((char *)dst) = (unsigned char)c;
		++dst;
		return (dst);
	}
	else
		return (NULL);
}

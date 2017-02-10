/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 10:20:48 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/17 02:03:02 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void		*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	void	*save;

	save = dst;
	while ((int)n)
	{
		*((char *)dst) = *((char *)src);
		++dst;
		++src;
		--n;
	}
	return (save);
}

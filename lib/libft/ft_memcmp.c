/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:29:35 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/17 01:23:43 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int			ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (!(int)n)
		return (0);
	while ((int)n > 1 && *((char *)s1) == *((char *)s2))
	{
		++s1;
		++s2;
		--n;
	}
	return ((unsigned char)(*((char *)s1)) - (unsigned char)(*((char *)s2)));
}

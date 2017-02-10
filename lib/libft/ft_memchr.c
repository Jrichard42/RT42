/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 15:48:32 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/17 01:23:35 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void		*ft_memchr(const void *s, int c, size_t n)
{
	char	*tmp;

	tmp = (char *)s;
	if ((int)n == 0)
		return (NULL);
	while ((int)n > 1 && (unsigned char)(*tmp) != (unsigned char)c)
	{
		++tmp;
		--n;
	}
	if ((unsigned char)(*tmp) != (unsigned char)c)
		return (NULL);
	return ((void *)tmp);
}

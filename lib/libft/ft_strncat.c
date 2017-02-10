/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 15:32:10 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/17 01:40:25 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char		*ft_strncat(char *restrict s1, const char *restrict s2, size_t n)
{
	char	*save;

	save = s1;
	while (*s1)
		++s1;
	while (*s2 && n > 0)
	{
		*s1++ = *s2++;
		--n;
	}
	*s1 = '\0';
	return (save);
}

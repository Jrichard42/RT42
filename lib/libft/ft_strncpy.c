/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:35:45 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/17 01:40:40 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char		*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*save;

	save = dst;
	while (len)
	{
		if (*src)
			*dst = *src++;
		else
			*dst = '\0';
		--len;
		++dst;
	}
	return (save);
}

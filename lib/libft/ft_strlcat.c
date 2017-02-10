/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:34:05 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/17 01:38:25 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t		ft_strlcat(char *restrict dst, const char *restrict src,
						size_t size)
{
	size_t	save;
	size_t	save_dst_l;
	size_t	save_src_l;

	save = size;
	save_src_l = ft_strlen(src);
	save_dst_l = ft_strlen(dst);
	while (*dst)
	{
		if (size > 0)
			--size;
		++dst;
	}
	while (size-- > 1 && *src)
		*dst++ = *src++;
	*dst = '\0';
	if (save < save_dst_l)
		return (save + save_src_l);
	return (save_dst_l + save_src_l);
}

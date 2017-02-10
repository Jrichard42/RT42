/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 12:39:51 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/17 01:41:35 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include "libft.h"

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		i;
	char	*tmp;
	int		add;

	i = 0;
	add = 0;
	if (!little[0])
		return ((char *)big);
	while ((tmp = ft_strchr(big + add, little[0])) &&
			((tmp - big) + (int)ft_strlen(little)) <= (int)len)
	{
		while (tmp[i] && little[i] && tmp[i] == little[i])
			++i;
		if (!little[i])
			return ((char *)tmp);
		else
			i = 0;
		++add;
	}
	return (NULL);
}

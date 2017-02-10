/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 11:31:15 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/17 01:42:12 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "libft.h"

char		*ft_strstr(const char *big, const char *little)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!little[0])
		return ((char *)big);
	while (*big && (tmp = ft_strchr(big, little[0])))
	{
		while (tmp[i] && little[i] && tmp[i] == little[i])
			++i;
		if (!little[i])
			return ((char *)tmp);
		else
		{
			big = tmp + 1;
			i = 0;
		}
	}
	return (NULL);
}

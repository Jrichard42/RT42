/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 13:05:51 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/18 23:45:06 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*tmp;

	if (s)
	{
		tmp = ft_strnew(len);
		if (tmp)
			return (ft_strncpy(tmp, s + start, len));
	}
	return (NULL);
}

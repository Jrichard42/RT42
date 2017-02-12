/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 11:01:00 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/17 01:23:02 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static int	get_length(int nbr)
{
	int ret;

	ret = 0;
	while (nbr / 10)
	{
		nbr = nbr / 10;
		++ret;
	}
	if (nbr < 0)
		return (ret + 2);
	else
		return (ret + 1);
}

char		*ft_itoa(int nbr)
{
	char	*str;
	int		i;

	i = get_length(nbr);
	if ((str = (char *)malloc((i + 1) * sizeof(*str))))
	{
		str[i--] = '\0';
		while (nbr / 10)
		{
			if (nbr < 0)
				str[i] = -(nbr % 10) + 48;
			else
				str[i] = (nbr % 10) + 48;
			nbr = nbr / 10;
			--i;
		}
		if (nbr < 0)
		{
			nbr = -nbr;
			str[0] = '-';
		}
		str[i] = nbr % 10 + 48;
		return (str);
	}
	return (NULL);
}

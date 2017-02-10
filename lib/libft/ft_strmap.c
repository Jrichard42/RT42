/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 10:12:16 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/17 01:40:08 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*tab;
	int		i;
	int		i2;

	if (s)
	{
		i = 0;
		i2 = 0;
		if (!(tab = (char *)malloc((ft_strlen(s) + 1) * sizeof(*tab))))
			return (NULL);
		while (s[i])
		{
			tab[i2] = f(s[i]);
			++i;
			++i2;
		}
		tab[i2] = '\0';
		return (tab);
	}
	return (NULL);
}

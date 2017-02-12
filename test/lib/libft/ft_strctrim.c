/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strctrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 11:39:07 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/17 01:49:05 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char				*ft_strctrim(char const *s, char c)
{
	unsigned int	start;
	size_t			end;

	if (!s)
		return (NULL);
	start = 0;
	end = ft_strlen(s) - 1;
	while (s[start] && (s[start] == c))
		++start;
	if (!s[start])
		return (ft_strsub(s, start, 1));
	while (end && (s[end] == c))
		--end;
	return (ft_strsub(s, start, end - start + 1));
}

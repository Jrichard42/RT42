/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 13:35:06 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/17 01:42:38 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char				*ft_strtrim(char const *s)
{
	unsigned int	start;
	size_t			end;

	if (!s)
		return (NULL);
	start = 0;
	end = ft_strlen(s) - 1;
	while (s[start] && (s[start] == ' ' ||
			s[start] == '\n' || s[start] == '\t'))
		++start;
	if (!s[start])
		return (ft_strsub(s, start, 1));
	while (end && (s[end] == ' ' || s[end] == '\n' || s[end] == '\t'))
		--end;
	return (ft_strsub(s, start, end - start + 1));
}

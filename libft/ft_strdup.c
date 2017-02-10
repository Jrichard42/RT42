/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 17:07:36 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/18 08:03:20 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

char		*ft_strdup(const char *s1)
{
	char	*ret;

	if ((ret = (char *)malloc((ft_strlen(s1) + 1) * sizeof(*ret))))
		return (ft_strcpy(ret, s1));
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 11:26:53 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/17 01:30:54 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

void		*ft_realloc(void *ptr, size_t size)
{
	void	*new;

	if (!(new = malloc(size * sizeof(*new))))
		return (NULL);
	if (ptr)
	{
		ft_strcpy((char *)new, (char *)ptr);
		ft_memdel(&ptr);
	}
	return (new);
}

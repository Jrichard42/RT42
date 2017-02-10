/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 10:20:17 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/18 21:31:33 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char		*ft_strnew(size_t size)
{
	char	*tab;

	tab = (char *)ft_memalloc((size + 1) * sizeof(*tab));
	return (tab);
}

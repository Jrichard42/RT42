/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 09:05:57 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/17 01:21:45 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	return (((unsigned char)c == ' ' ||
		(unsigned char)c == '\f' ||
		(unsigned char)c == '\n' ||
		(unsigned char)c == '\r' ||
		(unsigned char)c == '\t' ||
		(unsigned char)c == '\v') ? 1 : 0);
}

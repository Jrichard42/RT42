/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 16:35:37 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/18 22:34:01 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	delgnl(void *content, size_t content_size)
{
	ft_bzero(content, content_size);
	ft_strdel((&(((t_gnldata*)content)->buff)));
	ft_memdel(&content);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 16:39:20 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/08 16:45:31 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

#define NODE ((t_gnldata *)node->content)

void	delgnl(void *content, size_t content_size)
{
	ft_strdel((&(((t_gnldata*)content)->buff)));
	ft_bzero(content, content_size);
	ft_memdel(&content);
}

int		fd_cmp(t_list *node, void *data)
{
	if (node && data)
		if (NODE->fd == *(int *)data)
			return (1);
	return (0);
}

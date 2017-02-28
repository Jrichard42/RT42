/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kvlexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <jrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 18:12:12 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/25 15:03:37 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_kvlexer.h"

void			free_node(void *data, size_t size)
{
	t_kvlexer	*tmp;

	(void)size;
	if (data)
	{
		tmp = (t_kvlexer*)data;
		ft_strdel(&(tmp->key));
		ft_strdel(&(tmp->value));
		tmp->father = NULL;
		ft_lstdel(&(tmp->children), &free_node);
		free(data);
	}
}

void			free_kvlexer(t_kvlexer *kvlexer)
{
	if (kvlexer)
		free_node(kvlexer, sizeof(t_kvlexer));
}

void			*fail_kvlexer(t_kvlexer *kvlexer, int fd)
{
	close(fd);
	free_kvlexer(kvlexer);
	return (NULL);
}

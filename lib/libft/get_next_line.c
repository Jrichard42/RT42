/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 13:59:03 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/08 16:49:55 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

#define NODE ((t_gnldata *)node->content)
#define PNODE ((t_gnldata *)(*node)->content)

static int			create_data(t_dlist **list, int fd, t_list **node)
{
	t_gnldata		data;

	data.buff = NULL;
	data.index = 0;
	data.fd = fd;
	ft_lstadd(list, ft_lstnew(&data, sizeof(data)));
	*node = (*list)->head;
	if (!(PNODE->buff = ft_strnew(BUFF_SIZE)))
		return (-1);
	return (0);
}

static int			check_endline(t_list **node, int save, char **line)
{
	int				ret;
	char			*tmp;
	char			*tmp_join;

	if (!(tmp = ft_strnew(BUFF_SIZE)) ||
			(ret = read(PNODE->fd, tmp, BUFF_SIZE)) == -1)
		return (-1);
	if (!ret)
	{
		ft_strdel(&tmp);
		if (!(*line = ft_strsub(PNODE->buff, save, PNODE->index - save)))
			return (-1);
		return (1);
	}
	else
	{
		if (!(tmp_join = ft_strjoin(PNODE->buff + save, tmp)))
			return (-1);
		ft_strdel(&PNODE->buff);
		ft_strdel(&tmp);
		PNODE->buff = tmp_join;
		PNODE->index = 0;
		return (2);
	}
}

static int			read_more(t_list **node, char **line)
{
	int				save;

	save = PNODE->index;
	while (PNODE->buff[PNODE->index] && PNODE->buff[PNODE->index] != '\n')
		++PNODE->index;
	if (!PNODE->buff[PNODE->index])
		return (check_endline(node, save, line));
	else
	{
		if (!(*line = ft_strsub(PNODE->buff, save, PNODE->index - save)))
			return (-1);
		++PNODE->index;
		if (!PNODE->buff[PNODE->index])
		{
			ft_strdel(&PNODE->buff);
			if (!(PNODE->buff = ft_strnew(BUFF_SIZE)))
				return (-1);
			if (read(PNODE->fd, PNODE->buff, BUFF_SIZE) == -1)
				return (-1);
			PNODE->index = 0;
		}
		return (1);
	}
}

int					get_next_line(const int fd, char **line)
{
	static t_dlist	*list;
	t_list			*node;
	int				ret;

	if (!line)
		return (-1);
	if (!list || !(node = ft_lstsearch(list->head, &fd_cmp, (void *)&fd)))
		if (create_data(&list, fd, &node) == -1)
			return (-1);
	if (!NODE->buff[0] && read(fd, NODE->buff, BUFF_SIZE) == -1)
		return (-1);
	if (!NODE->buff[0] || !NODE->buff[NODE->index])
	{
		ft_lstdelone(&list, node, &delgnl);
		return (0);
	}
	while ((ret = read_more(&node, line)) == 2)
		;
	return (ret);
}

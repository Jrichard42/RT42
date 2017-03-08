/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <jrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 21:47:12 by jrichard          #+#    #+#             */
/*   Updated: 2017/01/19 00:21:06 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

#define NODE ((t_gnldata *)node->content)
#define PNODE ((t_gnldata *)(*node)->content)

static int			fd_cmp(t_list *node, void *data)
{
	if (node && data)
		if (NODE->fd == *(int *)data)
			return (1);
	return (0);
}

static int			create_data(t_dlist **list, int fd, t_list **node)
{
	t_gnldata			data;

	data.buff = NULL;
	data.index = 0;
	data.fd = fd;
	ft_lstadd(list, ft_lstnew(&data, sizeof(data)));
	*node = (*list)->head;
	if (!(PNODE->buff = ft_strnew(BUFF_SIZE)))
		return (-1);
	return (0);
}

/*static int			new_line(t_dlist **list, t_list **node, int i, char **line)
{
	int				check_abs;

	ft_strdel(line);
	if (!(*line = (char *)malloc((i + 1) * sizeof(**line))))
		return (-1);
	(*line)[i] = '\0';
	ft_strncpy(*line, PNODE->buff, i);
	check_abs = ABS(PNODE->ret);
	if (!(PNODE->buff[0]) && check_abs < BUFF_SIZE)
	{
		ft_lstdelone(list, *node, &delgnl);
		if ((*list) && (*list)->head == NULL)
			free(*list);
		*list = NULL;
		return (0);
	}
	if (!(PNODE->buff[i]))
	{
		ft_strclr(PNODE->buff);
		PNODE->ret = BUFF_SIZE;
	}
	else
		ft_strcpy(PNODE->buff, PNODE->buff + i + 1);
	return (1);
}

static int			read_more(t_dlist **list, t_list **node, char **line)
{
	char			*tmp_join;
	int				i;
	int				check_abs;

	i = 0;
	tmp_join = ft_strjoin(PNODE->buff, PNODE->tmp);
	ft_strdel(&PNODE->buff);
	PNODE->buff = tmp_join;
	ft_strclr(PNODE->tmp);
	if (PNODE->ret > 0)
		PNODE->ret = -PNODE->ret;
	while (PNODE->buff[i] && PNODE->buff[i] != '\n')
		++i;
	check_abs = ABS(PNODE->ret);
	if (!PNODE->buff[i] && (check_abs == BUFF_SIZE))
	{
		PNODE->ret = BUFF_SIZE;
		return (2);
	}
	return (new_line(list, node, i, line));
}*/

static int			read_mode(t_list **node, char **line)
{
	char			*tmp;
	int				save;
	char			*tmp_join;
	
	save = PNODE->index;
	while (PNODE->buff[PNODE->index] && PNODE->buff[PNODE->index] != '\n')
		++PNODE->index;
	if (!PNODE->buff[PNODE->index])
	{
		if (!(tmp = ft_strnew(BUFF_SIZE)))
			return (-1);
		if (read(PNODE->fd, tmp, BUFF_SIZE) == -1)
			return (-1);
		if (!(tmp_join = ft_strnew(ft_strlen(PNODE->buff) - save + BUFF_SIZE)))
			return (-1);

		ft_strcpy(tmp_join, PNODE->buff + PNODE->index);
		ft_strcat(tmp_join, tmp);
		ft_strdel(&PNODE->buff);
		ft_strdel(&tmp);
		PNODE->buff = tmp_join;
		PNODE->index = 0;
		if (!PNODE->buff[0])
			return (0);
		return (2);
	}
	else
	{
		if (!(*line = ft_strsub(PNODE->buff, save, PNODE->index - save)))
			return (-1);
		++PNODE->index;
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
	//ft_strdel(line);
	if (!list || !(node = ft_lstsearch(list->head, &fd_cmp, (void *)&fd)))
		if (create_data(&list, fd, &node) == -1)
			return (-1);
	if (!NODE->buff[0] && read(fd, NODE->buff, BUFF_SIZE) == -1)
		return (-1);
	if (!NODE->buff[0])
	{
		ft_lstdelone(&list, node, &delgnl);
		return (0);
	}
	while ((ret = read_mode(&node, line)) == 2)
		;
	return (ret);
}

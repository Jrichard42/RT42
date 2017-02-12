/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kvlexer2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 19:34:01 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/10 19:43:14 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"
#include "ft_kvlexer.h"

static int		check_indent(char *line, int current_nb)
{
	int			i;
	int			ret;

	i = 0;
	ret = 0;
	while (line[i] == '\t')
	{
		++ret;
		++i;
	}
	if (ret == 0 && current_nb != -1)
	{
		ft_putendl("Only one root allowed");
		return (-1);
	}
	if (ret > current_nb + 1)
	{
		ft_putendl("Wrong indentation");
		return (-1);
	}
	if (ft_isprint(line[i]) && !ft_isspace(line[i]))
		return (ret);
	ft_putendl("Invalid characters");
	return (-1);
}

static int		fill_node(char *line, int nb, t_kvlexer *node,
		t_kvlexer *father)
{
	char		*trimmed;
	char		*value;
	int			size;

	if (!(trimmed = ft_strtrim(line)))
		return (-1);
	value = NULL;
	size = ft_strlen(trimmed);
	ft_strdel(&line);
	node->nb = nb;
	node->key = NULL;
	node->value = NULL;
	value = ft_strchr(trimmed, '=');
	if (value)
	{
		node->value = ft_strdup(value + 1);
		size = ft_strlen(trimmed) - ft_strlen(value);
	}
	node->key = ft_strnew(size);
	ft_strncpy(node->key, trimmed, size);
	node->father = father;
	node->children = NULL;
	ft_strdel(&trimmed);
	return (1);
}

static int		create_node(char *line, t_kvlexer **current, t_kvlexer *node)
{
	int			i;
	int			nb;

	i = 0;
	if ((nb = check_indent(line, (*current)->nb)) == -1)
		return (-1);
	if (nb <= (*current)->nb)
	{
		i = (*current)->nb - nb + 1;
		while (i--)
			*current = (*current)->father;
	}
	if (!(fill_node(line, nb, node, *current)))
		return (-1);
	return (1);
}

static int		create_root(t_kvlexer **root, char *line, t_kvlexer **current)
{
	if (!(*root = ft_memalloc(sizeof(**root))))
		return (-1);
	if (check_indent(line, -1) == -1)
		return (-1);
	if (fill_node(line, 0, *root, NULL) == -1)
		return (-1);
	*current = *root;
	return (0);
}

t_kvlexer		*ft_kvlexer(char *name)
{
	int			fd;
	char		*line;
	t_kvlexer	node;
	t_kvlexer	*current;
	t_kvlexer	*root;

	if ((fd = open(name, O_RDONLY)) == -1)
		return (ft_error("Unable to open the file"));
	root = NULL;
	while (get_next_line(fd, &line) == 1)
	{
		if (root)
		{
			if (create_node(line, &current, &node) == -1)
				return (fail_kvlexer(root, fd));
			if (!(ft_lstadd_end(&(current->children),
							ft_lstnew(&node, sizeof(t_kvlexer)))))
				return (fail_kvlexer(root, fd));
			current = (t_kvlexer *)current->children->tail->content;
		}
		else if (create_root(&root, line, &current) == -1)
			return (fail_kvlexer(root, fd));
	}
	close(fd);
	return (root);
}

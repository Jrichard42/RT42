/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kvlexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <jrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 18:12:12 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/10 14:22:19 by hpachy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"
#include "ft_kvlexer.h"

static void		*error(char *to_print)
{
	ft_putendl(to_print);
	return (0);
}

void		free_node(void *data, size_t size)
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

void		*free_kvlexer(t_kvlexer *kvlexer)
{
	if (kvlexer)
		free_node(kvlexer, sizeof(t_kvlexer));
	return (NULL);
}

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

static int		fill_node(char *line, int nb, t_kvlexer *node, t_kvlexer *father)
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

static int	create_root(t_kvlexer **root, char *line, t_kvlexer **current)
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
	int		fd;
	char	*line;
	t_kvlexer	node;
	t_kvlexer	*current;
	t_kvlexer	*root;

	if ((fd = open(name, O_RDONLY)) == -1)
		return (error("Unable to open the file"));
	root = NULL;
	while (get_next_line(fd, &line) == 1)
	{
		if (!root)
		{
			if (create_root(&root, line, &current) == -1)
				return (free_kvlexer(root)); //close fd
		}
		else
		{
			if (create_node(line, &current, &node) == -1)
				return (free_kvlexer(root));
			if (!(ft_lstadd_end(&(current->children), ft_lstnew(&node, sizeof(t_kvlexer)))))
				return (free_kvlexer(root));
			current = (t_kvlexer *)current->children->tail->content;
		}
	}
	close(fd);
	return (root);
}

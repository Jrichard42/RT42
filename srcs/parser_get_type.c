/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 16:07:58 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/24 15:06:12 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int				search_key(t_list *node, void *data)
{
	if (!ft_strcmp(((t_kvlexer *)node->content)->key, (char *)data))
		return (1);
	return (0);
}

int				get_as_vector3f(t_kvlexer *token, char *str, t_vector3f *vec)
{
	t_list		*node;
	t_kvlexer	*field;
	char		*tmp;

	if (token->children && (node = ft_lstsearch(token->children->head, &search_key, str)))
	{
		field = (t_kvlexer *)node->content;
		if (field && field->value && *field->value)
		{
			vec->x = ft_atof(field->value);
			tmp = ft_strchr(field->value, ',');
			if (tmp && *(++tmp))
				vec->y = ft_atof(tmp);
			else
				return (0);
			tmp = ft_strchr(tmp, ',');
			if (tmp && *(++tmp))
				vec->z = ft_atof(tmp);
			else
				return (0);
			return (1);
		}
	}
	return (0);
}

int				get_as_vector2f(t_kvlexer *token, char *str, t_vector2f *vec)
{
	t_list		*node;
	t_kvlexer	*field;
	char		*tmp;

	if (token->children && (node = ft_lstsearch(token->children->head, &search_key, str)))
	{
		field = (t_kvlexer *)node->content;
		if (field && field->value && *field->value)
		{
			vec->x = ft_atof(field->value);
			tmp = ft_strchr(field->value, ',');
			if (tmp && *(++tmp))
				vec->y = ft_atof(tmp);
			else
				return (0);
			return (1);
		}
	}
	return (0);
}

int				get_as_float(t_kvlexer *token, char *str, float *f)
{
	t_list		*node;
	t_kvlexer	*field;

	if (token->children && (node = ft_lstsearch(token->children->head, &search_key, str)))
	{
		field = (t_kvlexer *)node->content;
		if (field && field->value && *field->value)
			*f = ft_atof(field->value);
		return (1);
	}
	return (0);
}

int				get_as_double(t_kvlexer *token, char *str, double *d)
{
	t_list		*node;
	t_kvlexer	*field;

	if (token->children && (node = ft_lstsearch(token->children->head, &search_key, str)))
	{
		field = (t_kvlexer *)node->content;
		if (field && field->value && *field->value)
			*d = ft_atof(field->value);
		return (1);
	}
	return (0);
}

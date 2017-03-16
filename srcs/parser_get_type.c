/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 16:07:58 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/16 14:28:31 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int				search_key(t_list *node, void *data)
{
	if (!ft_strcmp(((t_kvlexer *)node->content)->key, (char *)data))
		return (1);
	return (0);
}

t_vector3f		get_as_vector3f(t_kvlexer *token, char *str)
{
	t_list		*node;
	t_kvlexer	*field;
	char		*tmp;
	t_vector3f	vector;

	vector = create_vector3f(1, 1, 1);
	if ((node = ft_lstsearch(token->children->head, &search_key, str)))
	{
		field = (t_kvlexer *)node->content;
		if (field && field->value && *field->value)
		{
			vector.x = ft_atof(field->value);
			tmp = ft_strchr(field->value, ',');
			if (tmp && *(++tmp))
				vector.y = ft_atof(tmp);
			tmp = ft_strchr(tmp, ',');
			if (tmp && *(++tmp))
				vector.z = ft_atof(tmp);
		}
	}
	return (vector);
}

t_vector2f		get_as_vector2f(t_kvlexer *token, char *str)
{
	t_list		*node;
	t_kvlexer	*field;
	char		*tmp;
	t_vector2f	vector;

	vector = create_vector2f(1, 1);
	if ((node = ft_lstsearch(token->children->head, &search_key, str)))
	{
		field = (t_kvlexer *)node->content;
		if (field && field->value && *field->value)
		{
			vector.x = ft_atof(field->value);
			tmp = ft_strchr(field->value, ',');
			if (tmp && *(++tmp))
				vector.y = ft_atof(tmp);
		}
	}
	return (vector);
}

float			get_as_float(t_kvlexer *token, char *str)
{
	t_list		*node;
	t_kvlexer	*field;
	float		ret_float;

	ret_float = 100;
	if ((node = ft_lstsearch(token->children->head, &search_key, str)))
	{
		field = (t_kvlexer *)node->content;
		if (field && field->value && *field->value)
			ret_float = ft_atof(field->value);
	}
	return (ret_float);
}

float			get_as_double(t_kvlexer *token, char *str)
{
	t_list		*node;
	t_kvlexer	*field;
	double		ret_float;

	ret_float = 100;
	if ((node = ft_lstsearch(token->children->head, &search_key, str)))
	{
		field = (t_kvlexer *)node->content;
		if (field && field->value && *field->value)
			ret_float = ft_atof(field->value);
	}
	return (ret_float);
}

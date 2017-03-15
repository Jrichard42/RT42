/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_type2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 16:10:52 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/13 16:16:28 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

char			*get_as_string(t_kvlexer *token, char *str)
{
	t_list		*node;
	t_kvlexer	*field;
	char		*string;

	string = NULL;
	if ((node = ft_lstsearch(token->children->head, &search_key, str)))
	{
		field = (t_kvlexer *)node->content;
		if (!(string = ft_strdup(field->value)))
			return (NULL);
	}
	return (string);
}

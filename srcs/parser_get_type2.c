/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_type2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 16:10:52 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/24 15:06:37 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int				get_as_int(t_kvlexer *token, char *str, int *i)
{
	t_list		*node;
	t_kvlexer	*field;

	if (token->children && (node = ft_lstsearch(token->children->head,
		&search_key, str)))
	{
		field = (t_kvlexer *)node->content;
		if (field && field->value && *field->value)
			*i = ft_atoi(field->value);
		return (1);
	}
	return (0);
}

int				get_as_string(t_kvlexer *token, char *str, char *string)
{
	t_list		*node;
	t_kvlexer	*field;

	if (token->children && (node = ft_lstsearch(token->children->head,
		&search_key, str)))
	{
		field = (t_kvlexer *)node->content;
		if (!(string = ft_strdup(field->value)))
			return (0);
		return (1);
	}
	return (1);
}

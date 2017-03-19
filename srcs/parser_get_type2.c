/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_type2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 16:10:52 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/16 14:28:28 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

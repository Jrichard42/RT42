/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 14:00:00 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/23 18:20:01 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "parser.h"

t_kvlexer			*get_texture(t_kvlexer *token)
{
	t_list			*node;

	if (token->children &&
			(node = ft_lstsearch(token->children->head, &search_key, "TEXTURE")))
		return ((t_kvlexer *)node->content);
	return (NULL);
}

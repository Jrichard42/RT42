/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:14:02 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/13 16:14:23 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "parser.h"

t_damier		get_text_as_damier(t_kvlexer *token)
{
	t_damier	damier;

	damier.color_1 = get_as_vector3f(token, "COLOR_1");
	damier.color_2 = get_as_vector3f(token, "COLOR_2");
	return (damier);
}

/*t_perlin		get_text_as_perlin(t_kvlexer *token)
{
	t_perlin	perlin;

	perlin.turbpower = get_as_double(token, "TURBPOWER");
	perlin.turbsize = get_as_double(token, "TURBSIZE");
	perlin.periode = get_as_vector2f(token, "PERIODE");
	perlin.color = get_as_vector3f(token, "COLOR");
	perlin.type_perlin = get_as_string(token, "TYPE_PERLIN");
	return (perlin);
}*/

t_kvlexer		*get_texture(t_kvlexer *token)
{
	t_list		*node;

	if ((node = ft_lstsearch(token->children->head, &search_key, "TEXTURE")))
		return ((t_kvlexer *)node->content);
	return (NULL);
}

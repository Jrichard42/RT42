/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 14:00:00 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/30 17:41:19 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "parser.h"

int				get_texture(t_kvlexer *token, t_rt *rt, t_texture *tex)
{
	t_list		*node;
	t_kvlexer	*tex_token;

	if (token->children && (node = ft_lstsearch(token->children->head,
					&search_key, "TEXTURE")))
	{
		tex_token = (t_kvlexer *)node->content;
		if (tex_token->value)
		{
			if (rt->textures && (node = ft_lstsearch(rt->textures->head,
							&search_tex, tex_token->value)))
				*tex = *((t_texture *)node->content);
			else
			{
				ft_putstr("Couldn't find the TEXTURE named ");
				ft_putendl(tex_token->value);
				tex_token->value = NULL;
				return (0);
			}
			return (1);
		}
		else
			return (check_type_tex(tex_token, tex));
	}
	return (0);
}

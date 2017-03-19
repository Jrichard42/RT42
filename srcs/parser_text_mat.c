/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_text_mat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 09:20:34 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/19 17:55:18 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "obj_types.h"
#include "material.h"
#include "parser.h"
#include "ft_kvlexer.h"
#include "libft.h"

int						parser_text_mat(t_kvlexer *token, t_rt *rt)
{
	t_kvlexer			*kvlexer;
	t_list				*current_node;
	t_kvlexer			*current_child;

	if (!(kvlexer = ft_kvlexer(token->value)))
		return ((int)ft_error("Wrong file"));
	current_node = kvlexer->children->head;
	while (current_node)
	{
		current_child = (t_kvlexer *)current_node->content;
		if (!ft_strcmp(current_child->key, "MATERIAL\0"))
			create_mat(current_child, rt);
		else if (!ft_strcmp(current_child->key, "TEXTURE\0"))
			;//fill_text();
		else
			ft_error("Only materials and textures are allowed in this file");
		current_node = current_node->next;
	}
	free_kvlexer(kvlexer);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_material.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 13:57:58 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/23 16:59:15 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"
#include "parser.h"

static int		modify_material(t_kvlexer *mat_token, t_material *mat)
{
	if (!get_as_float(mat_token, "AMBIENT", &(mat->ka)) && (!mat_token->value
				|| !mat_token->value[0]))
		return ((int)ft_error("The MATERIAL should contain either "
		"a valid name or a field AMBIENT"));
	if (!get_as_float(mat_token, "DIFFUSE", &(mat->kd)) && (!mat_token->value
				|| !mat_token->value[0]))
		return ((int)ft_error("The MATERIAL should contain either "
		"a valid name or a field DIFFUSE"));
	if (!get_as_float(mat_token, "SPECULAR", &(mat->ks)) && (!mat_token->value
				|| !mat_token->value[0]))
		return ((int)ft_error("The MATERIAL should contain either "
		"a valid name or a field SPECULAR"));
	if (!get_as_int(mat_token, "SHININESS", &(mat->sh)) && (!mat_token->value
				|| !mat_token->value[0]))
		return ((int)ft_error("The MATERIAL should contain either "
		"a valid name or a field SHININESS"));
	if (!get_as_float(mat_token, "IR", &(mat->ir)) && (!mat_token->value
				|| !mat_token->value[0]))
		return ((int)ft_error("The MATERIAL should contain either "
		"a valid name or a field IR"));
	return (1);
}

int				get_material(t_kvlexer *token, t_rt *rt, t_material *mat)
{
	t_list		*node;
	t_kvlexer	*mat_token;

	if (token->children && (node = ft_lstsearch(token->children->head,
					&search_key, "MATERIAL")))
	{
		mat_token = (t_kvlexer *)node->content;
		if (mat_token->value && rt->materials)
		{
			if ((node = ft_lstsearch(rt->materials->head,
							&search_mat, mat_token->value)))
				*mat = *((t_material *)node->content);
			else
			{
				ft_putstr("Couldn't find the MATERIAL named ");
				ft_putendl(mat_token->value);
				mat_token->value = NULL;
			}
		}
		if (!modify_material(mat_token, mat))
			return (0);
	}
	return (1);
}

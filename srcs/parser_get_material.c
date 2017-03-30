/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_material.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 13:57:58 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/30 16:25:30 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"
#include "parser.h"

static int		modify_material_2(t_kvlexer *mat_token, t_material *mat)
{
	if (!get_as_float(mat_token, "IR", &(mat->ir)) && (!mat_token->value
				|| !mat_token->value[0]))
		return ((int)ft_error("The MATERIAL should contain either "
		"a valid name or a field IR"));
	if (!get_as_float(mat_token, "REFLECT", &(mat->reflect))
			&& (!mat_token->value
				|| !mat_token->value[0]))
		return ((int)ft_error("The MATERIAL should contain either "
		"a valid name or a field REFLECT"));
	if (!get_as_float(mat_token, "REFRACT", &(mat->refract))
			&& (!mat_token->value
				|| !mat_token->value[0]))
		return ((int)ft_error("The MATERIAL should contain either "
		"a valid name or a field REFRACT"));
	return (1);
}

static int		modify_material(t_kvlexer *mat_token, t_material *mat)
{
	if (!get_as_vector3f(mat_token, "AMBIENT", &(mat->ka)) && (!mat_token->value
				|| !mat_token->value[0]))
		return ((int)ft_error("The MATERIAL should contain either "
		"a valid name or a field AMBIENT"));
	if (!get_as_vector3f(mat_token, "DIFFUSE", &(mat->kd)) && (!mat_token->value
				|| !mat_token->value[0]))
		return ((int)ft_error("The MATERIAL should contain either "
		"a valid name or a field DIFFUSE"));
	if (!get_as_vector3f(mat_token, "SPECULAR",
				&(mat->ks)) && (!mat_token->value
				|| !mat_token->value[0]))
		return ((int)ft_error("The MATERIAL should contain either "
		"a valid name or a field SPECULAR"));
	if (!get_as_int(mat_token, "SHININESS", &(mat->sh)) && (!mat_token->value
				|| !mat_token->value[0]))
		return ((int)ft_error("The MATERIAL should contain either "
		"a valid name or a field SHININESS"));
	return (modify_material_2(mat_token, mat));
}

int				get_material(t_kvlexer *token, t_rt *rt, t_material *mat)
{
	t_list		*node;
	t_kvlexer	*mat_token;

	if (token->children && (node = ft_lstsearch(token->children->head,
					&search_key, "MATERIAL")))
	{
		mat_token = (t_kvlexer *)node->content;
		if (mat_token->value)
		{
			if (rt->materials && (node = ft_lstsearch(rt->materials->head,
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
		return (1);
	}
	return (2);
}

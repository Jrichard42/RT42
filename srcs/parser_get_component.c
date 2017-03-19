/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_component.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 13:09:46 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/16 14:27:50 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include "texture.h"
#include "parser.h"

t_material			get_material(t_kvlexer *token)
{
	t_list			*node;
	t_material		material;
	t_kvlexer		*mat_token;

	material.ka = 0.33;
	material.kd = 0.33;
	material.ks = 0.33;
	material.sh = 10;
	material.ir = 1.0;
	if ((node = ft_lstsearch(token->children->head, &search_key, "MATERIAL")))
	{
		mat_token = (t_kvlexer *)node->content;
		material.ka = get_as_float(mat_token, "AMBIENT");
		material.kd = get_as_float(mat_token, "DIFFUSE");
		material.ks = get_as_float(mat_token, "SPECULAR");
		material.sh = get_as_float(mat_token, "SHININESS");
		material.ir = get_as_float(mat_token, "IR");
	}
	return (material);
}

static t_damier		get_text_as_damier(t_kvlexer *token)
{
	t_damier		damier;

	damier.color_1 = get_as_vector3f(token, "COLOR_1");
	damier.color_2 = get_as_vector3f(token, "COLOR_2");
	return (damier);
}

static t_perlin		get_text_as_perlin(t_kvlexer *token)
{
	t_perlin		perlin;

	perlin.turbpower = get_as_double(token, "TURBPOWER");
	perlin.turbsize = get_as_double(token, "TURBSIZE");
	perlin.periode = get_as_vector2f(token, "PERIODE");
	perlin.color = get_as_vector3f(token, "COLOR");
	perlin.type_perlin = get_as_string(token, "TYPE_PERLIN");
	return (perlin);
}

t_kvlexer			*get_texture(t_kvlexer *token)
{
	t_list			*node;

	if ((node = ft_lstsearch(token->children->head, &search_key, "TEXTURE")))
		return ((t_kvlexer *)node->content);
	return (NULL);
}

t_light				get_light(t_kvlexer *token)
{
	t_list			*node;
	t_light			light;
	t_kvlexer		*light_token;

	light.color = create_vector3f(0, 0, 0);
	light.intensity = 10.0;
	if ((node = ft_lstsearch(token->children->head, &search_key, "LIGHT")))
	{
		light_token = (t_kvlexer *)node->content;
		light.color = get_as_vector3f(light_token, "COLOR");
		light.intensity = get_as_float(light_token, "INTENSITY");
		light.calc_light = &calcul_light;
	}
	return (light);
}

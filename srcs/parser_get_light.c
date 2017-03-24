/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 14:00:52 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/23 14:01:16 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include "parser.h"

t_light				get_light(t_kvlexer *token)
{
	t_list			*node;
	t_light			light;
	t_kvlexer		*light_token;

	light.color = create_vector3f(255, 255, 255);
	light.intensity = 10;
	light.calc_light = &calcul_light;
	if (token->children && (node = ft_lstsearch(token->children->head,
		&search_key, "LIGHT")))
	{
		light_token = (t_kvlexer *)node->content;
		get_as_vector3f(light_token, "COLOR", &(light.color));
		get_as_float(light_token, "INTENSITY", &(light.intensity));
		light.calc_light = &calcul_light;
	}
	return (light);
}

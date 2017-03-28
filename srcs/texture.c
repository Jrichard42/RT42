/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 16:28:56 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/28 15:34:17 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "parser.h"
#include "bruit_perlin.h"
#include "libft.h"

t_vector3f					get_tex_point(t_texture tex, float u, float v)
{
	t_vector3f				color;
	int						x;
	int						y;

	if (u < 0.0f)
        x = (int)(((1.0f - ((long int)u - u))) * tex.width);
    else
        x = (int)(u * tex.width);
    if (v < 0.0f)
        y = (int)(((1.0f - ((long int)v - v))) * tex.height);
    else
        y = (int)(v * tex.height);
	color = tex.data[y % tex.height][x % tex.width];
	return (color);
}

int							malloc_tex(t_texture *tex)
{
	int y;

	y = 0;
	if (!(tex->data = malloc(sizeof(t_vector3f *) * tex->height)))
		return (0);
	while (y < tex->height)
	{
		if (!(tex->data[y] = malloc(sizeof(t_vector3f) * tex->width)))
			return (0);
		y++;
	}
	return (1);
}

int							search_tex(t_list *node, void *data)
{
	if (!ft_strcmp(((t_texture *)node->content)->name, (char *)data))
		return (1);
	return (0);
}

int							check_type_tex(t_kvlexer *token, t_texture *tex)
{
	static t_ptr_tex_type	ptr_tex_type[5] = {{"WOOD\0", NULL},
						{"MARBLE\0", NULL}, {"SKY\0", NULL},
						{"DAMIER\0", &damier_tex}, {"PERLIN\0", NULL}};
	int						i;
	char					*type;

	i = 0;
	type = NULL;
	if (!get_as_string(token, "TYPE", &type))
		return ((int)ft_error("The TEXTURE should contain a field TYPE"));
	while (i < 5)
	{
		if (!ft_strcmp(type, ptr_tex_type[i].type))
		{
			if (!ptr_tex_type[i].create(token, tex))
			{
				return (error_parser("Unable to create the texture ",
							tex->name));
				ft_strdel(&type);
			}
			break ;
		}
		++i;
	}
	if (i == 5)
	{
		ft_strdel(&type);
		return (error_parser("Unknown texture type ", type));
	}
	ft_strdel(&type);
	return (1);
}

static int					create_tex2(t_kvlexer *token, t_texture *tex)
{
	ft_strncpy(tex->name, token->value, 10);
	if (ft_strlen(token->value) > 10)
	{
		ft_putstr("The TEXTURE name ");
		ft_putstr(token->value);
		ft_putstr(" is too long (10 characters max), it will be shortened to ");
		ft_putendl(tex->name);
	}
	check_type_tex(token, tex);
	return (1);
}

int							create_tex(t_kvlexer *token, t_rt *rt)
{
	t_texture				tex;
	t_list					*node;

	if (token->value)
	{
		if (rt->textures && (node = ft_lstsearch(rt->textures->head,
						&search_tex, token->value)))
		{
			ft_putstr("The texture named ");
			ft_putstr(token->value);
			return ((int)ft_error(" has already been created"));
		}
		else
		{
			if (!create_tex2(token, &tex))
				return (0);
			ft_lstadd(&rt->textures, ft_lstnew(&tex, sizeof(tex)));
		}
	}
	else
		ft_error("Textures in the .mat file should have a name");
	return (1);
}

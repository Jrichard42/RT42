/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 16:28:56 by jrichard          #+#    #+#             */
/*   Updated: 2017/04/03 14:39:10 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "parser.h"
#include "bruit_perlin.h"
#include "libft.h"

int							search_tex(t_list *node, void *data)
{
	if (!ft_strcmp(((t_texture *)node->content)->name, (char *)data))
		return (1);
	return (0);
}

static int					error_type_tex(char *type, char *error,
		char *error2)
{
	ft_strdel(&type);
	return (error_parser(error, error2));
}

int							check_type_tex(t_kvlexer *token, t_texture *tex)
{
	static t_ptr_tex_type	ptr_tex_type[4] = {{"WOOD\0", &wood_tex},
		{"MARBLE\0", &marble_tex}, {"SKY\0", &sky_tex},
		{"DAMIER\0", &damier_tex}};
	int						i;
	char					*type;

	i = 0;
	type = NULL;
	if (!get_as_string(token, "TYPE", &type))
		return ((int)ft_error("The TEXTURE should contain a field TYPE"));
	while (i < 4)
	{
		if (!ft_strcmp(type, ptr_tex_type[i].type))
		{
			if (!ptr_tex_type[i].create(token, tex))
				return (error_type_tex(type,
				"Unable to create the texture ", tex->name));
				break ;
		}
		++i;
	}
	if (i == 4)
		return (error_type_tex(type, "Unable texture type ", type));
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
	return (check_type_tex(token, tex));
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

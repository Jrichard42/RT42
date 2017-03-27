/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 16:28:56 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/27 13:59:58 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "parser.h"
#include "libft.h"

int	tex_wood(t_kvlexer *token, t_rt *rt, t_texture *tex)
{
	printf("Creating tex wood\n");
}
int	tex_marble(t_kvlexer *token, t_rt *rt, t_texture *tex)
{
	printf("Creating tex marble\n");
}
int	tex_sky(t_kvlexer *token, t_rt *rt, t_texture *tex)
{
	printf("Creating tex sky\n");
}

int tex_perlin(t_kvlexer *token, t_rt *rt, t_texture *tex)
{
	printf("Creating tex perlin\n");
}

t_vector3f		get_tex_point(t_texture tex, float u, float v)
{
	t_vector3f	color;
	int			x;
	int 		y;

	x = abs((int)(u * tex.width));
	y = abs((int)(v * tex.height));
	color = tex.data[y % tex.height][x % tex.width];
	//color = bilinear_filter(tex, x, y, 8);
	return (color);
}

int							search_tex(t_list *node, void *data)
{
	if (!ft_strcmp(((t_texture *)node->content)->name, (char *)data))
		return (1);
	return (0);
}

int							check_type_tex(t_kvlexer *token, t_rt *rt,
		t_texture *tex)
{
	static t_ptr_tex_type	ptr_tex_type[5] = {{"WOOD\0", &tex_wood},
											{"MARBLE\0", &tex_marble},
											{"SKY\0", &tex_sky},
											{"DAMIER\0", &tex_damier},
											{"PERLIN\0", &tex_perlin}};
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
			if (!ptr_tex_type[i].create(token, rt, tex))
				error_parser("Unable to create the texture ", tex->name);
			break ;
		}
		++i;
	}
	if (i == 5)
		error_parser("Unknown texture type ", type);
	return (1);
}

static int		create_tex2(t_kvlexer *token, t_rt *rt, t_texture *tex)
{
	ft_strncpy(tex->name, token->value, 10);
	if (ft_strlen(token->value) > 10)
	{
		ft_putstr("The TEXTURE name ");
		ft_putstr(token->value);
		ft_putstr(" is too long (10 characters max), it will be shortened to ");
		ft_putendl(tex->name);
	}
	check_type_tex(token, rt, tex);
	return (1);
}

int				create_tex(t_kvlexer *token, t_rt *rt)
{
	t_texture	tex;
	t_list		*node;

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
			if (!create_tex2(token, rt, &tex))
				return (0);
			ft_lstadd(&rt->textures, ft_lstnew(&tex, sizeof(tex)));
		}
	}
	else
		ft_error("Textures in the .mat file should have a name");
	return (1);
}

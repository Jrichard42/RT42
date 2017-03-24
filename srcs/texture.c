/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 16:28:56 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/24 18:27:41 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "parser.h"
#include "libft.h"

int				search_tex(t_list *node, void *data)
{
	if (!ft_strcmp(((t_texture *)node->content)->name, (char *)data))
		return (1);
	return (0);
}

static void		check_type()
{
	static t_ptr_type	ptr_type[12] = {{"SPHERE\0", &create_sphere},
	int					i;

	i = 0;
	while (i < 12)
	{
		if (!ft_strcmp(token->key, ptr_type[i].type))
		{
			if (!ptr_type[i].create(token, rt) && i != 11)
				error_parser("Unable to create the obj ", token->key);
			break ;
		}
		++i;
	}
	if (i == 12)
		error_parser("Unknown obj ", token->key);
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
	if (WOOD)
		wood();
	else if (DAMIER)
		damier(token, tex);
	return (1);
}

int				create_tex(t_kvlexer *token, t_rt *rt)
{
	t_texture	tex;
	t_list		*node;

	if (token->value)
	{
		printf("flibili\n");
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

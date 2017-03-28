/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 16:39:25 by jrichard          #+#    #+#             */
/*   Updated: 2017/03/27 16:20:14 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "obj_types.h"
#include "material.h"
#include "texture.h"
#include "parser.h"
#include "ft_kvlexer.h"
#include "libft.h"

int						error_parser(char *str, char *type)
{
	ft_putstr(str);
	ft_putendl(type);
	return (0);
}

static void				check_type(t_kvlexer *token, t_rt *rt)
{
	static t_ptr_type	ptr_type[15] = {{"SPHERE\0", &create_sphere},
			{"LIGHT\0", &create_light}, {"CAMERA\0", &create_camera},
			{"PLANE\0", &create_plane}, {"CYLINDER\0", &create_cylinder},
			{"TORUS\0", &create_torus}, {"TRIANGLE\0", &create_triangle},
			{"TETRAEDRE\0", &create_tetra}, {"PYRAMIDE\0", &create_pyra},
			{"BOX\0", &create_box}, {"CONE\0", &create_cone},
			{"FOG\0", &create_fog}, {"DISK\0", &create_disque},
			{"PARA\0", &create_paraboloide}, {"INCLUDE\0", &parser_text_mat}};
	int					i;

	i = 0;
	while (i < 15)
	{
		if (!ft_strcmp(token->key, ptr_type[i].type))
		{
			if (!ptr_type[i].create(token, rt) && i != 14)
				error_parser("Unable to create the obj ", token->key);
			break ;
		}
		++i;
	}
	if (i == 15)
		error_parser("Unknown obj ", token->key);
}

int						parser(char *name, t_rt *rt)
{
	t_kvlexer			*kvlexer;
	t_list				*current_child;

	if (!(kvlexer = ft_kvlexer(name)))
		return ((int)ft_error("Wrong file"));
	if (kvlexer->children)
		current_child = kvlexer->children->head;
	else
		return (0);
	while (current_child)
	{
		check_type((t_kvlexer *)current_child->content, rt);
		current_child = current_child->next;
	}
	free_kvlexer(kvlexer);
	if (!rt->camera)
		return ((int)ft_error("There should be a camera in the scene"));
	if (!rt->objs)
		return ((int)ft_error("The scene is empty"));
	return (1);
}

int						parser_text_mat(t_kvlexer *token, t_rt *rt)
{
	t_kvlexer			*kvlexer;
	t_list				*current_node;
	t_kvlexer			*current_child;

	if (!(kvlexer = ft_kvlexer(token->value)))
		return ((int)ft_error("Wrong file"));
	if (kvlexer->children)
		current_node = kvlexer->children->head;
	else
		return (0);
	while (current_node)
	{
		current_child = (t_kvlexer *)current_node->content;
		if (!ft_strcmp(current_child->key, "MATERIAL\0"))
			create_mat(current_child, rt);
		else if (!ft_strcmp(current_child->key, "TEXTURE\0"))
			create_tex(current_child, rt);
		else
			ft_error("Only materials and textures are allowed in this file");
		current_node = current_node->next;
	}
	free_kvlexer(kvlexer);
	return (1);
}

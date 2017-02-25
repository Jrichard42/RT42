/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 16:39:25 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/25 15:05:21 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "obj_types.h"
#include "parser.h"
#include "ft_kvlexer.h"
#include "libft.h"

static void				check_type(t_kvlexer *token, t_rt *rt)
{
	static t_ptr_type	ptr_type[6] = {{"SPHERE\0", &create_sphere},
										{"LIGHT\0", &create_light},
										{"CAMERA\0", &create_camera},
										{"PLANE\0", &create_plane},
										{"CYLINDER\0", &create_cylinder},
										{"CONE\0", &create_cone}};
	int					i;

	i = 0;
	while (i < 6)
	{
		if (!ft_strcmp(token->key, ptr_type[i].type))
		{
			if (!ptr_type[i].create(token, rt))
				printf("Unable to create the obj %s", token->key); // check
			break ;
		}
		++i;
	}
	if (i == 6)
		printf("Unknown obj %s", token->key); // check
}

int						parser(char *name, t_rt *rt)
{
	t_kvlexer			*kvlexer;
	t_list				*current_child;

	if (!(kvlexer = ft_kvlexer(name)))
		return ((int)ft_error("Wrong file"));
	current_child = kvlexer->children->head;
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

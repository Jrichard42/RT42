/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 16:39:25 by jrichard          #+#    #+#             */
/*   Updated: 2017/02/10 16:00:53 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void				check_type(t_kvlexer *token, t_raytracer *raytracer)
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
			if (!(ptr_type[i].create(token, rt)))
				error_sdl("Unable to create the obj ", token->key);
			break ;
		}
		++i;
	}
	if (i == 6)
		error_sdl("Unknown obj ", token->key);
}

int						parser(char *name, t_rt *rt)
{
	t_kvlexer			*kvlexer;
	t_list				*current_child;

	if (!(kvlexer = ft_kvlexer(name)))
		return ((int)error("Wrong format"));
	current_child = kvlexer->children->head;
	while (current_child)
	{
		check_type((t_kvlexer *)current_child->content, rt);
		current_child = current_child->next;
	}
	free_kvlexer(kvlexer);
	return (1);
}

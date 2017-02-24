/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:29:48 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/18 18:44:45 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "plane.h"
#include "quadratic.h"
#include "parser.h"

#define	PLANE ((t_plane *)obj->data)

static 	float		inter_plane(t_obj *obj, t_ray *ray)
{
	t_quadratic var;
	t_vector3f	tmp;

	if (dot_vector3f(ray->dir, PLANE->dir) != 0.0)
	{
		tmp = sub_vector3f(obj->pos, ray->start);
		var.a = dot_vector3f(tmp, PLANE->dir);
		var.a = var.a / dot_vector3f(ray->dir, PLANE->dir);
		var.result = var.a;
	}
	else
		return (NAN);
	return (var.result);
}

static t_vector3f	normal_plane(struct s_obj *obj, t_vector3f *impact)
{
	(void)impact;
	return (PLANE->dir);
}

int					create_plane(t_kvlexer *token, t_rt *rt)
{
	t_obj			*obj;

	if (!(obj = ft_memalloc(sizeof(*obj))))
		return (-1);
	if (!(obj->data = ft_memalloc(sizeof(t_plane))))
		return (-1);
	obj->normal = &normal_plane;
	obj->inter = &inter_plane;
	obj->pos = get_as_vector3f(token, "POSITION");
	obj->mat = get_material(token);
	obj->id = get_as_float(token, "ID");
	obj->is_src = get_as_float(token, "IS_SRC");
	obj->is_visible = get_as_float(token, "IS_VISIBLE");
	PLANE->dir = get_as_vector3f(token, "DIR");
	obj->color = get_as_vector3f(token, "COLOR");
	PLANE->dir = normalize_vector3f(PLANE->dir);
	ft_lstadd(&rt->objs, ft_lstnew(obj, sizeof(*obj)));
	ft_memdel((void **)&obj);
	return (0);
}

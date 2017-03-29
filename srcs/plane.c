/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:29:48 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/28 15:26:06 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "plane.h"
#include "quadratic.h"
#include "parser.h"
#include "inter.h"
#include "texture_shape.h"

#define PLANE ((t_plane *)obj->data)

static	float		inter_plane(t_obj *obj, t_ray *ray)
{
	t_quadratic		var;
	t_vector3f		tmp;

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

static int			create_plane2(t_kvlexer *token, t_rt *rt, t_obj *obj)
{
	if (!get_material(token, rt, &(obj->mat)))
		return (0);
	if (!get_texture(token, rt, &(obj->tex)))
		obj->texture = NULL;
	if (!get_as_vector3f(token, "POS", &(obj->pos)))
		return ((int)ft_error("The PLANE should contain a field POS"));
	if (!get_as_int(token, "ID", &(obj->id)))
		return ((int)ft_error("The PLANE should contain a field ID"));
	if (!get_as_int(token, "IS_SRC", &(obj->is_src)))
		return ((int)ft_error("The PLANE should contain a field IS_SRC"));
	if (obj->is_src)
		obj->light = get_light(token);
	if (!get_as_int(token, "IS_VISIBLE", &(obj->is_visible)))
		return ((int)ft_error("The PLANE should contain a field IS_VISIBLE"));
	if (!get_as_vector3f(token, "DIR", &(PLANE->dir)))
		return ((int)ft_error("The PLANE should contain a field DIR"));
	PLANE->dir = normalize_vector3f(PLANE->dir);
	return (1);
}

int					create_plane(t_kvlexer *token, t_rt *rt)
{
	t_obj			obj;

	if (!(obj.data = ft_memalloc(sizeof(t_plane))))
		return (0);
	obj.normal = &normal_plane;
	obj.inter = &inter_plane;
	obj.texture = &plane_tex;
	if (create_plane2(token, rt, &obj))
		ft_lstadd(&rt->objs, ft_lstnew(&obj, sizeof(obj)));
	else
	{
		free(obj.data);
		return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:29:48 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/19 18:02:30 by jrichard         ###   ########.fr       */
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

static void			base_plane(t_obj *obj, t_kvlexer *token, t_rt *rt)
{
	obj->pos = create_vector3f(0, 0, 0);
	obj->id = 0;
	obj->is_src = 0;
	obj->is_visible = 1;
	obj->color = create_vector3f(1, 1, 1);
	PLANE->dir = create_vector3f(0, 0, 1);
	obj->normal = &normal_plane;
	obj->inter = &inter_plane;
	obj->mat = get_material(token, rt);
}

int					create_plane(t_kvlexer *token, t_rt *rt)
{
	t_obj			obj;
	t_plane			*plane;

	if (!(obj.data = ft_memalloc(sizeof(t_plane))))
		return (0);
	plane = ((t_plane *)obj.data);
	base_plane(&obj, token, rt);
	get_as_vector3f(token, "POS", &(obj.pos));
	get_as_int(token, "ID", &(obj.id));
	get_as_int(token, "IS_SRC", &(obj.is_src));
	if (obj.is_src)
		obj.light = get_light(token);
	get_as_int(token, "IS_VISIBLE", &(obj.is_visible));
	get_as_vector3f(token, "COLOR", &(obj.color));
	get_as_vector3f(token, "DIR", &(plane->dir));
	plane->dir = normalize_vector3f(plane->dir);
	/*PLANE->damier = get_as_float(token, "DAMIER");
	PLANE->color1 = get_as_vector3f(token, "COLOR_DAMIER_1");
	PLANE->color2 = get_as_vector3f(token, "COLOR_DAMIER_2");*/
	ft_lstadd(&rt->objs, ft_lstnew(&obj, sizeof(obj)));
	return (1);
}

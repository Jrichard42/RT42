/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:29:48 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/25 14:25:02 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "plane.h"
#include "quadratic.h"
#include "parser.h"
#include "inter.h"

#define	PLANE ((t_plane *)obj->data)

static	t_vector3f	plane_tex(t_obj *self, t_inter inter)
{
	t_vector3f		color;

	return (color);
}

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
		return(NAN);
	if (var.result < 10000)
		return (var.result);
	else
		return (NAN);
	if (var.result > -10000)
		return (var.result);
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
		return (0);
	if (!(obj->data = ft_memalloc(sizeof(t_plane))))
		return (0);
	obj->normal = &normal_plane;
	obj->inter = &inter_plane;
	obj->texture = &plane_tex;
	obj->pos = get_as_vector3f(token, "POSITION");
	obj->mat = get_material(token);
	obj->id = get_as_float(token, "ID");
	obj->is_src = get_as_float(token, "IS_SRC");
	obj->is_visible = get_as_float(token, "IS_VISIBLE");
	PLANE->dir = get_as_vector3f(token, "DIR");
	PLANE->damier = get_as_float(token, "DAMIER");
	PLANE->color1 = get_as_vector3f(token, "COLOR_DAMIER_1");
	PLANE->color2 = get_as_vector3f(token, "COLOR_DAMIER_2");
	obj->color = get_as_vector3f(token, "COLOR");
	PLANE->dir = normalize_vector3f(PLANE->dir);
	obj->dir = PLANE->dir;
	ft_lstadd(&rt->objs, ft_lstnew(obj, sizeof(*obj)));
	ft_memdel((void **)&obj);
	return (1);
}

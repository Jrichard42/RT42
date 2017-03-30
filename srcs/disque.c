/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disque.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 15:07:48 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/03/30 15:58:11 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "disque.h"
#include "quadratic.h"
#include "parser.h"
#include "inter.h"

#define DISK ((t_disque *)obj->data)

static	t_vector3f	disque_tex(t_obj *self, t_inter inter)
{
	t_vector3f		color;
	t_vector3f		ua;
	t_vector3f		va;
	t_vector3f		uv;

	ua = create_vector3f(((t_disque *)self->data)->dir.y,
			((t_disque *)self->data)->dir.z, -((t_disque *)self->data)->dir.x);
	va = cross_vector3f(ua, ((t_disque *)self->data)->dir);
	uv.x = dot_vector3f(inter.impact, ua) * (1.0f / self->tex.width);
	uv.y = dot_vector3f(inter.impact, va) * (1.0f / self->tex.height);
	uv.z = 0;
	color = get_tex_point(self->tex, uv.x, uv.y);
	return (color);
}

static float		inter_disque(t_obj *obj, t_ray *ray)
{
	t_quadratic		var;
	t_vector3f		tmp;

	if (dot_vector3f(ray->dir, DISK->dir) != 0.0)
	{
		tmp = sub_vector3f(obj->pos, ray->start);
		var.a = dot_vector3f(tmp, DISK->dir);
		var.a = var.a / dot_vector3f(ray->dir, DISK->dir);
		var.result = var.a;
		tmp = add_vector3f(ray->start, mult_vector3f(ray->dir, var.a));
		tmp = sub_vector3f(obj->pos, tmp);
		if (sqrt(dot_vector3f(tmp, tmp)) > DISK->radius)
			return (NAN);
	}
	else
		return (NAN);
	return (var.result);
}

static t_vector3f	normal_disque(struct s_obj *obj, t_vector3f *impact)
{
	(void)impact;
	return (DISK->dir);
}

static int			create_disque2(t_kvlexer *token, t_rt *rt, t_obj *obj)
{
	if (!get_material(token, rt, &(obj->mat)))
		return (0);
	if (!get_texture(token, rt, &(obj->tex)))
	{
		obj->tex.data = NULL;
		obj->texture = NULL;
	}
	if (!get_as_vector3f(token, "POS", &(obj->pos)))
		return ((int)ft_error("The DISK should contain a field POS"));
	if (!get_as_int(token, "ID", &(obj->id)))
		return ((int)ft_error("The DISK should contain a field ID"));
	if (!get_as_int(token, "IS_SRC", &(obj->is_src)))
		return ((int)ft_error("The DISK should contain a field IS_SRC"));
	if (obj->is_src)
		obj->light = get_light(token);
	if (!get_as_int(token, "IS_VISIBLE", &(obj->is_visible)))
		return ((int)ft_error("The DISK should contain a field IS_VISIBLE"));
	if (!get_as_vector3f(token, "DIR", &(DISK->dir)))
		return ((int)ft_error("The DISK should contain a field DIR"));
	DISK->dir = normalize_vector3f(DISK->dir);
	if (!get_as_float(token, "RADIUS", &DISK->radius))
		return ((int)ft_error("The DISK should contain a field RADIUS"));
	return (1);
}

int					create_disque(t_kvlexer *token, t_rt *rt)
{
	t_obj			obj;

	if (!(obj.data = ft_memalloc(sizeof(t_disque))))
		return (0);
	obj.normal = &normal_disque;
	obj.inter = &inter_disque;
	obj.texture = &disque_tex;
	obj.destroy = NULL;
	if (create_disque2(token, rt, &obj))
		ft_lstadd(&rt->objs, ft_lstnew(&obj, sizeof(obj)));
	else
	{
		free(obj.data);
		return (0);
	}
	return (1);
}

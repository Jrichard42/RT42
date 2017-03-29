/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_shape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 18:48:12 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/29 18:48:13 by abitoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "obj.h"
#include "libft_matrix.h"
#include "plane.h"

#define PLANE ((t_plane *)obj->data)

t_vector3f			plane_tex(t_obj *obj, t_inter inter)
{
	t_vector3f		color;
	t_vector3f		ua;
	t_vector3f		va;
	t_vector3f		uv;

	ua = create_vector3f(PLANE->dir.y, PLANE->dir.z, -PLANE->dir.x);
	va = cross_vector3f(ua, PLANE->dir);
	uv.x = dot_vector3f(inter.impact, ua) * (1.0f / obj->tex.width);
	uv.y = dot_vector3f(inter.impact, va) * (1.0f / obj->tex.height);
	uv.z = 0;
	color = get_tex_point(obj->tex, uv.x, uv.y);
	return (color);
}

t_vector3f			sphere_tex(t_obj *self, t_inter inter)
{
	t_vector3f		color;
	t_vector3f		pos;
	t_vector3f		uv;

	pos = sub_vector3f(inter.obj->pos, inter.impact);
	pos = normalize_vector3f(pos);
	uv.x = asinf(pos.x) / M_PI + 0.5f;
	uv.y = asinf(pos.y) / M_PI + 0.5f;
	color = get_tex_point(self->tex, uv.x, uv.y);
	return (color);
}

t_vector3f			cone_tex(t_obj *self, t_inter inter)
{
	t_vector3f		color;

	color = create_vector3f(0, 0, 0);
	return (color);
}

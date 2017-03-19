/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 16:51:50 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/03/19 18:02:13 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangle.h"
#define TRIANGLE ((t_triangle *)obj->data)
#define FLOAT_ZERO 0.0001f

static float		inter_triangle(t_obj *obj, t_ray *ray)
{
	t_var var;

	var.e1 = sub_vector3f(TRIANGLE->vertex[1], TRIANGLE->vertex[0]);
	var.e2 = sub_vector3f(TRIANGLE->vertex[2], TRIANGLE->vertex[0]);
	var.pvector = cross_vector3f(ray->dir, var.e2);
	var.determinant = dot_vector3f(var.e1, var.pvector);
	if (fabs(var.determinant) < FLOAT_ZERO)
		return (NAN);
	var.invertedeterminant = 1.0f / var.determinant;
	var.tvec = sub_vector3f(ray->start, TRIANGLE->vertex[0]);
	var.lambda = dot_vector3f(var.tvec, var.pvector);
	var.lambda *= var.invertedeterminant;
	if (var.lambda < 0.0f || var.lambda > 1.0f)
		return (NAN);
	var.qvec = cross_vector3f(var.tvec, var.e1);
	var.mue = dot_vector3f(ray->dir, var.qvec);
	var.mue *= var.invertedeterminant;
	if (var.mue < 0.0f || var.mue + var.lambda > 1.0f)
		return (NAN);
	var.f = dot_vector3f(var.e2, var.qvec);
	var.f = var.f * var.invertedeterminant - FLOAT_ZERO;
	return (var.f);
}

static void			cal_normal_triangle(t_triangle *t)
{
	t_vector3f	e1;
	t_vector3f	e2;

	e1 = sub_vector3f(t->vertex[1], t->vertex[0]);
	e2 = sub_vector3f(t->vertex[2], t->vertex[0]);
	t->normal = normalize_vector3f(cross_vector3f(e1, e2));
}

static t_vector3f	normal_triangle(struct s_obj *obj, t_vector3f *impact)
{
	(void)impact;
	return (TRIANGLE->normal);
}

static void			base_triangle(t_obj *obj, t_kvlexer *token, t_rt *rt)
{
	obj->pos = create_vector3f(0, 0, 0);
	obj->id = 0;
	obj->is_src = 0;
	obj->is_visible = 1;
	obj->color = create_vector3f(1, 1, 1);
	TRIANGLE->vertex[0] = create_vector3f(0, 0, 1); //set base
	TRIANGLE->vertex[1] = create_vector3f(0, 0, 1); //set base
	TRIANGLE->vertex[2] = create_vector3f(0, 0, 1); //set base
	obj->normal = &normal_triangle;
	obj->inter = &inter_triangle;
	obj->mat = get_material(token, rt);
}

int					create_triangle(t_kvlexer *token, t_rt *rt)
{
	t_obj			obj;
	t_triangle		*triangle;

	if (!(obj.data = ft_memalloc(sizeof(t_triangle))))
		return (0);
	triangle = ((t_triangle *)obj.data);
	base_triangle(&obj, token, rt);
	get_as_vector3f(token, "POS", &(obj.pos));
	get_as_int(token, "ID", &(obj.id));
	get_as_int(token, "IS_SRC", &(obj.is_src));
	if (obj.is_src)
		obj.light = get_light(token);
	get_as_int(token, "IS_VISIBLE", &(obj.is_visible));
	get_as_vector3f(token, "COLOR", &(obj.color));
	get_as_vector3f(token, "VERTEX0", &(triangle->vertex[0]));
	triangle->vertex[0] = add_vector3f(obj.pos, triangle->vertex[0]);
	get_as_vector3f(token, "VERTEX1", &(triangle->vertex[1]));
	triangle->vertex[1] = add_vector3f(obj.pos, triangle->vertex[1]);
	get_as_vector3f(token, "VERTEX2", &(triangle->vertex[2]));
	triangle->vertex[2] = add_vector3f(obj.pos, triangle->vertex[2]);
	cal_normal_triangle(triangle);
	ft_lstadd(&rt->objs, ft_lstnew(&obj, sizeof(obj)));
	return (1);
}

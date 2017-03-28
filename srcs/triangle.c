/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 16:51:50 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/03/23 15:18:54 by jrichard         ###   ########.fr       */
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

static int			create_triangle2(t_kvlexer *token, t_rt *rt, t_obj *obj)
{
	if (!get_material(token, rt, &(obj->mat)))
		return (0);
	if (!get_texture(token, rt, &(obj->tex)))
		obj->texture = NULL;
	if (!get_as_vector3f(token, "POS", &(obj->pos)))
		return ((int)ft_error("The TRIANGLE should contain a field POS"));
	if (!get_as_int(token, "ID", &(obj->id)))
		return ((int)ft_error("The TRIANGLE should contain a field ID"));
	if (!get_as_int(token, "IS_SRC", &(obj->is_src)))
		return ((int)ft_error("The TRIANGLE should contain a field IS_SRC"));
	if (obj->is_src)
		obj->light = get_light(token);
	if (!get_as_int(token, "IS_VISIBLE", &(obj->is_visible)))
		return ((int)ft_error("The TRIANGLE should contain "
		"a field IS_VISIBLE"));
	if (!get_as_vector3f(token, "VERTEX0", &(TRIANGLE->vertex[0])) ||
			!get_as_vector3f(token, "VERTEX1", &(TRIANGLE->vertex[1])) ||
			!get_as_vector3f(token, "VERTEX2", &(TRIANGLE->vertex[0])))
		return ((int)ft_error("The TRIANGLE should contain "
		"3 fields VERTEX0-2"));
	TRIANGLE->vertex[0] = add_vector3f(obj->pos, TRIANGLE->vertex[0]);
	TRIANGLE->vertex[1] = add_vector3f(obj->pos, TRIANGLE->vertex[1]);
	TRIANGLE->vertex[2] = add_vector3f(obj->pos, TRIANGLE->vertex[2]);
	cal_normal_triangle(TRIANGLE);
	return (1);
}

int					create_triangle(t_kvlexer *token, t_rt *rt)
{
	t_obj			obj;

	if (!(obj.data = ft_memalloc(sizeof(t_triangle))))
		return (0);
	obj.normal = &normal_triangle;
	obj.inter = &inter_triangle;
	if (create_triangle2(token, rt, &obj))
		ft_lstadd(&rt->objs, ft_lstnew(&obj, sizeof(obj)));
	else
	{
		free(obj.data);
		return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetraedre_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 19:53:46 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/30 20:09:18 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetraedre.h"
#define TETRA ((t_tetra *)obj->data)
#define FLOAT_ZERO 0.0001f

float				inter_triangles(t_triangle *t, t_ray *ray)
{
	t_var var;

	var.e1 = sub_vector3f(t->vertex[1], t->vertex[0]);
	var.e2 = sub_vector3f(t->vertex[2], t->vertex[0]);
	var.pvector = cross_vector3f(ray->dir, var.e2);
	var.determinant = dot_vector3f(var.e1, var.pvector);
	if (fabs(var.determinant) < FLOAT_ZERO)
		return (NAN);
	var.invertedeterminant = 1.0f / var.determinant;
	var.tvec = sub_vector3f(ray->start, t->vertex[0]);
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

int					create_tetra3(t_kvlexer *token, t_obj *obj)
{
	t_vector3f vert[4];

	if (!get_as_int(token, "IS_VISIBLE", &(obj->is_visible)))
		return ((int)ft_error("The TETRA should contain "
		"a field IS_VISIBLE"));
	if (!get_as_vector3f(token, "VERTEX0", &(vert[0])) ||
			!get_as_vector3f(token, "VERTEX1", &(vert[1])) ||
			!get_as_vector3f(token, "VERTEX2", &(vert[2])) ||
			!get_as_vector3f(token, "VERTEX3", &(vert[3])))
		return ((int)ft_error("The TETRA should contain "
		"4 fields VERTEX0-3"));
	vert[0] = add_vector3f(obj->pos, vert[0]);
	vert[1] = add_vector3f(obj->pos, vert[1]);
	vert[2] = add_vector3f(obj->pos, vert[2]);
	vert[3] = add_vector3f(obj->pos, vert[3]);
	TETRA->face = create_tetra_bis(vert[0], vert[1], vert[2], vert[3]);
	calc_normal_tetra(TETRA);
	return (1);
}

void				destroy_tetra(struct s_obj *obj)
{
	int i;

	i = 0;
	while (i < 4)
		ft_memdel(&TETRA->face[i++]);
}

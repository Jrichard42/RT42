/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetraedre.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 17:11:11 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/03/08 17:11:12 by jqueyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetraedre.h"
#define TETRA ((t_tetra *)obj->data)
#define FLOAT_ZERO 0.0001f

static float		inter_triangle(t_triangle *t, t_ray *ray)
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

static float		inter_tetra(t_obj *obj, t_ray *ray)
{
	float	inter;
	float	tmp;
	int		i;

	inter = NAN;
	i = 0;
	while (i < 4)
	{
		tmp = inter_triangle(&TETRA->face[i], ray);
		if (((!isnan(tmp) && tmp < inter) || (!isnan(tmp) &&
			isnan(inter))))
		{
			TETRA->touch = i;
			inter = tmp;
		}
		i++;
	}
	if (inter < 0)
	{
		TETRA->touch = -1;
		inter = NAN;
	}
	return (inter);
}

static t_vector3f	normal_tetra(struct s_obj *obj, t_vector3f *impact)
{
	t_vector3f normale;
	t_vector3f e1;
	t_vector3f e2;
	t_triangle t;

	t = TETRA->face[TETRA->touch];
	e1 = sub_vector3f(t.vertex[1], t.vertex[0]);
	e2 = sub_vector3f(t.vertex[2], t.vertex[0]);
	normale = (cross_vector3f(e1, e2));
	normale.x = fabs(normale.x) * sgn(impact->x) * -1;
	normale.y = fabs(normale.y) * sgn(impact->y) * -1;
	normale.z = fabs(normale.z) * sgn(impact->z) * -1;
	return (normalize_vector3f(normale));
}

static t_triangle	*create_tetra_bis(t_vector3f v1, t_vector3f v2,
	t_vector3f v3, t_vector3f v4)
{
	t_triangle *t;

	if (!(t = (t_triangle*)ft_memalloc(4 * sizeof(t_triangle))))
		return (NULL);
	t[0].vertex[0] = v1;
	t[0].vertex[1] = v2;
	t[0].vertex[2] = v3;
	t[1].vertex[0] = v1;
	t[1].vertex[1] = v2;
	t[1].vertex[2] = v4;
	t[2].vertex[0] = v1;
	t[2].vertex[1] = v3;
	t[2].vertex[2] = v4;
	t[3].vertex[0] = v2;
	t[3].vertex[1] = v3;
	t[3].vertex[2] = v4;
	return (t);
}

int					create_tetra(t_kvlexer *token, t_rt *rt)
{
	t_obj			*obj;

	if (!(obj = ft_memalloc(sizeof(*obj))))
		return (0);
	if (!(obj->data = ft_memalloc(sizeof(t_tetra))))
		return (0);
	obj->normal = &normal_tetra;
	obj->inter = &inter_tetra;
	obj->pos = get_as_vector3f(token, "POS");
	obj->mat = get_material(token);
	obj->id = get_as_float(token, "ID");
	obj->is_src = get_as_float(token, "IS_SRC");
	obj->is_visible = get_as_float(token, "IS_VISIBLE");
	TETRA->face = create_tetra_bis(add_vector3f(obj->pos,
		get_as_vector3f(token, "VERTEX0")),
					add_vector3f(obj->pos, get_as_vector3f(token, "VERTEX1")),
					add_vector3f(obj->pos, get_as_vector3f(token, "VERTEX2")),
					add_vector3f(obj->pos, get_as_vector3f(token, "VERTEX3")));
	obj->color = get_as_vector3f(token, "COLOR");
	ft_lstadd(&rt->objs, ft_lstnew(obj, sizeof(*obj)));
	ft_memdel((void **)&obj);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetraedre.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 17:11:11 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/03/23 15:19:15 by jrichard         ###   ########.fr       */
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

static float		inter_tetra(t_obj *obj, t_ray *ray)
{
	float	inter;
	float	tmp;
	int		i;

	inter = NAN;
	i = 0;
	while (i < 4)
	{
		tmp = inter_triangles(&TETRA->face[i], ray);
		if (((!isnan(tmp) && tmp < inter) || (!isnan(tmp) &&
						isnan(inter))))
			inter = tmp;
		i++;
	}
	if (inter < 0)
		inter = NAN;
	return (inter);
}

static t_vector3f	normal_tetra(struct s_obj *obj, t_vector3f *impact)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (i < 6)
	{
		if (if_touch(&TETRA->face[i], impact))
			res = i;
		i++;
	}
	return (TETRA->face[res].normal);
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

static void			base_tetra(t_obj *obj, t_kvlexer *token, t_rt *rt)
{
	obj->pos = create_vector3f(0, 0, 0);
	obj->id = 0;
	obj->is_src = 0;
	obj->is_visible = 1;
	obj->color = create_vector3f(1, 1, 1);
	//base value tetra	
	obj->normal = &normal_tetra;
	obj->inter = &inter_tetra;
	//obj->mat = get_material(token, rt);
}

int					create_tetra(t_kvlexer *token, t_rt *rt)
{
	t_obj			obj;
	t_tetra			*tetra;

	if (!(obj.data = ft_memalloc(sizeof(t_tetra))))
		return (0);
	tetra = ((t_tetra *)obj.data);
	base_tetra(&obj, token, rt);
	get_as_vector3f(token, "POS", &(obj.pos));
	get_as_int(token, "ID", &(obj.id));
	get_as_int(token, "IS_SRC", &(obj.is_src));
	if (obj.is_src)
		obj.light = get_light(token);
	get_as_int(token, "IS_VISIBLE", &(obj.is_visible));
	get_as_vector3f(token, "COLOR", &(obj.color));
	//	TETRA->face = create_tetra_bis(add_vector3f(obj->pos,
	//				get_as_vector3f(token, "VERTEX0")),
	//			add_vector3f(obj->pos, get_as_vector3f(token, "VERTEX1")),
	//			add_vector3f(obj->pos, get_as_vector3f(token, "VERTEX2")),
	//			add_vector3f(obj->pos, get_as_vector3f(token, "VERTEX3"))); // TODO
	//	calc_normal_tetra(TETRA);
	ft_lstadd(&rt->objs, ft_lstnew(&obj, sizeof(obj)));
	return (1);
}

/*static int			create_tetra2(t_kvlexer *token, t_rt *rt, t_obj *obj)
{
	t_vertex		vert;

	obj->mat = get_material(token, rt);
	if (!get_as_vector3f(token, "POS", &(obj->pos)))
		return ((int)ft_error("The TETRAEDRE should contain a field POS"));
	if (!get_as_int(token, "ID", &(obj->id)))
		return ((int)ft_error("The TETRAEDRE should contain a field ID"));
	if (!get_as_int(token, "IS_SRC", &(obj->is_src)))
		return ((int)ft_error("The TETRAEDRE should contain a field IS_SRC"));
	if (obj->is_src)
		obj->light = get_light(token);
	if (!get_as_int(token, "IS_VISIBLE", &(obj->is_visible)))
		return ((int)ft_error("The TETRAEDRE should contain a field IS_VISIBLE"));
	if (!get_as_vector3f(token, "COLOR", &(obj->color)))
		return ((int)ft_error("The TETRAEDRE should contain a field COLOR"));
	if (!get_as_vector3f(token, "VERTEX0", &(vert.v1)) ||
			!get_as_vector3f(token, "VERTEX1", &(vert.v2)) ||
			!get_as_vector3f(token, "VERTEX2", &(vert.v3)) ||
			!get_as_vector3f(token, "VERTEX3", &(vert.v4)))
		return ((int)ft_error("The TRIANGLE should contain 4 fields VERTEX0-3"));
	
	calc_normal_pyra(TETRA);
	return (1);
}

int					create_tetra(t_kvlexer *token, t_rt *rt)
{
	t_obj			obj;

	if (!(obj.data = ft_memalloc(sizeof(t_pyra))))
		return (0);
	obj.normal = &normal_tetra;
	obj.inter = &inter_tetra;
	if (create_tetra2(token, rt, &obj))
		ft_lstadd(&rt->objs, ft_lstnew(&obj, sizeof(obj)));
	else
	{
		free(obj.data);
		return (0);
	}
	return (1);
}*/

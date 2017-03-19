/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramide.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 17:18:19 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/03/19 18:04:54 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pyramide.h"
#define PYRA ((t_pyra *)obj->data)
#define FLOAT_ZERO 0.0001f

static float		inter_pyra(t_obj *obj, t_ray *ray)
{
	float	inter;
	float	tmp;
	int		i;

	inter = NAN;
	i = 0;
	while (i < 6)
	{
		tmp = inter_triangles(&PYRA->face[i], ray);
		if (((!isnan(tmp) && tmp < inter) || (!isnan(tmp) &&
						isnan(inter))))
			inter = tmp;
		i++;
	}
	if (inter < 0)
		inter = NAN;
	return (inter);
}

int					if_touch(t_triangle *t, t_vector3f *impact)
{
	float d;

	d = dot_vector3f(t->normal, t->vertex[0]);
	if (((dot_vector3f(*impact, t->normal) - d) < 0.0005f)
			&& ((dot_vector3f(*impact, t->normal) - d) > -0.0005f))
		return (1);
	return (0);
}

static t_vector3f	normal_pyra(struct s_obj *obj, t_vector3f *impact)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (i < 6)
	{
		if (if_touch(&PYRA->face[i], impact))
			res = i;
		i++;
	}
	return (PYRA->face[res].normal);
}

static t_triangle	*create_pyra_bis(t_vertex *vert)
{
	t_triangle *t;

	if (!(t = (t_triangle*)ft_memalloc(6 * sizeof(t_triangle))))
		return (NULL);
	t[0].vertex[0] = vert->sommet;
	t[0].vertex[1] = vert->v1;
	t[0].vertex[2] = vert->v2;
	t[1].vertex[0] = vert->sommet;
	t[1].vertex[1] = vert->v2;
	t[1].vertex[2] = vert->v3;
	t[2].vertex[0] = vert->sommet;
	t[2].vertex[1] = vert->v3;
	t[2].vertex[2] = vert->v4;
	t[3].vertex[0] = vert->sommet;
	t[3].vertex[1] = vert->v1;
	t[3].vertex[2] = vert->v4;
	t[4].vertex[0] = vert->v1;
	t[4].vertex[1] = vert->v2;
	t[4].vertex[2] = vert->v3;
	t[5].vertex[0] = vert->v1;
	t[5].vertex[1] = vert->v3;
	t[5].vertex[2] = vert->v4;
	return (t);
}

static void			base_pyra(t_obj *obj, t_kvlexer *token, t_rt *rt)
{
	obj->pos = create_vector3f(0, 0, 0);
	obj->id = 0;
	obj->is_src = 0;
	obj->is_visible = 1;
	obj->color = create_vector3f(1, 1, 1);
	//base value pyra
	obj->normal = &normal_pyra;
	obj->inter = &inter_pyra;
	obj->mat = get_material(token, rt);
}

int					create_pyra(t_kvlexer *token, t_rt *rt)
{
	t_obj			obj;
	t_pyra			*pyra;
	t_vertex		vert;

	if (!(obj.data = ft_memalloc(sizeof(t_pyra))))
		return (0);
	pyra = ((t_pyra *)obj.data);
	base_pyra(&obj, token, rt);
	get_as_vector3f(token, "POS", &(obj.pos));
	get_as_int(token, "ID", &(obj.id));
	get_as_int(token, "IS_SRC", &(obj.is_src));
	if (obj.is_src)
		obj.light = get_light(token);
	get_as_int(token, "IS_VISIBLE", &(obj.is_visible));
	get_as_vector3f(token, "COLOR", &(obj.color));
/*	vert.sommet = add_vector3f(obj->pos, get_as_vector3f(token, "SOMMET"));
	vert.v1 = add_vector3f(obj->pos, get_as_vector3f(token, "VERTEX0"));
	vert.v2 = add_vector3f(obj->pos, get_as_vector3f(token, "VERTEX1"));
	vert.v3 = add_vector3f(obj->pos, get_as_vector3f(token, "VERTEX2"));
	vert.v4 = add_vector3f(obj->pos, get_as_vector3f(token, "VERTEX3"));
	PYRA->face = create_pyra_bis(&vert);
	calc_normal_pyra(PYRA);*/ // TODO
	ft_lstadd(&rt->objs, ft_lstnew(&obj, sizeof(obj)));
	return (1);
}

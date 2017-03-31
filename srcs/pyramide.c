/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramide.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 17:18:19 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/03/30 20:12:59 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pyramide.h"
#define PYRA ((t_pyra *)obj->data)
#define FLOAT_ZERO 0.0001f

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

static int			create_pyra2(t_kvlexer *token, t_rt *rt, t_obj *obj)
{
	t_vertex		vert;

	create_pyra3(token, rt, obj);
	if (!get_as_int(token, "IS_VISIBLE", &(obj->is_visible)))
		return ((int)ft_error("The PYRAMIDE should contain IS_VISIBLE"));
	if (!get_as_vector3f(token, "SOMMET", &(vert.sommet)))
		return ((int)ft_error("The PYRAMIDE should contain a field SOMMET"));
	if (!get_as_vector3f(token, "VERTEX0", &(vert.v1)) ||
			!get_as_vector3f(token, "VERTEX1", &(vert.v2)) ||
			!get_as_vector3f(token, "VERTEX2", &(vert.v3)) ||
			!get_as_vector3f(token, "VERTEX3", &(vert.v4)))
		return ((int)ft_error("The PYRAMIDE should contain"
		" 4 fields VERTEX0-3"));
	vert.sommet = add_vector3f(obj->pos, vert.sommet);
	vert.v4 = add_vector3f(obj->pos, vert.v4);
	vert.v1 = add_vector3f(obj->pos, vert.v1);
	vert.v2 = add_vector3f(obj->pos, vert.v2);
	vert.v3 = add_vector3f(obj->pos, vert.v3);
	PYRA->face = create_pyra_bis(&vert);
	calc_normal_pyra(PYRA);
	return (1);
}

int					create_pyra(t_kvlexer *token, t_rt *rt)
{
	t_obj			obj;

	if (!(obj.data = ft_memalloc(sizeof(t_pyra))))
		return (0);
	obj.normal = &normal_pyra;
	obj.inter = &inter_pyra;
	obj.texture = NULL;
	obj.destroy = &destroy_pyra;
	if (create_pyra2(token, rt, &obj))
		ft_lstadd(&rt->objs, ft_lstnew(&obj, sizeof(obj)));
	else
	{
		free(obj.data);
		return (0);
	}
	return (1);
}

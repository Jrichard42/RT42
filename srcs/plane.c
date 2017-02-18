/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:29:48 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/18 18:30:29 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "plane.h"
#include "quadratic.h"

#define	PLANE ((t_plane *)obj->data)

static 	float		inter_plane(t_obj *obj, t_ray *ray)
{
	t_quadratic var;

	if (scalaire_prod_vector(&ray->dir, &plan->normale) != 0.0)
	{
		sub_vector(&ray->start, &plan->point_plane, &tmp);
		a = scalaire_prod_vector(&tmp, &plan->normal);
		a = a / scalaire_prod_vector(&ray->dir, &plan->normal);
		result = a;
	}
	else
		return (nan);
	return (result);
}

static t_vector3f	normal_plane(struct s_obj *obj, t_vector3f *impact)
{
	return(PLANE->dir);
}

int					create_plane(t_kvlexer *token, t_rt *rt)
{
	t_obj			*obj;

	if (!(obj = ft_memalloc(sizeof(*obj))))
		return (-1);
	if (!(obj->data = ft_memalloc(sizeof(t_plane))))
		return (-1);
	obj->normal = &normal_plane;
	obj->inter = &inter_plane;
	obj->pos = get_as_vector3f(token, "POSITION");
	obj->mat = get_material(token);
	obj->id = get_as_float(token, "ID");
	obj->is_src = get_as_float(token, "IS_SRC");
	obj->is_visible = get_as_float(token, "IS_VISIBLE");
	PLANE->dir = get_as_vector3f(token, "DIR");
	PLANE->dir = normalize_vector3f(PLANE->dir);
	ft_lstadd(&rt->objs, ft_lstnew(obj, sizeof(*obj)));
	ft_memdel((void **)&obj);
	return (0);
}

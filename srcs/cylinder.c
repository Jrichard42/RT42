/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:29:48 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/10 15:48:09 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

#define	CYLINDER ((t_cylinder *)obj->data)

t_inter				inter_cylinder(t_obj *obj, t_ray *ray)
{

}

static t_vector3f	normal_cylinder(struct s_obj *obj, t_vector3f *coll)
{

}

void				create_cylinder(t_kvlexer *token, t_rt *rt)
{
	t_ob			*obj;

	if (!(obj = ft_memalloc(sizeof(*obj))))
		return (NULL);
	if (!(obj->data = ft_memalloc(sizeof(t_plane))))
		return (NULL);
	obj->normal = &normal_plane;
	obj->inter = &inter_plane;

	obj->pos = get_as_vector3f(token, "POSITION");
	obj->mat = get_material(token);
	obj->id = get_as_float(token, "ID");
	obj->is_src = get_as_float(token, "IS_SRC");
	obj->is_visible = get_as_float(token, "IS_VISIBLE");
	CYLINDER->radius = get_as_float(token, "RADIUS");
	ft_lstadd(&rt->objs, ft_lstnew(obj, sizeof(*obj)));
	ft_memdel((void **)&obj);
}

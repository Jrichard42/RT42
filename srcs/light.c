/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:29:48 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/10 15:52:12 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

#define	LIGHT ((t_light *)obj->data)

t_inter				inter_light(t_obj *obj, t_ray *ray)
{

}

static t_vector3f	normal_light(struct s_obj *obj, t_vector3f *coll)
{

}

void				create_light(t_kvlexer *token, t_rt *rt)
{
	t_ob			*obj;

	if (!(obj = ft_memalloc(sizeof(*obj))))
		return (NULL);
	if (!(obj->data = ft_memalloc(sizeof(t_plane))))
		return (NULL);
	obj->normal = &normal_light;
	obj->inter = &inter_light;

	obj->pos = get_as_vector3f(token, "POSITION");
	obj->mat = get_material(token);
	obj->id = get_as_float(token, "ID");
	obj->is_src = get_as_float(token, "IS_SRC");
	obj->is_visible = get_as_float(token, "IS_VISIBLE");
	ft_lstadd(&rt->objs, ft_lstnew(obj, sizeof(*obj)));
	ft_memdel((void **)&obj);
}

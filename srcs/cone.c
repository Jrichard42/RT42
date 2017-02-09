/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:29:48 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/09 19:00:17 by hpachy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"

#define	cone ((t_cone *)obj->data)

t_inter				inter_cone(t_obj *obj, t_ray *ray)
{

}

static t_vector3f	normal_cone(struct s_obj *obj, t_vector3f *coll)
{

}

t_obj				*create_cone(char **tmp)
{
	t_ob			*obj;

	if (!(obj = ft_memalloc(sizeof(*obj))))
		return (NULL);
	if (!(obj->data = ft_memalloc(sizeof(t_cone))))
		return (NULL);
	obj->normal = &normal_cone;
	obj->inter = &inter_cone;

	obj->pos = create_vector3f(ft_atoi(tmp[2]), ft_atoi(tmp[3]), ft_atoi(tmp[4]));
	obj->mat = 0; // TODO
	obj->id = ft_atoi(tmp[0]);
	obj->is_src = 0;
	obj->is_visible = 1;
	CONE->angle = (ft_atoi(tmp[8]) * M_PI) / 180;

	/*obj->mat.kd = ft_atoi(tmp[10]) / 100.0f;
	obj.mat.ks = ft_atoi(tmp[11]) / 100.0f;
	obj.mat.psh = ft_atoi(tmp[12]);*/
	
	return (obj);
}

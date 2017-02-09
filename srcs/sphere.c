/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:29:48 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/09 18:59:33 by hpachy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"

#define	SPHERE ((t_sphere *)obj->data)

t_inter				inter_sphere(t_obj *obj, t_ray *ray)
{

}

static t_vector3f	normal_sphere(struct s_obj *obj, t_vector3f *coll)
{

}

t_obj				*create_sphere(char **tmp)
{
	t_ob			*obj;

	if (!(obj = ft_memalloc(sizeof(*obj))))
		return (NULL);
	if (!(obj->data = ft_memalloc(sizeof(t_sphere))))
		return (NULL);
	obj->normal = &normal_sphere;
	obj->inter = &inter_sphere;

	obj->id = ft_atoi(tmp[0]);
	obj->mat = 0; //TODO
	obj->pos = create_vector3f(ft_atoi(tmp[2]), ft_atoi(tmp[3]), ft_atoi(tmp[4]));
	obj->id = ft_atoi(tmp[0]);
	obj->is_src = 0;
	obj->is_visible = 1;
	SPHERE->radius = ft_atoi(tmp[8]);
	/*obj->mat.kd = ft_atoi(tmp[10]) / 100.0f;
	obj.mat.ks = ft_atoi(tmp[11]) / 100.0f;
	obj.mat.psh = ft_atoi(tmp[12]);*/
	
	return (obj);
}

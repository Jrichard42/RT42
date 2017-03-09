/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 14:41:35 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/09 14:41:37 by abitoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "obj.h"
#include "inter.h"
#include "apply_color.h"

void			calcul_inter(t_cl *cl, t_ray *ray, t_obj *obj, t_inter *inter)
{
	float 			tmp;

	tmp = obj->inter(obj, ray);
	if (!isnan(tmp) && tmp > 0.01 && (tmp < inter->distance || isnan(inter->distance)))
	{
		inter->distance = tmp;
		// inter->impact = add_vector3f_cl(cl, ray->start, mult_vector3f(ray->dir, inter->distance));
		inter->impact = add_vector3f(ray->start, mult_vector3f(ray->dir, inter->distance));
		inter->normal = obj->normal(obj, &inter->impact);
		inter->obj = obj;
	}
}

t_vector3f		get_inters(t_rt *rt, t_ray *ray)
{
	t_list				*node;
	t_inter				inter;
	t_vector3f			color;

	inter.obj = NULL;
	inter.distance = NAN;
	color = create_vector3f(0, 0, 0);
	node = rt->objs->head;
	while (node)
	{
		if (((t_obj *)node->content)->is_src != 1)
			calcul_inter(rt->cl, ray, ((t_obj *)node->content), &inter);
		node = node->next;
	}
	apply_light(rt, ray, &color, &inter);
	return (color);
}
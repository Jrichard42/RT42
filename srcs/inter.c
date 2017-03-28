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

void				calcul_inter(t_ray *ray, t_obj *obj, t_inter *inter)
{
	float			tmp;

	tmp = obj->inter(obj, ray);
	if (!isnan(tmp) && tmp > 0.01 && (tmp < inter->distance
		|| isnan(inter->distance)) && tmp < DIST_MAX)
	{
		inter->distance = tmp;
		inter->impact = add_vector3f(ray->start,
			mult_vector3f(ray->dir, inter->distance));
		inter->normal = obj->normal(obj, &inter->impact);
		inter->obj = obj;
	}
}

t_inter				get_inters(t_list *list, t_ray *ray)
{
	t_list			*node;
	t_inter			inter;

	inter.obj = NULL;
	inter.distance = NAN;
	node = list;
	while (node)
	{
		if (((t_obj *)node->content)->is_src != 1 &&
			((t_obj *)node->content)->inter != NULL &&
			((t_obj *)node->content)->normal != NULL)
			calcul_inter(ray, ((t_obj *)node->content), &inter);
		node = node->next;
	}
	return (inter);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflexion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 15:27:16 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/20 15:27:18 by abitoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reflexion.h"
#include "refraction.h"
#include "light.h"
#include "plane.h"
#include "apply_color.h"

t_vector3f	apply_reflexion(t_obj *obj,
										t_ray ray,
										int rec_count,
										t_rt *rt)
{
	t_vector3f	color;
	t_ray		ray_obj;
	t_inter		inter;
	t_list		*list;

	color = create_vector3f(0, 0, 0);
	list = rt->objs->head;
	inter = get_inters(list, &ray);
	if (inter.obj != NULL)
	{
		ray_obj.start = inter.impact;
		ray_obj.dir = normalize_vector3f(sub_vector3f(obj->pos,
			inter.impact));
		if (is_shadow(obj, &inter, rt->objs->head, &ray_obj) != 1)
			color = obj->light.calc_light(obj, &ray, &inter);
		ray.start = inter.impact;
		ray.dir = sub_vector3f(ray.dir, mult_vector3f(inter.normal,
			2.0 * dot_vector3f(ray.dir, inter.normal)));
		ray.ir = inter.obj->mat.ir;
		color = div_vector3f(add_vector3f(color,
			apply_light(rt, &ray, rec_count - 1)), 2.0f);
	}
	return (clamp_vector3f(color, 0, 255));
}

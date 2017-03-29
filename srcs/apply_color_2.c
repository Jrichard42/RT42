/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_color_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 18:37:33 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/29 18:37:35 by abitoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "obj.h"
#include "inter.h"
#include "libft_matrix.h"
#include "apply_color.h"

t_vector3f	apply_color_2_annex(t_inter *inter,
								t_obj *obj,
								t_ray *ray,
								t_rt *rt)
{
	t_ray		ray_obj;
	t_vector3f	color;

	color = create_vector3f(0, 0, 0);
	ray_obj.start = inter->impact;
	ray_obj.dir = normalize_vector3f(sub_vector3f(obj->pos, inter->impact));
	if (is_shadow(obj, inter, rt->objs->head, &ray_obj) != 1)
		color = mult_vector3f(obj->light.calc_light(obj, ray, inter), 1);
	return (color);
}

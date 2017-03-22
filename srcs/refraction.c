/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 15:41:20 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/20 15:41:21 by abitoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reflexion.h"
#include "refraction.h"
#include "light.h"
#include "plane.h"
#include "apply_color.h"

static int			calcul_cos_refraction(t_inter *inter, double *cos1, double *cos2, t_ray inc_tmp) // pour refraction
{
	t_vector3f	inc;

	inc = mult_vector3f(inc_tmp.dir, -1.0);
	*cos1 = dot_vector3f(inc, inter->normal);
	if (inter->obj->mat.ir == 0)
		return (-1);
	*cos2 = 1 - pow(inc_tmp.ir / inter->obj->mat.ir, 2.0) *
		(1.0 - pow(*cos1, 2.0));
	if (*cos2 < 0)
		return (-1);
	*cos2 = sqrt(*cos2);
	return (1);
}

static	t_vector3f	vector_ref(t_inter *inter, t_ray inc_tmp) // refraction aussi
{
	t_vector3f	v_refraction;
	double		cos1;
	double		cos2;
	double		ir_tmp;

	if (calcul_cos_refraction(inter, &cos1, &cos2, inc_tmp) == -1)
	{
		v_refraction.x = NAN;
		return (v_refraction);
	}
	if (inc_tmp.ir == inter->obj->mat.ir)
		ir_tmp = 1.0;
	else
		ir_tmp = inter->obj->mat.ir;
	if (cos1 > 0)
		v_refraction =
		add_vector3f(mult_vector3f(inc_tmp.dir, inc_tmp.ir / ir_tmp),
		mult_vector3f(inter->normal, ((inc_tmp.ir / ir_tmp) * cos1) - cos2));
	else if (cos1 < 0)
		v_refraction =
		add_vector3f(mult_vector3f(inc_tmp.dir, inc_tmp.ir / ir_tmp),
		mult_vector3f(inter->normal, ((inc_tmp.ir / ir_tmp) * cos1) + cos2));
	else
		return (inc_tmp.dir);
	return (v_refraction);
}

t_vector3f			apply_refraction(t_obj *obj,
										t_ray ray,
										int rec_count,
										t_rt *rt)
{
	t_vector3f	color;
	int 		recursion;
	t_ray		ray_obj;
	t_inter 	inter;

	recursion = 0;
	color = create_vector3f(0,0,0);
	inter = get_inters(rt->objs->head, &ray);
	if (inter.obj != NULL)
	{
		ray_obj.start = inter.impact;
		ray_obj.dir = normalize_vector3f(sub_vector3f(obj->pos, inter.impact));
		if (is_shadow(obj, &inter, rt->objs->head, &ray_obj) != 1)
			if (!(isnan(ray.dir.x)))
			{
				color = obj->light.calc_light(obj, &ray, &inter);
				ray.dir = vector_ref(&inter, ray);
				ray.start = inter.impact;
				ray.ir = inter.obj->mat.ir;
				color = div_vector3f(add_vector3f(color, apply_light(rt, &ray, rec_count - 1)), 2.0f);
			}
	}
	return (clamp_vector3f(color, 0, 255));
}
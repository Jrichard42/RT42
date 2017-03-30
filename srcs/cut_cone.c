/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:13:31 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/03/30 14:13:34 by jqueyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cut.h"
#include <math.h>
#include "cone.h"
#include "obj.h"
#define CONE ((t_cone *)obj->data)

static float	cut_up(t_obj *obj, t_ray *ray, t_quadratic *var, t_ray *raytmp)
{
	t_vector3f	tmp;

	tmp = sub_vector3f(add_vector3f(obj->pos, mult_vector3f(CONE->dir,
		CONE->h)), raytmp->start);
	var->a = dot_vector3f(tmp, CONE->dir);
	var->a = var->a / dot_vector3f(raytmp->dir, CONE->dir);
	if (var->a < 0.f)
	{
		if (dot_vector3f(ray->dir, CONE->dir) != 0.0)
		{
			tmp = sub_vector3f(add_vector3f(obj->pos, mult_vector3f(CONE->dir,
				CONE->h)), ray->start);
			var->a = dot_vector3f(tmp, CONE->dir);
			var->a = var->a / dot_vector3f(ray->dir, CONE->dir);
			tmp = add_vector3f(ray->start, mult_vector3f(ray->dir, var->a));
			tmp = sub_vector3f(add_vector3f(obj->pos, mult_vector3f(CONE->dir,
				CONE->h)), tmp);
			if (sqrt(dot_vector3f(tmp, tmp)) > CONE->radius)
				return (NAN);
			var->result = var->a;
		}
		else
			return (NAN);
	}
	return (var->result);
}

float			cut_cone(t_obj *obj, t_ray *ray, t_quadratic *var)
{
	t_ray		raytmp;
	t_vector3f	tmp;

	if (CONE->h == 0)
		return (var->result);
	raytmp.start = add_vector3f(ray->start, mult_vector3f(ray->dir,
		var->result));
	raytmp.dir = CONE->dir;
	if (dot_vector3f(raytmp.dir, CONE->dir) != 0.0)
	{
		tmp = sub_vector3f(obj->pos, raytmp.start);
		var->a = dot_vector3f(tmp, CONE->dir);
		var->a = var->a / dot_vector3f(raytmp.dir, CONE->dir);
		if (var->a > 0.f)
			return (NAN);
		if (isnan(cut_up(obj, ray, var, &raytmp)))
			return (NAN);
	}
	return (var->result);
}

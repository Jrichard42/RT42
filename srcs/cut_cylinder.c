/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:02:45 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/03/30 14:02:48 by jqueyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cut.h"
#include <math.h>
#include "cylinder.h"
#include "obj.h"
#define CYLINDER ((t_cylinder *)obj->data)

static	float	cut_up(t_obj *obj, t_ray *ray, t_quadratic *var, t_ray *raytmp)
{
	t_vector3f	tmp;

	tmp = sub_vector3f(obj->pos, raytmp->start);
	var->a = dot_vector3f(tmp, CYLINDER->dir);
	var->a = var->a / dot_vector3f(raytmp->dir, CYLINDER->dir);
	if (var->a > 0.f)
	{
		if (dot_vector3f(ray->dir, CYLINDER->dir) != 0.0)
		{
			tmp = sub_vector3f(obj->pos, ray->start);
			var->a = dot_vector3f(tmp, CYLINDER->dir);
			var->a = var->a / dot_vector3f(ray->dir, CYLINDER->dir);
			var->result = var->a;
			tmp = add_vector3f(ray->start, mult_vector3f(ray->dir, var->a));
			tmp = sub_vector3f(obj->pos, tmp);
			if (sqrt(dot_vector3f(tmp, tmp)) > CYLINDER->radius)
				return (NAN);
		}
		else
			return (NAN);
	}
	return (var->result);
}

static	float	cut_down(t_obj *obj, t_ray *ray, t_quadratic *var,
	t_ray *raytmp)
{
	t_vector3f	tmp;

	tmp = sub_vector3f(add_vector3f(obj->pos,
		mult_vector3f(CYLINDER->dir, CYLINDER->h)), raytmp->start);
	var->a = dot_vector3f(tmp, CYLINDER->dir);
	var->a = var->a / dot_vector3f(raytmp->dir, CYLINDER->dir);
	if (var->a < 0.f)
	{
		if (dot_vector3f(ray->dir, CYLINDER->dir) != 0.0)
		{
			tmp = sub_vector3f(add_vector3f(obj->pos,
				mult_vector3f(CYLINDER->dir, CYLINDER->h)), ray->start);
			var->a = dot_vector3f(tmp, CYLINDER->dir);
			var->a = var->a / dot_vector3f(ray->dir, CYLINDER->dir);
			var->result = var->a;
			tmp = add_vector3f(ray->start, mult_vector3f(ray->dir, var->a));
			tmp = sub_vector3f(add_vector3f(obj->pos,
				mult_vector3f(CYLINDER->dir, CYLINDER->h)), tmp);
			if (sqrt(dot_vector3f(tmp, tmp)) > CYLINDER->radius)
				return (NAN);
		}
		else
			return (NAN);
	}
	return (var->result);
}

float			cut_cylinder(t_obj *obj, t_ray *ray, t_quadratic *var)
{
	t_ray	raytmp;

	raytmp.start = add_vector3f(ray->start,
		mult_vector3f(ray->dir, var->result));
	raytmp.dir = CYLINDER->dir;
	if (dot_vector3f(raytmp.dir, CYLINDER->dir) != 0.0)
	{
		if (isnan(cut_up(obj, ray, var, &raytmp)))
			return (NAN);
		if (isnan(cut_down(obj, ray, var, &raytmp)))
			return (NAN);
	}
	return (var->result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:29:41 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/03/30 14:29:43 by jqueyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"
#include "half_sphere.h"
#include "quadratic.h"
#include "parser.h"
#include "inter.h"
#include "libft.h"
#define SPHERE ((t_half_sphere *)obj->data)

static float	cut_disque(t_obj *obj, t_ray *ray, t_quadratic *var)
{
	t_vector3f tmp;

	if (dot_vector3f(ray->dir, SPHERE->dir) != 0.0)
	{
		tmp = sub_vector3f(obj->pos, ray->start);
		var->a = dot_vector3f(tmp, SPHERE->dir);
		var->a = var->a / dot_vector3f(ray->dir, SPHERE->dir);
		var->result = var->a;
		tmp = add_vector3f(ray->start, mult_vector3f(ray->dir, var->a));
		tmp = sub_vector3f(obj->pos, tmp);
		if (sqrt(dot_vector3f(tmp, tmp)) > SPHERE->radius)
			return (NAN);
	}
	else
		return (NAN);
	return (var->result);
}

float			cut_sphere(t_obj *obj, t_ray *ray, t_quadratic *var)
{
	t_ray		raytmp;
	t_vector3f	tmp;

	raytmp.dir = SPHERE->dir;
	if (dot_vector3f(raytmp.dir, raytmp.dir) != 0.0)
	{
		raytmp.start = add_vector3f(ray->start,
			mult_vector3f(ray->dir, var->result));
		tmp = sub_vector3f(obj->pos, raytmp.start);
		var->a = dot_vector3f(tmp, raytmp.dir);
		var->a = var->a / dot_vector3f(raytmp.dir, raytmp.dir);
		if (var->a > 0.0)
			var->result = cut_disque(obj, ray, var);
	}
	return (var->result);
}

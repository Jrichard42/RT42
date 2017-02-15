/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:29:48 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/10 17:08:55 by hpachy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"
#include <math.h>

#define	CONE ((t_cone *)obj->data)

static float			inter_cone(t_obj *obj, t_ray *ray)
{
	t_quadratic var;

	var.tmp = sub_vector3f(ray->start, obj->pos);
	var.a = dot_vector3f(ray->dir, ray->dir) - ((1.0 + CONE->angle * CONE->angle) * powf(dot_vector3f(ray->dir, CONE->dir), 2.0));
	var.b = 2.0 * (dot_vector3f(ray->dir, var.tmp) - ((1.0 + CONE->angle * CONE->angle) * (dot_vector3f(ray->dir, CONE->dir) * dot_vector3f(var.tmp, CONE->dir))));
	var.c = dot_vector3f(var.tmp, var.tmp) - ((1.0 + CONE->angle * CONE->angle) * powf(dot_vector3f(var.tmp, CONE->dir), 2.0) - powf(CONE->radius, 2.0));
	if (var.a < 0)
		return (nan);
	var.delta = powf(var.b, 2.0) - (4.0 * var.a * var.c);
	var.delta = sqrt(var.delta);
	var.a = 2.0 * var.a;
	var.sol_1 = (-var.b - var.delta) / var.a;
	var.sol_2 = (-var.b + var.delta) / var.a;
	if (var.sol_1 > sol_2)
		var.result = var.sol_2;
	else
		var.result = var.sol_1;
	return (var.result);
}

static t_vector3f	normal_cone(struct s_obj *obj, t_vector3f *impact)
{
	t_vector3f	tmp;

	tmp = sub_vector3f(*impact, obj->pos);
	tmp = mult_vector3f(CONE->dir, dot_vector3f(tmp, CONE->dir));
	tmp = add_vector3f(tmp, obj->pos);
	tmp = sub_vector3f(*impact, tmp);
	tmp = normalize_vector3f(tmp);

	return (tmp);
}

void				create_cone(t_kvlexer *token, t_rt *rt)
{
	t_ob			*obj;

	if (!(obj = ft_memalloc(sizeof(*obj))))
		return (NULL);
	if (!(obj->data = ft_memalloc(sizeof(t_cone))))
		return (NULL);
	obj->normal = &normal_cone;
	obj->inter = &inter_cone;

	obj->pos = get_as_vector3f(token, "POSITION");
	obj->mat = get_material(token);
	obj->id = get_as_float(token, "ID");
	obj->is_src = get_as_float(token, "IS_SRC");
	obj->is_visible = get_as_float(token, "IS_VISIBLE");
	CONE->angle = get_as_float(token, "ANGLE");
	CONE->angle = tan(CONE->angle * M_PI / 180.0);
	CONE->dir = get_as_vector3f(token, "DIR");
	CONE->dir = normalize_vector3f(PLANE->dir);
	ft_lstadd(&rt->objs, ft_lstnew(obj, sizeof(*obj)));
	ft_memdel((void **)&obj);	
}

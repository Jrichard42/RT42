/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:29:48 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/15 16:15:23 by abitoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

#define	CYLINDER ((t_cylinder *)obj->data)

static 	float		inter_cylinder(t_obj *obj, t_ray *ray)
{
	t_quadratic var;

	var.tmp = sub_vector3f(ray->start, obj->pos);
	var.a = dot_vector3f(ray->dir, ray->dir) - powf(dot_vector3f(ray->dir, CYLINDER->dir), 2.0);
	var.b = 2.0 * (dot_vector3f(ray->dir, var.tmp) - (dot_vector3f(ray->dir, CYLINDER->dir) * dot_vector3f(var.tmp, CYLINDER->dir)));
	var.c = dot_vector3f(var.tmp, var.tmp) - powf(dot_vector3f(var.tmp, CYLINDER->dir), 2.0) - powf(CYLINDER->radius, 2.0);
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

static t_vector3f	normal_cylinder(struct s_obj *obj, t_vector3f *impact)
{
	t_vector3f	tmp;

	tmp = sub_vector3f(*impact, obj->pos);
	tmp = mult_vector3f(CYLINDER->dir, dot_vector3f(tmp, CYLINDER->dir));
	tmp = add_vector3f(tmp, obj->pos);
	tmp = sub_vector3f(*impact, tmp);
	tmp = normalize_vector3f(tmp);

	return (tmp);
}

void				create_cylinder(t_kvlexer *token, t_rt *rt)
{
	t_ob			*obj;

	if (!(obj = ft_memalloc(sizeof(*obj))))
		return (NULL);
	if (!(obj->data = ft_memalloc(sizeof(t_cylinder))))
		return (NULL);
	obj->normal = &normal_cylinder;
	obj->inter = &inter_cylinder;

	obj->pos = get_as_vector3f(token, "POSITION");
	obj->mat = get_material(token);
	obj->id = get_as_float(token, "ID");
	obj->is_src = get_as_float(token, "IS_SRC");
	obj->is_visible = get_as_float(token, "IS_VISIBLE");
	CYLINDER->radius = get_as_float(token, "RADIUS");
	CYLINDER->dir = get_as_vector3f(token, "DIR");
	CYLINDER->dir = normalize_vector3f(PLANE->dir);
	ft_lstadd(&rt->objs, ft_lstnew(obj, sizeof(*obj)));
	ft_memdel((void **)&obj);
}

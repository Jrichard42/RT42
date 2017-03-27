/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:29:48 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/27 14:56:14 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"
#include "sphere.h"
#include "quadratic.h"
#include "parser.h"
#include "libft.h"

#define SPHERE ((t_sphere *)obj->data)

static float		inter_sphere(t_obj *obj, t_ray *ray)
{
	t_quadratic		var;
	t_vector3f		tmp;

	tmp = sub_vector3f(obj->pos, ray->start);
	var.a = dot_vector3f(tmp, ray->dir);
	var.b = var.a * var.a - dot_vector3f(tmp, tmp) + SPHERE->radius
	* SPHERE->radius;
	if (var.b < 0)
		return (NAN);
	var.sol_1 = var.a - sqrt(var.b);
	var.sol_2 = var.a + sqrt(var.b);
	if (var.sol_1 > var.sol_2)
		var.result = var.sol_2;
	else
		var.result = var.sol_1;
	return (var.result);
}

static t_vector3f	normal_sphere(struct s_obj *obj, t_vector3f *impact)
{
	return (normalize_vector3f(sub_vector3f(*impact, obj->pos)));
}

static int			create_sphere2(t_kvlexer *token, t_rt *rt, t_obj *obj)
{
	if (!get_material(token, rt, &(obj->mat)))
		return (0);
	if (!get_as_vector3f(token, "POS", &(obj->pos)))
		return ((int)ft_error("The SPHERE should contain a field POS"));
	if (!get_as_int(token, "ID", &(obj->id)))
		return ((int)ft_error("The SPHERE should contain a field ID"));
	if (!get_as_int(token, "IS_SRC", &(obj->is_src)))
		return ((int)ft_error("The SPHERE should contain a field IS_SRC"));
	if (obj->is_src)
		obj->light = get_light(token);
	if (!get_as_int(token, "IS_VISIBLE", &(obj->is_visible)))
		return ((int)ft_error("The SPHERE should contain a field IS_VISIBLE"));
	if (!get_as_float(token, "RADIUS", &(SPHERE->radius)))
		return ((int)ft_error("The SPHERE should contain a field RADIUS"));
	return (1);
}

int					create_sphere(t_kvlexer *token, t_rt *rt)
{
	t_obj			obj;

	if (!(obj.data = ft_memalloc(sizeof(t_sphere))))
		return (0);
	obj.normal = &normal_sphere;
	obj.inter = &inter_sphere;
	if (create_sphere2(token, rt, &obj))
		ft_lstadd(&rt->objs, ft_lstnew(&obj, sizeof(obj)));
	else
	{
		free(obj.data);
		return (0);
	}
	return (1);
}

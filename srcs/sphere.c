/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:29:48 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/19 18:02:22 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"
#include "sphere.h"
#include "quadratic.h"
#include "parser.h"
#include "libft.h"

#define	SPHERE ((t_sphere *)obj->data)

static float		inter_sphere(t_obj *obj, t_ray *ray)
{
	t_quadratic var;
	t_vector3f	tmp;

	tmp = sub_vector3f(obj->pos, ray->start);
	var.a = dot_vector3f(tmp, ray->dir);
	var.b = var.a * var.a - dot_vector3f(tmp, tmp) + SPHERE->radius * SPHERE->radius;
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

static void			base_sphere(t_obj *obj, t_kvlexer *token, t_rt *rt)
{
	obj->pos = create_vector3f(0, 0, 0);
	obj->id = 0;
	obj->is_src = 0;
	obj->is_visible = 1;
	obj->color = create_vector3f(255, 255, 255);
	SPHERE->radius = 10;
	obj->normal = &normal_sphere;
	obj->inter = &inter_sphere;
	obj->mat = get_material(token, rt);
}

int					create_sphere(t_kvlexer *token, t_rt *rt)
{
	t_obj			obj;
	t_sphere		*sphere;

	if (!(obj.data = ft_memalloc(sizeof(t_sphere))))
		return (0);
	sphere = ((t_sphere *)obj.data);
	base_sphere(&obj, token, rt);
	get_as_vector3f(token, "POS", &(obj.pos));
	get_as_int(token, "ID", &(obj.id));
	get_as_int(token, "IS_SRC", &(obj.is_src));
	if (obj.is_src)
		obj.light = get_light(token);
	get_as_int(token, "IS_VISIBLE", &(obj.is_visible));
	get_as_vector3f(token, "COLOR", &(obj.color));
	get_as_float(token, "RADIUS", &(sphere->radius));
	ft_lstadd(&rt->objs, ft_lstnew(&obj, sizeof(obj)));
	return (1);
}

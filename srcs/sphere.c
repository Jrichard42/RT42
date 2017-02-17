/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:29:48 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/17 20:17:51 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"
#include "sphere.h"
#include "quadratic.h"
#include "libft.h"

#define	SPHERE ((t_sphere *)obj->data)

static float		inter_sphere(t_obj *obj, t_ray *ray)
{
	t_quadratic var;

	var.tmp = obj->pos;
	sub_vector3f(ray->start, var.tmp);
	var.a = dot_vector3f(var.tmp, ray->dir);
	var.b = var.a * var.a - dot_vector3f(var.tmp, var.tmp) + SPHERE->radius * SPHERE->radius;
	if (var.b < 0)
		return (NAN);
	var.b = sqrt(var.b);
	var.sol_1 = var.a - var.b;
	var.sol_2 = var.a + var.b;
	if (var.sol_1 > var.sol_2)
		var.result = var.sol_2;
	else
		var.result = var.sol_1;
	return (var.result);
}

static t_vector3f	normal_sphere(struct s_obj *obj, t_vector3f *impact)
{
	t_vector3f tmp;

	tmp = sub_vector3f(*impact, obj->pos);
	tmp = normalize_vector3f(tmp);

	return (tmp);
}

int					create_sphere(t_kvlexer *token, t_rt *rt)
{
	t_obj			*obj;

	if (!(obj = ft_memalloc(sizeof(*obj))))
		return (-1);
	if (!(obj->data = ft_memalloc(sizeof(t_sphere))))
		return (-1);
	obj->normal = &normal_sphere;
	obj->inter = &inter_sphere;
	obj->pos = get_as_vector3f(token, "POSITION");
	obj->mat = get_material(token);
	obj->id = get_as_float(token, "ID");
	obj->is_src = get_as_float(token, "IS_SRC");
	obj->is_visible = get_as_float(token, "IS_VISIBLE");
	SPHERE->radius = get_as_float(token, "RADIUS");
	ft_lstadd(&rt->objs, ft_lstnew(obj, sizeof(*obj)));
	ft_memdel((void **)&obj);
	return (0);
}

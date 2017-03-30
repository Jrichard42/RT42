/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:29:48 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/30 16:02:02 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cylinder.h"
#include "obj.h"
#include "parser.h"
#include "libft.h"
#include "cut.h"
#define CYLINDER ((t_cylinder *)obj->data)

static	t_vector3f	cyl_tex(t_obj *self, t_inter inter)
{
	return (create_vector3f(0, 0, 0));
}

static float		inter_cylinder(t_obj *obj, t_ray *ray)
{
	t_quadratic		var;
	t_vector3f		tmp;

	tmp = sub_vector3f(ray->start, obj->pos);
	var.a = dot_vector3f(ray->dir, ray->dir) -
	powf(dot_vector3f(ray->dir, CYLINDER->dir), 2.0);
	var.b = 2.0 * (dot_vector3f(ray->dir, tmp) -
		(dot_vector3f(ray->dir, CYLINDER->dir) *
			dot_vector3f(tmp, CYLINDER->dir)));
	var.c = dot_vector3f(tmp, tmp) - powf(dot_vector3f(tmp, CYLINDER->dir),
		2.0) - powf(CYLINDER->radius, 2.0);
	if (var.a < 0)
		return (NAN);
	var.delta = powf(var.b, 2.0) - (4.0 * var.a * var.c);
	var.delta = sqrt(var.delta);
	var.a = 2.0 * var.a;
	var.sol_1 = (-var.b - var.delta) / var.a;
	var.sol_2 = (-var.b + var.delta) / var.a;
	if (var.sol_1 > var.sol_2)
		var.result = var.sol_2;
	else
		var.result = var.sol_1;
	if (CYLINDER->h != 0)
		var.result = cut_cylinder(obj, ray, &var);
	return (var.result);
}

static t_vector3f	normal_cylinder(struct s_obj *obj, t_vector3f *impact)
{
	t_vector3f		tmp;
	float			d;

	if (CYLINDER->h)
	{
		d = dot_vector3f(CYLINDER->dir, obj->pos);
		if (((dot_vector3f(*impact, CYLINDER->dir) - d) < 0.0005f)
				&& ((dot_vector3f(*impact, CYLINDER->dir) - d) > -0.0005f))
			return (mult_vector3f(CYLINDER->dir, -1));
		d = dot_vector3f(CYLINDER->dir, add_vector3f(obj->pos,
			mult_vector3f(CYLINDER->dir, CYLINDER->h)));
		if (((dot_vector3f(*impact, CYLINDER->dir) - d) < 0.0005f)
				&& ((dot_vector3f(*impact, CYLINDER->dir) - d) > -0.0005f))
			return (CYLINDER->dir);
	}
	tmp = sub_vector3f(*impact, obj->pos);
	tmp = mult_vector3f(CYLINDER->dir, dot_vector3f(tmp, CYLINDER->dir));
	tmp = add_vector3f(tmp, obj->pos);
	tmp = sub_vector3f(*impact, tmp);
	tmp = normalize_vector3f(tmp);
	return (tmp);
}

static int			create_cylinder2(t_kvlexer *token, t_rt *rt, t_obj *obj)
{
	if (!get_material(token, rt, &(obj->mat)))
		return (0);
	if (!get_texture(token, rt, &(obj->tex)))
	{
		obj->tex.data = NULL;
		obj->texture = NULL;
	}
	if (!get_as_vector3f(token, "POS", &(obj->pos)))
		return ((int)ft_error("The CYLINDER should contain a field POS"));
	if (!get_as_int(token, "ID", &(obj->id)))
		return ((int)ft_error("The CYLINDER should contain a field ID"));
	if (!get_as_int(token, "IS_SRC", &(obj->is_src)))
		return ((int)ft_error("The CYLINDER should contain a field IS_SRC"));
	if (obj->is_src)
		obj->light = get_light(token);
	if (!get_as_int(token, "IS_VISIBLE", &(obj->is_visible)))
		return ((int)ft_error("The CYLINDER should contain"
		" a field IS_VISIBLE"));
	if (!get_as_float(token, "RADIUS", &(CYLINDER->radius)))
		return ((int)ft_error("The CYLINDER should contain a field RADIUS"));
	if (!get_as_vector3f(token, "DIR", &(CYLINDER->dir)))
		return ((int)ft_error("The CYLINDER should contain a field DIR"));
	if (!get_as_float(token, "HAUTEUR", &(CYLINDER->h)))
		CYLINDER->h = 0;
	CYLINDER->dir = normalize_vector3f(CYLINDER->dir);
	return (1);
}

int					create_cylinder(t_kvlexer *token, t_rt *rt)
{
	t_obj			obj;

	if (!(obj.data = ft_memalloc(sizeof(t_cylinder))))
		return (0);
	obj.normal = &normal_cylinder;
	obj.inter = &inter_cylinder;
	obj.texture = NULL;
	obj.destroy = NULL;
	if (create_cylinder2(token, rt, &obj))
		ft_lstadd(&rt->objs, ft_lstnew(&obj, sizeof(obj)));
	else
	{
		free(obj.data);
		return (0);
	}
	return (1);
}

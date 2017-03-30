/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloide.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 17:19:58 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/30 19:09:20 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paraboloide.h"
#include "quadratic.h"

#define PARABOLOIDE ((t_paraboloide *)obj->data)

static float		inter_paraboloide(t_obj *obj, t_ray *ray)
{
	t_vector3f		tmp_x;
	t_quadratic		var;

	tmp_x = sub_vector3f(ray->start, obj->pos);
	PARABOLOIDE->dir = normalize_vector3f(PARABOLOIDE->dir);
	var.a = dot_vector3f(ray->dir, ray->dir) -
		powf(dot_vector3f(ray->dir, PARABOLOIDE->dir), 2.0);
	var.b = (dot_vector3f(ray->dir, tmp_x) - dot_vector3f(ray->dir,
		mult_vector3f(PARABOLOIDE->dir,
		dot_vector3f(tmp_x, PARABOLOIDE->dir) + 2.0 * PARABOLOIDE->curve))) * 2;
	var.c = dot_vector3f(tmp_x, tmp_x) - dot_vector3f(tmp_x,
		mult_vector3f(PARABOLOIDE->dir,
		dot_vector3f(tmp_x, PARABOLOIDE->dir) + 4.0 * PARABOLOIDE->curve));
	if (var.a <= 0)
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
	return (var.result);
}

static t_vector3f	normal_paraboloide(struct s_obj *obj, t_vector3f *impact)
{
	t_vector3f		normal;

	normal = normalize_vector3f(sub_vector3f(
		sub_vector3f(*impact, obj->pos),
		mult_vector3f(PARABOLOIDE->dir, dot_vector3f(
		sub_vector3f(*impact, obj->pos),
			PARABOLOIDE->dir) + PARABOLOIDE->curve)));
	return (normal);
}

static int			create_paraboloide2(t_kvlexer *token, t_rt *rt, t_obj *obj)
{
	if (!get_material(token, rt, &(obj->mat)))
		return (0);
	if (!get_texture(token, rt, &(obj->tex)))
		obj->texture = NULL;
	if (!get_as_vector3f(token, "POS", &(obj->pos)))
		return ((int)ft_error("The PARABOLOIDE should contain a field POS"));
	if (!get_as_int(token, "ID", &(obj->id)))
		return ((int)ft_error("The PARABOLOIDE should contain a field ID"));
	if (!get_as_int(token, "IS_SRC", &(obj->is_src)))
		return ((int)ft_error("The PARABOLOIDE should contain a field IS_SRC"));
	if (obj->is_src)
		obj->light = get_light(token);
	if (!get_as_int(token, "IS_VISIBLE", &(obj->is_visible)))
		return ((int)ft_error("The PARA should contain a field IS_VISIBLE"));
	if (!get_as_vector3f(token, "DIR", &(PARABOLOIDE->dir)))
		return ((int)ft_error("The PARABOLOIDE should contain a field DIR"));
	if (!get_as_float(token, "CURVE", &(PARABOLOIDE->curve)))
		return ((int)ft_error("The PARABOLOIDE should contain a field CURVE"));
	return (1);
}

int					create_paraboloide(t_kvlexer *token, t_rt *rt)
{
	t_obj			obj;

	if (!(obj.data = ft_memalloc(sizeof(t_paraboloide))))
		return (0);
	obj.normal = &normal_paraboloide;
	obj.inter = &inter_paraboloide;
	obj.texture = NULL;
	obj.destroy = NULL;
	obj.tex = NULL;
	if (create_paraboloide2(token, rt, &obj))
		ft_lstadd(&rt->objs, ft_lstnew(&obj, sizeof(obj)));
	else
	{
		free(obj.data);
		return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 13:35:40 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/03/19 18:03:56 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "torus.h"
#define TORUS ((t_torus *)obj->data)

static float			resolution(double *eq)
{
	double	inter;
	t_res	res;

	res = equationpoly4(eq);
	inter = NAN;
	if (!isnan(res.x1))
		inter = res.x1;
	if (((!isnan(res.x2) && res.x2 < inter) || (!isnan(res.x2) &&
					isnan(inter))))
		inter = res.x2;
	if (((!isnan(res.x3) && res.x3 < inter) || (!isnan(res.x3) &&
					isnan(inter))))
		inter = res.x3;
	if (((!isnan(res.x4) && res.x4 < inter) || (!isnan(res.x4) &&
					isnan(inter))))
		inter = res.x4;
	if (inter < 0)
		inter = NAN;
	free(eq);
	return (inter);
}

static double			*calc_eq(t_var_torus var, float center_to_ray_dot_dir)
{
	double *eq;

	if (!(eq = (double*)ft_memalloc(5 * sizeof(double))))
		return (NULL);
	eq[0] = 1.0f;
	eq[1] = 4.0f * center_to_ray_dot_dir;
	eq[2] = (2.0f * var.d) + ((eq[1] * eq[1]) * 0.25f) - ((4.0f *
				var.outer_rad_sq) * var.a);
	eq[3] = (eq[1] * var.d) - ((4.0f * var.outer_rad_sq) * var.b);
	eq[4] = (var.d * var.d) - ((4.0f * var.outer_rad_sq) * var.c);
	return (eq);
}

static float			inter_torus(t_obj *obj, t_ray *ray)
{
	t_vector3f	center_to_raystart;
	float		center_to_ray_dot_dir;
	t_var_torus	var;

	center_to_raystart = sub_vector3f(ray->start, obj->pos);
	center_to_ray_dot_dir = dot_vector3f(ray->dir, center_to_raystart);
	var.center_to_ray_start_dot_dir_sqrt = dot_vector3f(center_to_raystart,
			center_to_raystart);
	var.inner_rad_sq = TORUS->inner_rad * TORUS->inner_rad;
	var.outer_rad_sq = TORUS->outer_rad * TORUS->outer_rad;
	var.axis_dot_centertoray = dot_vector3f(TORUS->axis, center_to_raystart);
	var.axis_dot_raydir = dot_vector3f(TORUS->axis, ray->dir);
	var.a = 1.0f - var.axis_dot_raydir * var.axis_dot_raydir;
	var.b = 2.0f * (dot_vector3f(center_to_raystart, ray->dir) -
			(var.axis_dot_centertoray * var.axis_dot_raydir));
	var.c = var.center_to_ray_start_dot_dir_sqrt -
		var.axis_dot_centertoray * var.axis_dot_centertoray;
	var.d = var.center_to_ray_start_dot_dir_sqrt +
		var.outer_rad_sq - var.inner_rad_sq;
	return (resolution(calc_eq(var, center_to_ray_dot_dir)));
}

static t_vector3f		normal_torus(struct s_obj *obj, t_vector3f *impact)
{
	t_vector3f	center_to_point;
	float		center_to_point_dot_axis;
	t_vector3f	direction;
	t_vector3f	normal;

	center_to_point = normalize_vector3f(sub_vector3f(*impact, obj->pos));
	center_to_point_dot_axis = dot_vector3f(center_to_point, TORUS->axis);
	direction = sub_vector3f(center_to_point, mult_vector3f(TORUS->axis,
				center_to_point_dot_axis));
	direction = normalize_vector3f(direction);
	normal = sub_vector3f(*impact, add_vector3f(obj->pos,
				mult_vector3f(direction, TORUS->outer_rad)));
	normal = normalize_vector3f(normal);
	return (normal);
}

static void			base_torus(t_obj *obj, t_kvlexer *token, t_rt *rt)
{
	obj->pos = create_vector3f(0, 0, 0);
	obj->id = 0;
	obj->is_src = 0;
	obj->is_visible = 1;
	obj->color = create_vector3f(1, 1, 1);
	TORUS->inner_rad = 10;
	TORUS->outer_rad = 10;
	TORUS->axis = create_vector3f(0, 0, 1);
	obj->normal = &normal_torus;
	obj->inter = &inter_torus;
	obj->mat = get_material(token, rt);
}

int						create_torus(t_kvlexer *token, t_rt *rt)
{
	t_obj				obj;
	t_torus				*torus;

	if (!(obj.data = ft_memalloc(sizeof(t_torus))))
		return (0);
	torus = ((t_torus *)obj.data);
	base_torus(&obj, token, rt);
	get_as_vector3f(token, "POS", &(obj.pos));
	get_as_int(token, "ID", &(obj.id));
	get_as_int(token, "IS_SRC", &(obj.is_src));
	if (obj.is_src)
		obj.light = get_light(token);
	get_as_int(token, "IS_VISIBLE", &(obj.is_visible));
	get_as_vector3f(token, "COLOR", &(obj.color));
	get_as_float(token, "OUTERRADIUS", &(torus->outer_rad));
	get_as_float(token, "INNERRADIUS", &(torus->inner_rad));
	get_as_vector3f(token, "AXIS", &(torus->axis));
	torus->axis = normalize_vector3f(torus->axis);
	ft_lstadd(&rt->objs, ft_lstnew(&obj, sizeof(obj)));
	return (1);
}

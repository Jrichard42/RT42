/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 13:35:51 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/03/19 18:04:19 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "box.h"
#define BOX ((t_box *)obj->data)
#define MAX_DISTANCE_TO_INTERSECTON 1000000
#define EPS_FOR_NORMAL_DIRECTION 0.005f

static void				ft_swap(float *a, float *b)
{
	float tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static float			calc_dist(t_ray *ray, t_vector3f tmin, t_vector3f tmax)
{
	if (fabs(ray->dir.x) > 0.000001f)
		if (tmin.x > tmax.x)
			ft_swap(&tmin.x, &tmax.x);
	if (fabs(ray->dir.y) > 0.000001f)
	{
		if (tmin.y > tmax.y)
			ft_swap(&tmin.y, &tmax.y);
		if (tmin.y > tmin.x)
			tmin.x = tmin.y;
		if (tmax.y < tmax.x)
			tmax.x = tmax.y;
	}
	if (fabs(ray->dir.z) > 0.000001f)
	{
		if (tmin.z > tmax.z)
			ft_swap(&tmin.z, &tmax.z);
		if (tmin.z > tmin.x)
			tmin.x = tmin.z;
		if (tmax.z < tmax.x)
			tmax.x = tmax.z;
	}
	if (!(tmin.x > 0.000001f && tmax.x > tmin.x))
		return (NAN);
	return (tmin.x);
}

static float			inter_box(t_obj *obj, t_ray *ray)
{
	t_vector3f tmin;
	t_vector3f tmax;
	t_vector3f inv_dir;

	inv_dir = div_float_by_vector3f(1.f, ray->dir);
	tmin = mult_by_vector3f(sub_vector3f(BOX->min, ray->start), inv_dir);
	tmax = mult_by_vector3f(sub_vector3f(BOX->max, ray->start), inv_dir);
	if (fabs(ray->dir.x) < 0.000001f)
		if (ray->start.x < BOX->min.x || ray->start.x > BOX->max.x)
			return (NAN);
	if (fabs(ray->dir.y) < 0.000001f)
		if (ray->start.y < BOX->min.y || ray->start.y > BOX->max.y)
			return (NAN);
	if (fabs(ray->dir.z) < 0.000001f)
		if (ray->start.z < BOX->min.z || ray->start.z > BOX->max.z)
			return (NAN);
	return (calc_dist(ray, tmin, tmax));
}

static t_vector3f		normal_box(struct s_obj *obj, t_vector3f *impact)
{
	t_vector3f pointtomin;
	t_vector3f pointtomax;

	pointtomin = normalize_vector3f(sub_vector3f(*impact, BOX->min));
	pointtomax = normalize_vector3f(sub_vector3f(*impact, BOX->max));
	if (fabs(pointtomin.x) < EPS_FOR_NORMAL_DIRECTION)
		return (create_vector3f(sgn(pointtomax.x), 0.0, 0.0));
	if (fabs(pointtomax.x) < EPS_FOR_NORMAL_DIRECTION)
		return (create_vector3f(sgn(pointtomin.x), 0.0, 0.0));
	if (fabs(pointtomin.y) < EPS_FOR_NORMAL_DIRECTION)
		return (create_vector3f(0.0, sgn(pointtomax.y), 0.0));
	if (fabs(pointtomax.y) < EPS_FOR_NORMAL_DIRECTION)
		return (create_vector3f(0.0, sgn(pointtomin.y), 0.0));
	if (fabs(pointtomin.z) < EPS_FOR_NORMAL_DIRECTION)
		return (create_vector3f(0.0, 0.0, sgn(pointtomax.z)));
	if (fabs(pointtomax.z) < EPS_FOR_NORMAL_DIRECTION)
		return (create_vector3f(0.0, 0.0, sgn(pointtomin.z)));
	return (create_vector3f(0.0, 0.0, 0.0));
}

static void			base_box(t_obj *obj, t_kvlexer *token, t_rt *rt)
{
	obj->pos = create_vector3f(0, 0, 0);
	obj->id = 0;
	obj->is_src = 0;
	obj->is_visible = 1;
	obj->color = create_vector3f(1, 1, 1);
	BOX->min = create_vector3f(0, 0, 1);
	BOX->max = create_vector3f(0, 1, 0);
	obj->normal = &normal_box;
	obj->inter = &inter_box;
	obj->mat = get_material(token, rt);
}

int						create_box(t_kvlexer *token, t_rt *rt)
{
	t_obj			obj;
	t_box			*box;

	if (!(obj.data = ft_memalloc(sizeof(t_box))))
		return (0);
	box = ((t_box *)obj.data);
	base_box(&obj, token, rt);
	get_as_vector3f(token, "POS", &(obj.pos));
	get_as_int(token, "ID", &(obj.id));
	get_as_int(token, "IS_SRC", &(obj.is_src));
	if (obj.is_src)
			obj.light = get_light(token);
	get_as_int(token, "IS_VISIBLE", &(obj.is_visible));
	get_as_vector3f(token, "COLOR", &(obj.color));	
	box->min = obj.pos;
	get_as_vector3f(token, "MAX", &(box->max));
	ft_lstadd(&rt->objs, ft_lstnew(&obj, sizeof(obj)));
	return (1);
}

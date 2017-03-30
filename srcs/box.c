/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueyrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 13:35:51 by jqueyrou          #+#    #+#             */
/*   Updated: 2017/03/30 18:52:19 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "box.h"
#include "libft.h"
#define BOX ((t_box *)obj->data)
#define MAX_DISTANCE_TO_INTERSECTON 1000000
#define EPS_FOR_NORMAL_DIRECTION 0.005f

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

static int				create_box2(t_kvlexer *token, t_rt *rt, t_obj *obj)
{
	t_vector3f		dimension;

	if (!get_material(token, rt, &(obj->mat)))
		return (0);
	if (!get_texture(token, rt, &(obj->tex)))
		obj->texture = NULL;
	if (!get_as_vector3f(token, "POS", &(obj->pos)))
		return ((int)ft_error("The BOX should contain a field POS"));
	if (!get_as_int(token, "ID", &(obj->id)))
		return ((int)ft_error("The BOX should contain a field ID"));
	if (!get_as_int(token, "IS_SRC", &(obj->is_src)))
		return ((int)ft_error("The BOX should contain a field IS_SRC"));
	if (obj->is_src)
		obj->light = get_light(token);
	if (!get_as_int(token, "IS_VISIBLE", &(obj->is_visible)))
		return ((int)ft_error("The BOX should contain a field IS_VISIBLE"));
	if (!get_as_vector3f(token, "DIMENSION", &dimension))
		return ((int)ft_error("The BOX should contain a field DIMENSION"));
	BOX->min = obj->pos;
	BOX->max = add_vector3f(obj->pos, dimension);
	return (1);
}

int						create_box(t_kvlexer *token, t_rt *rt)
{
	t_obj			obj;

	if (!(obj.data = ft_memalloc(sizeof(t_box))))
		return (0);
	obj.normal = &normal_box;
	obj.inter = &inter_box;
	obj.texture = NULL;
	obj.destroy = NULL;
	obj.tex = NULL;
	if (create_box2(token, rt, &obj))
		ft_lstadd(&rt->objs, ft_lstnew(&obj, sizeof(obj)));
	else
	{
		free(obj.data);
		return (0);
	}
	return (1);
}

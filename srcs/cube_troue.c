/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_troue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abitoun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:14:50 by abitoun           #+#    #+#             */
/*   Updated: 2017/03/30 20:11:26 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"
#include "sphere.h"
#include "quadratic.h"
#include "parser.h"
#include "inter.h"
#include "libft.h"
#include "cube_troue.h"
#include "equation.h"

#define CUBE_TROUE ((t_cube_troue *)obj->data)

static	float		resolution(double *eq)
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
	return (inter);
}

static float		inter_cube_troue(t_obj *obj, t_ray *ray)
{
	double	p[5];
	double	pos[3];
	double	solution;

	pos[0] = ray->start.x - obj->pos.x;
	pos[1] = ray->start.y - obj->pos.y;
	pos[2] = ray->start.z - obj->pos.z;
	p[0] = pow(ray->dir.x, 4) + pow(ray->dir.y, 4) + pow(ray->dir.z, 4);
	p[1] = 4 * (pow(ray->dir.x, 3) * pos[0] + pow(ray->dir.y, 3) * pos[1]
		+ pow(ray->dir.z, 3) * pos[2]);
	p[2] = 6 * (pow(ray->dir.x, 2) * pow(pos[0], 2) + pow(ray->dir.y, 2)
		* pow(pos[1], 2) + pow(ray->dir.z, 2) * pow(pos[2], 2)) - 5
	* (pow(ray->dir.x, 2) + pow(ray->dir.y, 2) + pow(ray->dir.z, 2));
	p[3] = 4 * (pow(pos[0], 3) * ray->dir.x + pow(pos[1], 3) * ray->dir.y
		+ pow(pos[2], 3) * ray->dir.z) - 10 * (ray->dir.x * pos[0]
		+ ray->dir.y * pos[1] + ray->dir.z * pos[2]);
	p[4] = pow(pos[0], 4) + pow(pos[1], 4) + pow(pos[2], 4) - 5 *
	(pow(pos[0], 2) + pow(pos[1], 2) + pow(pos[2], 2)) + CUBE_TROUE->circle;
	solution = resolution(p);
	return (solution);
}

static t_vector3f	normal_cube_troue(struct s_obj *obj, t_vector3f *impact)
{
	t_vector3f normal;

	normal.x = impact->x - obj->pos.x;
	normal.y = impact->y - obj->pos.y;
	normal.z = impact->z - obj->pos.z;
	normal.x = 4 * pow(normal.x, 3) - 10 * normal.x;
	normal.y = 4 * pow(normal.y, 3) - 10 * normal.y;
	normal.z = 4 * pow(normal.z, 3) - 10 * normal.z;
	normal = normalize_vector3f(normal);
	return (normal);
}

static int			create_cube_troue2(t_kvlexer *token, t_rt *rt, t_obj *obj)
{
	if (!get_material(token, rt, &(obj->mat)))
		return (0);
	if (!get_texture(token, rt, &(obj->tex)))
		obj->texture = NULL;
	if (!get_as_vector3f(token, "POS", &(obj->pos)))
		return ((int)ft_error("The CUBE_T should contain a field POS"));
	if (!get_as_int(token, "ID", &(obj->id)))
		return ((int)ft_error("The CUBE_T should contain a field ID"));
	if (!get_as_int(token, "IS_SRC", &(obj->is_src)))
		return ((int)ft_error("The CUBE_T should contain a field IS_SRC"));
	if (obj->is_src)
		obj->light = get_light(token);
	if (!get_as_float(token, "CIRCLE", &(CUBE_TROUE->circle)))
		return ((int)ft_error("The CUBE_T should contain a field CIRCLE"));
	if (!get_as_int(token, "IS_VISIBLE", &(obj->is_visible)))
		return ((int)ft_error("The CUBE_T should contain a field RADIUS"));
	return (1);
}

int					create_cube_troue(t_kvlexer *token, t_rt *rt)
{
	t_obj			obj;

	if (!(obj.data = ft_memalloc(sizeof(t_cube_troue))))
		return (0);
	obj.normal = &normal_cube_troue;
	obj.inter = &inter_cube_troue;
	obj.destroy = NULL;
	if (create_cube_troue2(token, rt, &obj))
		ft_lstadd(&rt->objs, ft_lstnew(&obj, sizeof(obj)));
	else
	{
		free(obj.data);
		return (0);
	}
	return (1);
}

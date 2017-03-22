/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:29:48 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/25 14:52:00 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"
#include "cone.h"
#include "parser.h"
#include "utils.h"
#include "libft_matrix.h"

#define	CONE ((t_cone *)obj->data)

static	t_vector3f	cone_tex(t_obj *self, t_inter inter)
{
	t_vector3f		color;

	return (color);
}

static float			inter_cone(t_obj *obj, t_ray *ray)
{
	t_quadratic var;
	t_vector3f	tmp;

	tmp = sub_vector3f(ray->start, obj->pos);
	var.a = dot_vector3f(ray->dir, ray->dir) - ((1.0 + tan(CONE->angle) * tan(CONE->angle)) * powf(dot_vector3f(ray->dir, CONE->dir), 2.0));
	var.b = 2.0 * (dot_vector3f(ray->dir, tmp) - ((1.0 + tan(CONE->angle) * tan(CONE->angle)) * (dot_vector3f(ray->dir, CONE->dir) * dot_vector3f(tmp, CONE->dir))));
	var.c = dot_vector3f(tmp, tmp) - ((1.0 + tan(CONE->angle) * tan(CONE->angle)) * powf(dot_vector3f(tmp, CONE->dir), 2.0) - powf(CONE->angle, 2.0));
	var.delta = powf(var.b, 2.0) - (4.0 * var.a * var.c);
	if (var.delta < 0)
		return (NAN);
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

static char			validate_direction(t_obj *obj, t_vector3f *io,
		t_vector3f *norm, t_vector3f *piv)
{
	float			est_tan;
	float			exp_tan;

	est_tan = norm->length / io->length;
	exp_tan = tan(CONE->angle);
	if (!almost_equal_relative(est_tan, exp_tan))
	{

		*piv = mult_vector3f(CONE->dir,
				-1.0f * length_vector3f(*io) / cos(CONE->angle));
		*piv = add_vector3f(*piv, obj->pos);
		return (0);
	}
	return (1);
}

static t_vector3f	normal_cone(t_obj *obj, t_vector3f *impact)
{
	t_vector3f		io;
	t_vector3f		piv;
	double			pi;
	t_vector3f		norm;

	io = sub_vector3f(*impact, obj->pos);
	pi = length_vector3f(io) / cos(CONE->angle);
	piv = mult_vector3f(CONE->dir, pi);
	piv = add_vector3f(piv, obj->pos);
	norm = sub_vector3f(*impact, piv);
	io.length = length_vector3f(io);
	norm.length = length_vector3f(norm);
	if (!validate_direction(obj, &io, &norm, &piv))
		norm = sub_vector3f(*impact, piv);
	return (normalize_vector3f(norm));
}

int					create_cone(t_kvlexer *token, t_rt *rt)
{
	t_obj			*obj;

	if (!(obj = ft_memalloc(sizeof(*obj))))
		return (0);
	if (!(obj->data = ft_memalloc(sizeof(t_cone))))
		return (0);
	obj->normal = &normal_cone;
	obj->inter = &inter_cone;
	obj->texture = &cone_tex;
	obj->pos = get_as_vector3f(token, "POS");
	obj->mat = get_material(token);
	obj->id = get_as_float(token, "ID");
	obj->is_src = get_as_float(token, "IS_SRC");
	obj->is_visible = get_as_float(token, "IS_VISIBLE");
	CONE->angle = get_as_float(token, "ANGLE");
	CONE->angle = CONE->angle * M_PI / 180.0;
	CONE->dir = get_as_vector3f(token, "DIR");
	obj->color = get_as_vector3f(token, "COLOR");
	CONE->dir = normalize_vector3f(CONE->dir);
	obj->dir = CONE->dir;
	ft_lstadd(&rt->objs, ft_lstnew(obj, sizeof(*obj)));
	ft_memdel((void **)&obj);
	return (1);
}

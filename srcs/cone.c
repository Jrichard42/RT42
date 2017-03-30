/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:29:48 by hpachy            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2017/03/30 18:54:24 by jrichard         ###   ########.fr       */
=======
/*   Updated: 2017/03/30 17:46:47 by jrichard         ###   ########.fr       */
>>>>>>> 506c03b7047b32355bce118244c4f099c0e18cbd
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"
#include "cone.h"
#include "parser.h"
#include "utils.h"
#include "libft_matrix.h"
#include "cut.h"
#define CONE ((t_cone *)obj->data)

static	t_vector3f		cone_tex(t_obj *self, t_inter inter)
{
	t_vector3f		color;

	color = create_vector3f(0, 0, 0);
	return (color);
}

static float			inter_cone(t_obj *obj, t_ray *ray)
{
	t_quadratic			var;
	t_vector3f			tmp;

	tmp = sub_vector3f(ray->start, obj->pos);
	var.a = dot_vector3f(ray->dir, ray->dir) - ((1.0 + tan(CONE->angle)
		* tan(CONE->angle)) * powf(dot_vector3f(ray->dir, CONE->dir), 2.0));
	var.b = 2.0 * (dot_vector3f(ray->dir, tmp) - ((1.0 + tan(CONE->angle)
		* tan(CONE->angle)) * (dot_vector3f(ray->dir, CONE->dir)
		* dot_vector3f(tmp, CONE->dir))));
	var.c = dot_vector3f(tmp, tmp) - ((1.0 + tan(CONE->angle)
		* tan(CONE->angle)) * powf(dot_vector3f(tmp, CONE->dir),
		2.0) - powf(CONE->angle, 2.0));
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
	return (cut_cone(obj, ray, &var));
}

static char				validate_direction(t_obj *obj, t_vector3f *io,
		t_vector3f *norm, t_vector3f *piv)
{
	float				est_tan;
	float				exp_tan;

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

static t_vector3f		normal_cone(t_obj *obj, t_vector3f *impact)
{
	t_vector3f			io;
	t_vector3f			piv;
	double				pi;
	t_vector3f			norm;
	float				d;

	d = dot_vector3f(CONE->dir, add_vector3f(obj->pos,
		mult_vector3f(CONE->dir, CONE->h)));
	if (((dot_vector3f(*impact, CONE->dir) - d) < 0.0005f)
			&& ((dot_vector3f(*impact, CONE->dir) - d) > -0.0005f))
		return (CONE->dir);
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

static int				create_cone2(t_kvlexer *token, t_rt *rt, t_obj *obj)
{
	if (!get_material(token, rt, &(obj->mat)))
		return (0);
	if (!get_texture(token, rt, &(obj->tex)))
	{
		obj->tex.data = NULL;
		obj->texture = NULL;
	}
	if (!get_as_vector3f(token, "POS", &(obj->pos)))
		return ((int)ft_error("The CONE should contain a field POS"));
	if (!get_as_int(token, "ID", &(obj->id)))
		return ((int)ft_error("The CONE should contain a field ID"));
	if (!get_as_int(token, "IS_SRC", &(obj->is_src)))
		return ((int)ft_error("The CONE should contain a field IS_SRC"));
	if (obj->is_src)
		obj->light = get_light(token);
	if (!get_as_int(token, "IS_VISIBLE", &(obj->is_visible)))
		return ((int)ft_error("The CONE should contain a field IS_VISIBLE"));
	if (!get_as_float(token, "ANGLE", &(CONE->angle)))
		return ((int)ft_error("The CONE should contain a field ANGLE"));
	CONE->angle *= M_PI / 180.0;
	if (!get_as_vector3f(token, "DIR", &(CONE->dir)))
		return ((int)ft_error("The CONE should contain a field DIR"));
	CONE->dir = normalize_vector3f(CONE->dir);
	if (!get_as_float(token, "HAUTEUR", &(CONE->h)))
		CONE->h = 0;
	else
		CONE->radius = tan(CONE->angle) * CONE->h;
	return (1);
}

int						create_cone(t_kvlexer *token, t_rt *rt)
{
	t_obj				obj;

	if (!(obj.data = ft_memalloc(sizeof(t_cone))))
		return (0);
	obj.normal = &normal_cone;
	obj.inter = &inter_cone;
	obj.texture = NULL;
	obj.destroy = NULL;
<<<<<<< HEAD
	obj.tex = NULL;
=======
>>>>>>> 506c03b7047b32355bce118244c4f099c0e18cbd
	if (create_cone2(token, rt, &obj))
		ft_lstadd(&rt->objs, ft_lstnew(&obj, sizeof(obj)));
	else
	{
		free(obj.data);
		return (0);
	}
	return (1);
}

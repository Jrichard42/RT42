/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:29:48 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/25 14:51:51 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"
#include "sphere.h"
#include "quadratic.h"
#include "parser.h"
#include "libft.h"

#define	SPHERE ((t_sphere *)obj->data)

static	t_vector3f	sphere_tex(t_obj *self, t_inter inter)
{
	t_vector3f		color;
	t_vector3f		pos;
	t_vector3f		uv;

	pos = sub_vector3f(inter.obj->pos, inter.impact);
	pos = normalize_vector3f(pos);
	uv.x = asinf(pos.x) / M_PI + 0.5f;
	uv.y = asinf(pos.y) / M_PI + 0.5f;
	color = get_tex_point(self->tex, uv.x, uv.y);
	return (color);
}

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
	if (var.result < 0)
		return (NAN);
	return (var.result);
}

static t_vector3f	normal_sphere(struct s_obj *obj, t_vector3f *impact)
{
	return (normalize_vector3f(sub_vector3f(*impact, obj->pos)));
}

int					create_sphere(t_kvlexer *token, t_rt *rt)
{
	t_obj			*obj;

	if (!(obj = ft_memalloc(sizeof(*obj))))
		return (0);
	if (!(obj->data = ft_memalloc(sizeof(t_sphere))))
		return (0);
	obj->normal = &normal_sphere;
	obj->inter = &inter_sphere;
	obj->texture = &sphere_tex;
	obj->pos = get_as_vector3f(token, "POS");
	obj->mat = get_material(token);
	obj->id = get_as_float(token, "ID");
	obj->is_src = get_as_float(token, "IS_SRC");
	obj->is_visible = get_as_float(token, "IS_VISIBLE");
	SPHERE->radius = get_as_float(token, "RADIUS");
	obj->dir = get_as_vector3f(token, "DIR");
	obj->dir = normalize_vector3f(obj->dir);
	obj->color = get_as_vector3f(token, "COLOR");
	obj->tex = create_texture(840, 840, "WOOD");
	ft_lstadd(&rt->objs, ft_lstnew(obj, sizeof(*obj)));
	ft_memdel((void **)&obj);
	return (1);
}

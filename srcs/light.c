/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:29:48 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/18 18:08:12 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include "inter.h"
#include "libft.h"

#define	LIGHT ((t_light *)obj->data)

static float		specular_light(t_obj *obj, t_inter *inter, t_ray *ray)
{
	t_vector3f		pos_cam;
	t_vector3f		incidence;
	t_vector3f		tmp;
	float			angle;

	pos_cam = sub_vector3f(ray->start, inter->impact);
	incidence = sub_vector3f(inter->impact, obj->pos);
	tmp = mult_vector3f(inter->normal, 2.0);
	tmp = mult_vector3f(tmp, dot_vector3f(inter->normal, incidence));
	tmp = sub_vector3f(incidence, tmp);
	tmp = normalize_vector3f(tmp);
	pos_cam = normalize_vector3f(pos_cam);
	angle = dot_vector3f(pos_cam, tmp);
	angle = powf(angle, inter->obj->mat.sh);
	if (angle < 0)
		angle = 0;
	return (angle);
}

static float		diffuse_light(t_obj *obj, t_inter *inter)
{
	t_vector3f		ray_light;
	float			norme;

	ray_light = normalize_vector3f(sub_vector3f(obj->pos, inter->impact));
	norme = dot_vector3f(ray_light, inter->normal);
	if (norme < 0)
		norme = 0;
	return (norme);
}

t_vector3f			calcul_light(t_obj *obj, t_inter *inter, t_ray *ray, t_vector3f *color)
{
	float			diffuse;
	float			specular;
	t_vector3f		color_return;
	float			coeffs;

	diffuse = diffuse_light(obj, inter) * inter->obj->mat.kd;
	specular = specular_light(obj, inter, ray) * inter->obj->mat.ks;
	coeffs = (diffuse + specular + inter->obj->mat.ka);
	color_return = mult_vector3f(LIGHT->color, coeffs); //TODO intensity
	color_return = add_vector3f(color_return, *color);
	if (color_return.x > 255)
		color_return.x = 255;
	if (color_return.y > 255)
		color_return.y = 255;
	if (color_return.z > 255)
		color_return.z = 255;
	return (color_return);
}

int					create_light(t_kvlexer *token, t_rt *rt)
{
	t_obj			*obj;

	if (!(obj = ft_memalloc(sizeof(*obj))))
		return (-1);
	if (!(obj->data = ft_memalloc(sizeof(t_light))))
		return (-1);
	obj->pos = get_as_vector3f(token, "POSITION");
	obj->mat = get_material(token);
	obj->id = get_as_float(token, "ID");
	obj->is_src = get_as_float(token, "IS_SRC");
	obj->is_visible = get_as_float(token, "IS_VISIBLE");
	ft_lstadd(&rt->objs, ft_lstnew(obj, sizeof(*obj)));
	ft_memdel((void **)&obj);
	return (0);
}

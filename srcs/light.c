/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:29:48 by hpachy            #+#    #+#             */
/*   Updated: 2017/02/24 17:38:37 by hpachy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include "inter.h"
#include "libft.h"
#include "plane.h"
#include "parser.h"

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

float		diffuse_light(t_obj *obj, t_inter *inter)
{
	t_vector3f		ray_light;
	float			angle;

	ray_light = normalize_vector3f(sub_vector3f(obj->pos, inter->impact));
	angle = dot_vector3f(ray_light, inter->normal);
	if (angle < 0)
		angle = 0;
	return (angle);
}

t_vector3f			calcul_light(t_obj *obj, t_inter *inter, t_ray *ray, t_vector3f *color)
{
	float			diffuse;
	float			specular;
	t_vector3f		color_return;
	float			coeffs;

	specular = 0.0;
	diffuse = diffuse_light(obj, inter) * inter->obj->mat.kd;
	if (dot_vector3f(inter->normal, sub_vector3f(obj->pos, inter->impact)) > 0)
		specular = specular_light(obj, inter, ray) * inter->obj->mat.ks;
	//printf("diffuse = %f\n", diffuse);
	coeffs = (diffuse + specular + inter->obj->mat.ka);
	//printf("impact.x = %f impact.y = %f impact.z = %f\n", inter->impact.x, inter->impact.y, inter->impact.z);
	//printf("coef = %f\n", diffuse);
	//printf("light.x = %f\n", LIGHT->color.x);
	//color_return = div_vector3f(add_vector3f(mult_vector3f(inter->obj->color, coeffs), mult_vector3f(LIGHT->color, coeffs)), 2.0); //TODO intensity
	color_return = mult_vector3f(mult_vector3f(inter->obj->color, coeffs), LIGHT->intensity);
	color_return = add_vector3f(color_return, *color);
	if (((t_plane *)inter->obj->data)->damier)
		if (((t_plane *)inter->obj->data)->damier == 1)
			color_return = procedurale(inter, coeffs, LIGHT->intensity, color);
	//printf("color_return.x = %f color_return.y = %f color_return.z = %f\n", color_return.x, color_return.y, color_return.z);
	if (color_return.x > 255.0)
		color_return.x = 255;
	if (color_return.y > 255.0)
		color_return.y = 255;
	if (color_return.z > 255.0)
		color_return.z = 255;
	//printf("color_return.x = %f color_return.y = %f color_return.z = %f\n", color_return.x, color_return.y, color_return.z);
	return (color_return);
}

int					create_light(t_kvlexer *token, t_rt *rt)
{
	t_obj			*obj;

	if (!(obj = ft_memalloc(sizeof(*obj))))
		return (-1);
	if (!(obj->data = ft_memalloc(sizeof(t_light))))
		return (-1);
	obj->pos = get_as_vector3f(token, "POS");
	obj->mat = get_material(token);
	obj->id = get_as_float(token, "ID");
	obj->is_src = get_as_float(token, "IS_SRC");
	obj->is_visible = get_as_float(token, "IS_VISIBLE");
	LIGHT->color = get_as_vector3f(token, "COLOR");
	LIGHT->intensity = get_as_float(token, "INTENSITY");
	ft_lstadd(&rt->objs, ft_lstnew(obj, sizeof(*obj)));
	ft_memdel((void **)&obj);
	return (0);
}

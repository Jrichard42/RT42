/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpachy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:29:48 by hpachy            #+#    #+#             */
/*   Updated: 2017/03/16 14:55:09 by jrichard         ###   ########.fr       */
/*   Updated: 2017/02/25 14:24:47 by jrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include "inter.h"
#include "libft.h"
#include "procedurale.h"
#include "parser.h"

#define	LIGHT ((t_light *)obj->data)

static float		specular_light(t_obj *obj, t_inter *inter, t_ray *ray)
{
	t_vector3f		pos_cam;
	t_vector3f		incidence;
	t_vector3f		tmp;
	double			angle;

	pos_cam = sub_vector3f(ray->start, inter->impact);
	incidence = sub_vector3f(inter->impact, obj->pos);
	tmp = mult_vector3f(inter->normal, 2.0);
	tmp = mult_vector3f(tmp, dot_vector3f(inter->normal, incidence));
	tmp = sub_vector3f(incidence, tmp);
	tmp = normalize_vector3f(tmp);
	pos_cam = normalize_vector3f(pos_cam);
	angle = dot_vector3f(pos_cam, tmp);
	if (angle < 0)
		angle = 0;
	angle = powf(angle, inter->obj->mat.sh);
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

t_vector3f	calcul_coef(t_obj *obj, t_inter *inter, t_ray *ray)
{
	t_vector3f		diffuse;
	t_vector3f		specular;
	t_vector3f		coeffs;

	specular = create_vector3f(0,0,0);
	diffuse = mult_vector3f(inter->obj->mat.kd, diffuse_light(obj, inter));
	if (dot_vector3f(inter->normal, sub_vector3f(obj->pos, inter->impact)) > 0)
		specular = mult_vector3f(inter->obj->mat.ks, specular_light(obj, inter, ray));
	//printf("specular = %f diffuse = %f\n", specular, diffuse);
	coeffs = add_vector3f(add_vector3f(diffuse, specular), inter->obj->mat.ka);
	return (coeffs);
}

t_vector3f	calcul_light(t_obj *obj, t_ray *ray, t_inter *inter)
{
	t_vector3f		color_return;
	t_vector3f		coeffs;

	coeffs = calcul_coef(obj, inter, ray);
	//printf("coeffs = %f\n", coeffs);
	//printf("color.x = %f color.y = %f color.z = %f\n", obj->color.x, obj->color.y, obj->color.z);
	//color_return = mult_vector3f(div_vector3f(add_vector3f(mult_vector3f(inter->obj->color, coeffs), mult_vector3f(obj->light.color, coeffs)), 2.0), obj->light.intensity); //TODO intensity
	//color_return = 
	color_return = mult_vector3f(mult_by_vector3f(obj->light.color, coeffs), obj->light.intensity);
	return (color_return);
}

t_vector3f	calcul_light_procedurale(t_obj *obj, t_ray *ray, t_inter *inter)
{
	t_vector3f		color_return;
	t_vector3f			coeffs;

	coeffs = calcul_coef(obj, inter, ray);
	color_return = procedurale(inter, &coeffs, &obj->light.intensity);
	return (color_return);
}

int					create_light(t_kvlexer *token, t_rt *rt)
{
	t_obj			*obj;

	if (!(obj = ft_memalloc(sizeof(*obj))))
		return (0);
//	if (!(obj->data = ft_memalloc(sizeof(t_light))))
//		return (0);
	obj->pos = get_as_vector3f(token, "POS");
	obj->mat = get_material(token);
	obj->id = get_as_float(token, "ID");
	obj->is_src = get_as_float(token, "IS_SRC");
	obj->is_visible = get_as_float(token, "IS_VISIBLE");
	obj->light.color = get_as_vector3f(token, "COLOR");
	obj->light.intensity = get_as_float(token, "INTENSITY");
	obj->light.calc_light = &calcul_light;
	//	LIGHT->color = get_as_vector3f(token, "COLOR");
	//	LIGHT->intensity = get_as_float(token, "INTENSITY");
	ft_lstadd(&rt->objs, ft_lstnew(obj, sizeof(*obj)));
	ft_memdel((void **)&obj);
	return (1);
}
